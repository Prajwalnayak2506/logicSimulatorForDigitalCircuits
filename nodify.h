#ifndef NODIFY_H
#define NODIFY_H
#include <vector>
#include <string>
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
    Node(int nodeId, int nodeType, vector<int> nodeInputs, int NodeOutput){
        id = nodeId;
        type = nodeType;
        inputs = nodeInputs;
        output = NodeOutput;
    }
};
void nodeMaker(vector<int> gate_id, vector<int> gate_type, vector<vector<int>> inputs, vector<int> outputs);
#endif