#pragma once
#include <vector>
using namespace std; 

class Node {
public:
    int id;
    int type;
    vector<int> inputs;
    int output;
    int level = -1;
    vector<Node*> children;
    vector<Node*> parents;
    int evaluate = -1;
    Node(int nodeId, int nodeType, vector<int> nodeInputs, int NodeOutput) {
        id = nodeId;
        type = nodeType;
        inputs = nodeInputs;
        output = NodeOutput;
    }
};
