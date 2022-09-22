//
// Created by Gregory Knapp on 7/1/20.
//

#ifndef LAB2_DATALOGPROGRAM_H
#define LAB2_DATALOGPROGRAM_H

#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include <vector>
#include <set>

using namespace std;


class DatalogProgram {

public:
    DatalogProgram();
    void toString();
    void addScheme(Predicate newPredicate);
    void addFact(Predicate newPredicate);
    void addQuery(Predicate newPredicate);
    void addRule(Rule newRule);
    void addDomain(string newDomain);
protected:
    vector<Predicate> schemeList;
    vector<Predicate> factList;
    vector<Predicate> queryList;
    vector<Rule> ruleList;
    set<string> domainList;
};


#endif //LAB2_DATALOGPROGRAM_H
