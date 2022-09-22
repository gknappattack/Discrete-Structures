//
// Created by Gregory Knapp on 7/30/20.
//

#ifndef LAB5_GRAPH_H
#define LAB5_GRAPH_H
#include <iostream>
#include <map>
#include "Node.h"
#include "Rule.h"
#include <string>
#include <vector>

using namespace std;


class Graph {
public:
    Graph(vector<Rule> rules);
    void createDependency();
    void reverseDependency();
    int dfs(Node& x,map<int,Node>& nodeMap);
    void dfsForest();
    void findSCC();
    void printSCC();
    vector<set<int>> getSCCList();
    bool checkDependency(int ruleNumber);
private:
    map<int, Node> graph;
    map<int,Node> reverseGraph;
    vector<Rule> ruleVector;
    int postOrderValue;
    set<int> SCC;
    vector<set<int>> SCCList;
};


#endif //LAB5_GRAPH_H
