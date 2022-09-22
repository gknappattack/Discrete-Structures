//
// Created by Gregory Knapp on 7/16/20.
//

#ifndef LAB2_RELATIONS_H
#define LAB2_RELATIONS_H

#include "Scheme.h"
#include "Tuple.h"
#include <set>
#include <iostream>

using namespace std;


class Relations {
public:
    Relations();
    Relations(Scheme scheme);
    Relations(string ID, Scheme scheme);
    bool addTuple(Tuple myTuple);
    void setScheme(Scheme scheme);
    void toString() const;
    string getName();
    void printTuples() const; //TODO: delete test functions
    Relations selectConstant(int position, string value);
    Relations selectVariable(int positionFirst, int positionSecond);
    Relations project(vector<int> columnIndexes);
    Relations rename(vector<string> variables);
    Relations join(Relations secondScheme);
    Scheme getScheme();
    set<Tuple> getTuple();
    int getSize();
    void printFinal() const;
    void clearTuples();

private:
    string name;
    Scheme myScheme;
    set<Tuple> tupleSet;
};


#endif //LAB2_RELATIONS_H
