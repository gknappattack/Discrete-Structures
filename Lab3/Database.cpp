//
// Created by Gregory Knapp on 7/16/20.
//

#include "Database.h"

Database::Database(DatalogProgram datalog) {
    myDatalog = datalog;
}

void Database::printDatabase() {

    evaluateSchemes();
    evaluateFacts();
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

void Database::evaluateQueries() {
    //1. Get the relation from the database with the same name as the query
    vector<Predicate> queries = myDatalog.getQueries();

    for (unsigned int i = 0; i < queries.size(); i++) {
        vector<string> attributes = queries.at(i).getVector();
        vector<int> projectIndexes;
        vector<string> renameVariables;

        string relationName = queries.at(i).getID();
        string variableCheck;
        int variablePosition = 0;



        //TODO: change to pass by reference for efficiency

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