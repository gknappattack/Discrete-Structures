//
// Created by Gregory Knapp on 7/1/20.
//

#ifndef LAB2_RULE_H
#define LAB2_RULE_H

#include "Predicate.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Rule {
public:
    Rule();
    string toString();
    void addHeadPredicate(Predicate newPredicate);
    void addToVector(Predicate newPredicate);
    void clear();
    Predicate getHead();
    vector<Predicate> getPredicateList();
    void setIdentifier(int iden);
    int getIdentifier();
private:
    Predicate headPredicate;
    vector<Predicate> predicateList;
    int identifier;
};


#endif //LAB2_RULE_H
