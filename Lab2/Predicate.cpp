//
// Created by Gregory Knapp on 7/1/20.
//

#include "Predicate.h"

string Predicate::toString() {
    stringstream ss;

    ss << ID << "(";
    for (unsigned int i = 0; i < parameterList.size(); i++) {

        if (i != parameterList.size() - 1) {
            ss << parameterList.at(i).toString() << ",";
        }
        else {
            ss << parameterList.at(i).toString();
        }


    }
    ss << ")";

    return ss.str();
}
void Predicate::setID(string value) {
    ID = value;
}
void Predicate::addToVector(string value) {
    Parameter newParameter = Parameter(value);
    parameterList.push_back(newParameter);
}
void Predicate::clear() {
    ID = "";
    parameterList.clear();
}
