//
// Created by Gregory Knapp on 7/30/20.
//

#include "Graph.h"

Graph::Graph(vector<Rule> rules) {
    ruleVector = rules;
    postOrderValue = 1;
}

void Graph::createDependency() {
    cout << "Dependency Graph" << endl;

    //Create Graph with nodes, Node holds rule ID, marked at a number
    for (unsigned int i = 0; i < ruleVector.size(); i++) {
        //Create Map with nodes of current rule
        graph.insert(std::make_pair(i, Node(i)));
    }

    string ruleHead;
    string predicateID;
    //For each Rule - Iterate through predicates, if predicate matches rule head, rule is dependant,
    for (unsigned int i = 0; i < ruleVector.size(); i++) {
        //Get Rule Head value
        vector<Predicate> predicates = ruleVector.at(i).getPredicateList();

        //Secondary loop through predicates of the rule
        for (unsigned int j = 0; j < predicates.size(); j++) {
            predicateID = predicates.at(j).getID();

            //Loop through all rules again
            for (unsigned int k = 0; k < ruleVector.size(); k++) {

                //Get head of current Rule
                Predicate head = ruleVector.at(k).getHead();
                ruleHead = head.getID();

                //If rule head ID is the same as the current predicate ID
                if (ruleHead == predicateID) {

                    //Add dependancy to current rule using map
                    graph.at(i).addDependency(k);
                }
            }
        }
    }

    //Print Rule dependencies out of map, accessing set of Nodes in each map entry
    for (auto const& pair: graph) {
        cout << "R" << pair.first << ":";

        set<int> dependencies = pair.second.getDependencies();

        for (auto it = dependencies.begin(); it != dependencies.end(); it++) {
            if (next(it) != dependencies.end()) {
                cout << "R" << *it << ",";
            }
            else {
                cout << "R" << *it;
            }
        }
        cout << endl;
    }
}

void Graph::reverseDependency() {
    //cout << "Reverse Dependancy Graph" << endl;

    //Fill new map
    for (unsigned int i = 0; i < ruleVector.size(); i++) {
        //Create Map with nodes of current rule
        reverseGraph.insert(std::make_pair(i, Node(i)));
    }

    //"loop" through new map
    for (unsigned int i = 0; i < ruleVector.size(); i++) {

        //Loop through original map
        for (unsigned int j = 0; j < ruleVector.size(); j++) {
            Node currentNode = graph.at(j);

            //Access the list of adjacent nodes for current value
            set<int> adjacentNodes = currentNode.getDependencies();

            //Loop through adjacent nodes set, look for matches
            for (auto it = adjacentNodes.begin(); it != adjacentNodes.end(); it++) {
                int match = i;
                //If the value on new map is found in this set, add reverse dependency
                if (*it == match) {
                    reverseGraph.at(i).addDependency(j);
                }
            }
        }
    }

    /*for (auto const& pair: reverseGraph) {
        cout << "R" << pair.first << ":";

        set<int> dependencies = pair.second.getDependencies();

        for (auto it = dependencies.begin(); it != dependencies.end(); it++) {
            if (next(it) != dependencies.end()) {
                cout << "R" << *it << ",";
            }
            else {
                cout << "R" << *it;
            }
        }
        cout << endl;
    }
     */

}

int Graph::dfs(Node& x,map<int,Node>& nodeMap) {
    x.setFlag(true);

    //cout << "Checking node" << endl;

    set<int> adjacentNodes = x.getDependencies();

    for (auto it = adjacentNodes.begin(); it != adjacentNodes.end(); it++) {

        Node y = nodeMap.at(*it);
        bool checkNode = y.getFlag();

        if (!checkNode) { //Run dfs on not visited nodes
            dfs(nodeMap.at(*it),nodeMap);
        }

    }

    //Adding identifier of x to current SCC
    SCC.insert(x.getIdentifier());

    //Setting current number to post order value
    x.setPostOrder(postOrderValue);

    postOrderValue++;

    return postOrderValue;
}

void Graph::dfsForest() {

    //cout << "Post order numbers:" << endl;

    //Reset flags on all values of x
    for (map<int,Node>::iterator it = reverseGraph.begin(); it != reverseGraph.end(); it++) {
        it->second.setFlag(false);
    }

    //Run dfs on all nodes that are not visited yet
    for (map<int,Node>::iterator it = reverseGraph.begin(); it != reverseGraph.end(); it++) {
        if (!it->second.getFlag()) { //Check if node has already been visited
            dfs(it->second,reverseGraph);
        }
    }

    //Print PostOrder Values
    //for (auto const& pair: reverseGraph) {
      //  cout << "R" << pair.first << ":" << pair.second.getPostOrder() << endl;
   // }

}

void Graph::findSCC() {

    //Reset flags on all values of x
    for (map<int,Node>::iterator it = graph.begin(); it != graph.end(); it++) {
        it->second.setFlag(false);
    }
    vector<int> postOrderNumbers;
    for (map<int,Node>::iterator it = reverseGraph.begin(); it != reverseGraph.end(); it++) {
        int postOrder = it->second.getPostOrder();
        postOrderNumbers.push_back(postOrder);
    }


    //Iterate backwards by post order
    for (unsigned int i = ruleVector.size(); i > 0; i--) {
        SCC.clear();

        for (unsigned int j = 0; j < postOrderNumbers.size(); j++) {
            int match = i;
            if (postOrderNumbers.at(j) == match) { //Node in position j has the matching post order #

                //cout << "Calling dfs on node: " << j << endl;
                if (!graph.at(j).getFlag()) {
                    dfs(graph.at(j),graph);
                    SCCList.push_back(SCC);
                }
            }
        }
    }

    //cout << "Number of SCC's to evaluate: ";
    //cout << SCCList.size() << endl;
}

void Graph::printSCC() {
    for (unsigned int i = 0; i < SCCList.size(); i++) {
        set<int> mySCC = SCCList.at(i);
        cout << "SCC #" << i << ":";

        for (auto it = mySCC.begin(); it != mySCC.end(); it++) {
            cout << "R" << *it << ",";
        }
        cout << endl;
    }
}

vector<set<int>> Graph::getSCCList() {
    return SCCList;
}

bool Graph::checkDependency(int ruleNumber) {

    set<int> dependencies = graph.at(ruleNumber).getDependencies();

    for (auto it = dependencies.begin(); it != dependencies.end(); it++) {
        if ((*it) == ruleNumber) { //Rule depends on itself, repeat multiple times
            return false;
        }
    }
    //Rule was not found in the dependency, run only one time
    return true;
}