//
// Created by Gregory Knapp on 7/16/20.
//

#include "Relations.h"

Relations::Relations() { //delete later?

}
Relations::Relations(Scheme scheme) {
    myScheme = scheme;
}

Relations::Relations(string ID, Scheme scheme) {
    name = ID;
    myScheme = scheme;
}

bool Relations::addTuple(Tuple myTuple) {
    bool wasAdded = tupleSet.insert(myTuple).second;
    return wasAdded;
}

void Relations::toString() const {
    cout << "Relation name: " << name << endl;
    cout << "Attributes: ";
    for (unsigned int i = 0; i < myScheme.size(); i++) {
        cout << myScheme.at(i) << " ";
    }
    cout << endl;
    this->printTuples();

}
string Relations::getName() {
    return name;
}
Scheme Relations::getScheme() {
    return myScheme;
}

void Relations::printTuples() const {
    for (auto it = tupleSet.begin(); it != tupleSet.end(); it++) {
        it->toString();
    }
}

Relations Relations::selectConstant(int position, string value) {
    string name = this->getName();
    Scheme scheme = this->getScheme();

    Relations selectedRelation(name, scheme);

    for (auto it = tupleSet.begin(); it != tupleSet.end(); it++) {
        if (it->at(position) == value) {
            selectedRelation.addTuple(*it);
        }
    }

    return selectedRelation;
}

Relations Relations::selectVariable(int positionFirst, int positionSecond) {
    string relationName = this->getName();
    Scheme scheme = this->getScheme();

    Relations selectedRelation(relationName, scheme);

    for (auto it = tupleSet.begin(); it != tupleSet.end(); it++) {
        if (it->at(positionFirst) == it->at(positionSecond)) {
            selectedRelation.addTuple(*it);
        }
    }

    return selectedRelation;
}

Relations Relations::project(vector<int> columnIndexes) {
    string relationName = this->getName();
    Scheme scheme = this->getScheme();

    //Get new scheme based on columns
    Scheme newScheme;

    for (unsigned int i = 0; i < columnIndexes.size(); i++) {
        newScheme.push_back(scheme.at(columnIndexes.at(i)));
    }


    Relations projectedRelation(relationName, newScheme);
    //Get tuples from list of columns

    for (auto it = tupleSet.begin(); it != tupleSet.end(); it++) {

        Tuple projectedTuples;

        for (unsigned int i = 0; i < columnIndexes.size(); i++) {
            int position = columnIndexes.at(i);
            projectedTuples.push_back(it->at(position));
        }
        //cout << "Tuple created: ";
        //projectedTuples.toString();
        projectedRelation.addTuple(projectedTuples);
    }

    return projectedRelation;
}

Relations Relations::rename(vector<string> variables) {
    Scheme newScheme;

    for (unsigned int i = 0; i < variables.size(); i++) {
        newScheme.push_back(variables.at(i));
    }

    Relations renameRelation = *this;
    renameRelation.setScheme(newScheme);

    return renameRelation;
}

Relations Relations::join(Relations secondRelation) {
    Scheme combineScheme = this->getScheme();
    Scheme addScheme = secondRelation.getScheme();
    vector<pair<int,int>> matchPositions;
    bool matchFound = false;

    //Get pair of all matching positions to check if any
    for (unsigned int i = 0; i < combineScheme.size(); i++) {
        for (unsigned int j = 0; j < addScheme.size(); j++) {
            if (combineScheme.at(i) == addScheme.at(j)) {
                pair<int,int> myPair;
                myPair.first = i;
                myPair.second = j;
                matchPositions.push_back(myPair);
                matchFound = true;
            }
        }
    }

    //Create new Scheme of the twos
    for (unsigned int i = 0; i < addScheme.size(); i++) {
        combineScheme.push_back(addScheme.at(i));
    }


    //Create empty relation with only new scheme
    Relations joinRelation(combineScheme);


    set<Tuple> secondTuples = secondRelation.getTuple();

    //Check if can join using match position
    for (auto it = tupleSet.begin(); it != tupleSet.end(); it++) { //Loop of Relation 1's Tuples
        for (auto up = secondTuples.begin(); up != secondTuples.end(); up++) { //Loop of Relation 2's Tuples

            //Find out if second tuple at match position matches any values in vector

            if (matchFound) { //If schemes have identical variables check for matches

                bool addTuple = true;

                //Iterate through all matching pairs, check if the given values match at the right positions
                //A tuple must match in all the given positions to be added.
                for (unsigned int i = 0; i < matchPositions.size(); i++) {
                    int firstPosition = matchPositions.at(i).first;
                    int secondPosition = matchPositions.at(i).second;
                    string matchFirst = it->at(firstPosition);
                    string matchSecond = up->at(secondPosition);

                    //If a pairing does not match in the given positions - break and skip adding
                    if (matchFirst != matchSecond) {
                        addTuple = false;
                        break;
                    }
                    //If they match, continue looping through. All matches will leave addTuple as true
                }

                //If the two tuples matched in all the same variables
                if (addTuple) {

                    //cout << "Found a match: " << matchTuple;
                    Tuple firstTuples = *it;
                    Tuple secondTuple = *up;

                    //Combine Tuples
                    for (unsigned int i = 0; i < secondTuple.size(); i++) {
                        firstTuples.push_back(secondTuple.at(i));
                    }
                    //Add to Relation
                    joinRelation.addTuple(firstTuples);
                }
            }
            else { //Just join the two
                Tuple firstTuples = *it;
                Tuple secondTuple = *up;

                //Combine Tuples
                for (unsigned int i = 0; i < secondTuple.size(); i++) {
                    firstTuples.push_back(secondTuple.at(i));
                }
                //Add to Relation
                joinRelation.addTuple(firstTuples);
            }
        }
    }


    return joinRelation;
}

void Relations::setScheme(Scheme scheme) {
    myScheme = scheme;
}

int Relations::getSize() {
    return tupleSet.size();
}
set<Tuple> Relations::getTuple() {
    return tupleSet;
}

void Relations::printFinal() const {
    if (!myScheme.empty()) {
        for (auto it = tupleSet.begin(); it != tupleSet.end(); it++) {
            cout << "  ";

            for (unsigned int i = 0; i < myScheme.size(); i++) {
                if (i == myScheme.size() - 1) {
                    cout << myScheme.at(i) << "=" << it->at(i);
                }
                else {
                    cout << myScheme.at(i) << "=" << it->at(i) << ", ";
                }
            }
            if (next(it,1) != tupleSet.end()) {
                cout << endl;
            }
        }
    }
}
void Relations::clearTuples() {
    tupleSet.clear();
}