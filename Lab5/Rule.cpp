//
// Created by Gregory Knapp on 7/1/20.
//

#include "Rule.h"

Rule::Rule() {
    predicateList.clear();
    headPredicate = Predicate();
}

string Rule::toString() {
    stringstream ss;
    ss << headPredicate.toString() << " :- ";

    for (unsigned int i = 0; i < predicateList.size(); i++) {

        if (i != predicateList.size() - 1) {
            ss << predicateList.at(i).toString() << ",";
        }
        else {
            ss << predicateList.at(i).toString();
        }
    }
    return ss.str();
}

void Rule::addHeadPredicate(Predicate newPredicate) {
    headPredicate = newPredicate;
}

void Rule::addToVector(Predicate newPredicate) {
    predicateList.push_back(newPredicate);
}
void Rule::clear() {
    headPredicate = Predicate();
    predicateList.clear();
}
Predicate Rule::getHead() {
    return headPredicate;
}
vector<Predicate> Rule::getPredicateList() {
    return predicateList;
}
void Rule::setIdentifier(int iden) {
    identifier = iden;
}
int Rule::getIdentifier() {
    return identifier;
}