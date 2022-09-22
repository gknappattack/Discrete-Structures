//
// Created by Gregory Knapp on 7/1/20.
//

#ifndef LAB2_PARAMETER_H
#define LAB2_PARAMETER_H

#include <string>
#include <iostream>

using namespace std;

class Parameter {
public:
    Parameter();
    Parameter(string value);
    string toString();
    void addExpression(string value);
    void clear();
private:
    string data;

};


#endif //LAB2_PARAMETER_H
