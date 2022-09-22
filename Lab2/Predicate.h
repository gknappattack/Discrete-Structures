//
// Created by Gregory Knapp on 7/1/20.
//

#ifndef LAB2_PREDICATE_H
#define LAB2_PREDICATE_H

#include "Parameter.h"
#include "Token.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;


class Predicate {
public:
    string toString();
    void setID(string value);
    void addToVector(string value);
    void clear();
private:
    vector<Parameter> parameterList;
    string ID;
};


#endif //LAB2_PREDICATE_H
