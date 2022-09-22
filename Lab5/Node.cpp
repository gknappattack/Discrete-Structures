//
// Created by Gregory Knapp on 7/30/20.
//

#include "Node.h"

Node::Node() {
}

Node::Node(int ruleID) {
    identifier = ruleID;
    visitedFlag = false;
}

void Node::addDependency(int nodeNumber) {

    dependantNodes.insert(nodeNumber);

}
set<int> Node::getDependencies() const {
    return dependantNodes;
}
int Node::getIdentifier() const {
    return identifier;
}
void Node::setFlag(bool truth) {
    visitedFlag = truth;
}
bool Node::getFlag() const {
    return visitedFlag;
}
void Node::setPostOrder(int value) {
    postOrderNumber = value;
}
int Node::getPostOrder() const {
    return postOrderNumber;
}