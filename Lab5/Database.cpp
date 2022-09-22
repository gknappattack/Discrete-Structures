//
// Created by Gregory Knapp on 7/16/20.
//

#include "Database.h"

Database::Database(DatalogProgram datalog) {
    myDatalog = datalog;
}

void Database::createDatabase() {

    evaluateSchemes();
    evaluateFacts();
    optimizeRules();
    cout << endl;
    evaluateQueries();
}

void Database::evaluateSchemes() {
    vector<Predicate> schemes = myDatalog.getSchemes();

    for (unsigned int i = 0; i < schemes.size(); i++) {
        vector<string> attributes = schemes.at(i).getVector();

        Scheme currentScheme;
        string relationName = schemes.at(i).getID();

        for (unsigned int j = 0; j < attributes.size(); j++) {
            currentScheme.push_back(attributes.at(j));
        }

        Relations newRelation(relationName,currentScheme);

        myDatabase.insert(std::pair<string,Relations>(relationName, newRelation));
    }

}

void Database::evaluateFacts() {
    vector<Predicate> facts = myDatalog.getFacts();

    for (unsigned int i = 0; i < facts.size(); i++) {
        vector<string> attributes = facts.at(i).getVector();

        Tuple currentFact;
        string relationName = facts.at(i).getID();

        for (unsigned int j = 0; j < attributes.size(); j++) {
            currentFact.push_back(attributes.at(j));
        }

        myDatabase.at(relationName).addTuple(currentFact);

    }
}

void Database::optimizeRules() {
    vector<Rule> rules = myDatalog.getRules();

    Graph myGraph(rules);
    myGraph.createDependency();
    myGraph.reverseDependency();
    myGraph.dfsForest();
    myGraph.findSCC();
    //myGraph.printSCC();

    vector<set<int>> SCCList = myGraph.getSCCList();

    cout << endl << "Rule Evaluation" << endl;

    vector<Rule> rulesSCC;

    for (unsigned int i = 0; i < SCCList.size(); i++) {
        rulesSCC.clear();
        bool runOnce = false;

        set<int> mySCC = SCCList.at(i);

        cout << "SCC: ";
        for (auto it = mySCC.begin(); it != mySCC.end(); it++) {
            for (unsigned int j = 0; j < rules.size(); j++) {
                int match = j;

                //find matching rules for SCC list
                if (match == (*it)) {
                    //Add rule to vector
                    rulesSCC.push_back(rules.at(j));
                }
            }
            //
            if (next(it) != mySCC.end()) {
                cout << "R" << *it << ",";
            }
            else {
                cout << "R" << *it << endl;
            }

            if (mySCC.size() == 1) { //Find SCCs with only one rule
                runOnce = myGraph.checkDependency(*it);
            }
        }

        //Evaluate rules on the new subset, loop back and repeat
        evaluateRules(rulesSCC, runOnce);

        for (auto it = mySCC.begin(); it != mySCC.end(); it++) {
            if (next(it) != mySCC.end()) {
                cout << "R" << *it << ",";
            }
            else {
                cout << "R" << *it << endl;
            }
        }
    }


}

void Database::evaluateRules(vector<Rule> subset, bool dependency) {

    //1. Evaluate predicates on right side of the rule separately (Predicate object)
    vector<Rule> rules = subset;
    bool changes = true;
    int loopCount = 0;

    while (changes) {
        changes = false;

        for (unsigned int i = 0; i < rules.size(); i++) {
            vector<Predicate> rightHand = rules.at(i).getPredicateList();
            Predicate head = rules.at(i).getHead();
            vector<Relations> intermediateRelations;
            vector<int> projectPositions;


            for (unsigned int j = 0; j < rightHand.size(); j++) { //Create vector of intermediate Relations
                intermediateRelations.push_back(evaluateSinglePredicate(rightHand.at(j)));
            }

            //2. Join the results using Relation.join function

            Relations joinedRelation;

            for (unsigned int j = 0; j < intermediateRelations.size(); j++) { //Set first relation, join with following
                if (j == 0) {
                    joinedRelation = intermediateRelations.at(j);
                } else {
                    joinedRelation = joinedRelation.join(intermediateRelations.at(j));
                }
            }

            //cout << endl << "Printing joined Relation" << endl << endl;
            //joinedRelation.toString();

            //3. Project columns that appear in the head predicate
            vector<string> headAttributes = head.getVector();
            queue<string> renameAttributes;

            for (unsigned int j = 0; j < headAttributes.size(); j++) {
                renameAttributes.push(headAttributes.at(j));
            }

            Scheme joinedScheme = joinedRelation.getScheme();
            string relationName = head.getID();

            //Get positions to project


            while (!renameAttributes.empty()) {
                for (unsigned int j = 0; j < joinedScheme.size(); j++) {
                    if (renameAttributes.front() == joinedScheme.at(j)) {
                        projectPositions.push_back(j);
                        renameAttributes.pop();
                        //cout << j << endl;
                        if (renameAttributes.empty()) {
                            break;
                        }
                    }
                }
            }


            joinedRelation = joinedRelation.project(projectPositions);

            //cout << endl << "Printing Projected Relation: " << endl << endl;
            //joinedRelation.toString();
            //cout << "Printing relation name: " << relationName << endl;


            //4. Rename the relationship to make it union compatible
            vector<string> renameVariables = myDatabase.at(relationName).getScheme();

            joinedRelation = joinedRelation.rename(renameVariables);


            //cout << endl << "Printing Renamed Relation:" << endl << endl;
            //joinedRelation.toString();

            //5. Union the result with the database

            set<Tuple> addTuple = joinedRelation.getTuple();
            joinedRelation.clearTuples();

            bool addedTuple = false;
            bool printNew = false;

            for (auto it = addTuple.begin(); it != addTuple.end(); it++) {
                Tuple currentTuple = *it;

                addedTuple = myDatabase.at(relationName).addTuple(currentTuple);

                if (addedTuple) {
                    joinedRelation.addTuple(currentTuple);
                    printNew = true;
                    changes = true;
                }

            }

            //cout << endl << "Printing Database after union" << endl << endl;
            //myDatabase.at(relationName).toString();


            //Output Rules and Tuples generated
            set<Tuple> ruleTuples = joinedRelation.getTuple();
            cout << rules.at(i).toString() << "." << endl;

            if (printNew) {
                joinedRelation.printFinal();
                cout << endl;
            }

            //printDatabase();

        }
        loopCount += 1;

        if (dependency) {
            changes = false;
        }
    }
    cout << loopCount << " passes: ";
}


void Database::evaluateQueries() {
    //1. Get the relation from the database with the same name as the query
    vector<Predicate> queries = myDatalog.getQueries();
    cout << "Query Evaluation" << endl;

    for (unsigned int i = 0; i < queries.size(); i++) {
        vector<string> attributes = queries.at(i).getVector();
        vector<int> projectIndexes;
        vector<string> renameVariables;

        string relationName = queries.at(i).getID();
        string variableCheck;
        int variablePosition = 0;


        Relations checkRelation = myDatabase.at(relationName);

        //2. Use various select operations to get tuples from relation that match the query (check for constant vs. variable)

        for (unsigned int j = 0; j < attributes.size(); j++) {

            string value = attributes.at(j);

            if (value.at(0) == '\'') {
                //Constant found, run select one
                checkRelation = checkRelation.selectConstant(j,value);
            }
            else if (variableCheck == value) {
                //Matching variables found, run select 2
                checkRelation = checkRelation.selectVariable(variablePosition, j);
            }
            else {
                variableCheck = value;
                variablePosition = j;
                projectIndexes.push_back(j);

                if (count(renameVariables.begin(),renameVariables.end(),value)) {
                    //Variable already in scheme, don't add
                }
                else {
                    //Variable not in scheme, add it
                    renameVariables.push_back(value);
                }
            }
        }


        //3. Project - only keep columns that correspond to variables
        checkRelation = checkRelation.project(projectIndexes);


        //4. Rename - rename scheme to match variables in query
        checkRelation = checkRelation.rename(renameVariables);


        //5. Check Query - Output results to terminal
        cout << queries.at(i).toString() << "? ";

        if (checkRelation.getSize() == 0) {
            if (i == queries.size() - 1) {
                cout << "No";
            }
            else {
                cout << "No" << endl;
            }
        }
        else {
            cout << "Yes(" << checkRelation.getSize() << ")";
            if (!checkRelation.getScheme().empty()) {
                cout << endl;
            }

            checkRelation.printFinal();

            if (i != queries.size() - 1) {
                cout << endl;
            }
        }
    }
}

Relations Database::evaluateSinglePredicate(Predicate pred) {
    //1. Get the relation from the database with the same name as the query

    vector<string> attributes = pred.getVector();
    vector<int> projectIndexes;
    vector<string> renameVariables;

    string relationName = pred.getID();
    string variableCheck;
    int variablePosition = 0;

    Relations checkRelation = myDatabase.at(relationName);

    //2. Use various select operations to get tuples from relation that match the query (check for constant vs. variable)

    for (unsigned int i = 0; i < attributes.size(); i++) {

        string value = attributes.at(i);

        if (value.at(0) == '\'') {
            //Constant found, run select one
            checkRelation = checkRelation.selectConstant(i, value);
        } else if (variableCheck == value) {
            //Matching variables found, run select 2
            checkRelation = checkRelation.selectVariable(variablePosition, i);
        } else {
            variableCheck = value;
            variablePosition = i;
            projectIndexes.push_back(i);

            if (count(renameVariables.begin(), renameVariables.end(), value)) {
                //Variable already in scheme, don't add
            } else {
                //Variable not in scheme, add it
                renameVariables.push_back(value);
            }
        }
    }


    //3. Project - only keep columns that correspond to variables
    checkRelation = checkRelation.project(projectIndexes);


    //4. Rename - rename scheme to match variables in query
    checkRelation = checkRelation.rename(renameVariables);


    //5. Check Query - Print to check (Just for testing purpose)
    //checkRelation.toString();



    return checkRelation;

}

void Database::printDatabase() {
    cout << endl;
    cout << "Printing entire database!" << endl;
    for (auto const& pair: myDatabase) {
        cout << "Relation Name: " << pair.first << endl;
        cout << "Relation Contents: " << endl;
        pair.second.printFinal();
        cout << endl;
    }
}