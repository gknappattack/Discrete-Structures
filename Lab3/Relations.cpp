//
// Created by Gregory Knapp on 7/16/20.
//

#include "Relations.h"

Relations::Relations() { //delete later?

}

Relations::Relations(string ID, Scheme scheme) {
    name = ID;
    myScheme = scheme;
}

void Relations::addTuple(Tuple myTuple) {
    tupleSet.insert(myTuple);
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
void Relations::setScheme(Scheme scheme) {
    myScheme = scheme;
}

int Relations::getSize() {
    return tupleSet.size();
}

void Relations::printFinal() {

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