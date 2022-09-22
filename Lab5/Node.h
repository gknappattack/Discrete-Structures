//
// Created by Gregory Knapp on 7/30/20.
//

#ifndef LAB5_NODE_H
#define LAB5_NODE_H
#include <iostream>
#include <string>
#include <set>

using namespace std;


class Node {
public:
    Node();
    Node(int nodeID);
    void addDependency(int nodeNumber);
    set<int> getDependencies() const;
    int getIdentifier() const;
    void setFlag(bool truth);
    bool getFlag() const;
    void setPostOrder(int value);
    int getPostOrder() const;
private:
    bool visitedFlag;
    set<int> dependantNodes;
    int identifier;
    int postOrderNumber;
};


#endif //LAB5_NODE_H
