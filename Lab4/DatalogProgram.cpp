//
// Created by Gregory Knapp on 7/1/20.
//

#include "DatalogProgram.h"

DatalogProgram::DatalogProgram() {
    schemeList.clear();
    ruleList.clear();
    queryList.clear();
    factList.clear();
}

void DatalogProgram::toString() {
    cout << "Schemes(" << schemeList.size() << "):" << endl;

    for (unsigned int i = 0; i < schemeList.size(); i++) {
        cout << "  " << schemeList.at(i).toString() << endl;
    }

    cout << "Facts(" << factList.size() << "):" << endl;
    for (unsigned int i = 0; i < factList.size(); i++) {
        cout << "  " << factList.at(i).toString() << "." << endl;
    }

    cout << "Rules(" << ruleList.size() << "):" << endl;
    for (unsigned int i = 0; i < ruleList.size(); i++) {
        cout << "  " << ruleList.at(i).toString() << "." << endl;
    }

    cout << "Queries(" << queryList.size() << "):" << endl;
    for (unsigned int i = 0; i < queryList.size(); i++) {
        cout << "  " << queryList.at(i).toString() << "?" << endl;
    }

    if (domainList.size() == 0) {
        cout << "Domain(" << domainList.size() <<  "):";
    }
    else {
        cout << "Domain(" << domainList.size() <<  "):" << endl;
        for (auto it = domainList.begin(); it != domainList.end(); ++it) {
            if (*it == *domainList.rbegin()) {
                cout << "  " << *it;
            }
            else {
                cout << "  " << *it << endl;
            }
        }
    }
}

void DatalogProgram::addScheme(Predicate newPredicate) {
    schemeList.push_back(newPredicate);
}
void DatalogProgram::addFact(Predicate newPredicate) {
    factList.push_back(newPredicate);
}
void DatalogProgram::addRule(Rule newRule) {
    ruleList.push_back(newRule);
}
void DatalogProgram::addQuery(Predicate newPredicate) {
    queryList.push_back(newPredicate);
}
void DatalogProgram::addDomain(string newDomain) {
    domainList.insert(newDomain);
}
vector<Predicate> DatalogProgram::getSchemes() {
    return schemeList;
}
vector<Predicate> DatalogProgram::getFacts() {
    return factList;
}
vector<Predicate> DatalogProgram::getQueries() {
    return queryList;
}
vector<Rule> DatalogProgram::getRules() {
    return ruleList;
}