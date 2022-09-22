//
// Created by Gregory Knapp on 7/16/20.
//

#ifndef LAB2_DATABASE_H
#define LAB2_DATABASE_H

#include <iostream>
#include <map>
#include <algorithm>
#include "Relations.h"
#include "Tuple.h"
#include "DatalogProgram.h"
#include "Predicate.h"

using namespace std;


class Database {
public:
    Database(DatalogProgram datalog);
    void printDatabase();
    void evaluateSchemes();
    void evaluateFacts();
    void evaluateQueries();
private:
    DatalogProgram myDatalog;
    map<string,Relations> myDatabase;
};


#endif //LAB2_DATABASE_H
