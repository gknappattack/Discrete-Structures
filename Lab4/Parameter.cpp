//
// Created by Gregory Knapp on 7/1/20.
//

#include "Parameter.h"

Parameter::Parameter() {
    data = "";
}
Parameter::Parameter(string value) {
    data = value;
}
string Parameter::toString() {
    return data;
}
void Parameter::addExpression(string value) {
    data +=  value;
}
void Parameter::clear() {
    data = "";
}
