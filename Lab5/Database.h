//
// Created by Gregory Knapp on 7/16/20.
//

#ifndef LAB2_DATABASE_H
#define LAB2_DATABASE_H

#include <iostream>
#include <map>
#include <algorithm>
#include <queue>
#include "Relations.h"
#include "Tuple.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include "Graph.h"
#include "Node.h"

using namespace std;


class Database {
public:
    Database(DatalogProgram datalog);
    void createDatabase();
    void evaluateSchemes();
    void evaluateFacts();
    void evaluateRules(vector<Rule> subset, bool dependency);
    void evaluateQueries();
    void printDatabase();
    void optimizeRules();
    Relations evaluateSinglePredicate(Predicate pred);
private:
    DatalogProgram myDatalog;
    map<string,Relations> myDatabase;
};


#endif //LAB2_DATABASE_H
