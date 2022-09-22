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
private:
    Predicate headPredicate;
    vector<Predicate> predicateList;
};


#endif //LAB2_RULE_H
