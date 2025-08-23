#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "node.h"
#include <algorithm>
using namespace std;

int evaluateGate(int type, int in1, int in2) {
    switch(type) {
    case 0: // INPUT
    case 1: // OUTPUT
        return in1;

    case 2: // NAND
        return !(in1 & in2);

    case 3: // AND
        return in1 & in2;

    case 4: // OR
        return in1 | in2;

    case 5: // NOR
        return !(in1 | in2);

    case 6: // XOR
        return in1 ^ in2;

    case 7: // XNOR
        return !(in1 ^ in2);

    case 8: // NOT
        return !in1;

    default:
        return 0;
}
}
vector<Node*> sorter(unordered_map<int,Node*>& circuitMap,vector<Node*> OverallOutputs){
vector<Node*> levelizedNodes;
int maxLevel = 0;
for(auto& kv : circuitMap) {
    if(kv.second->level > maxLevel) maxLevel = kv.second->level;
}
for(auto* gate : OverallOutputs) {
    if(gate->level > maxLevel) maxLevel = gate->level;
}
vector<vector<Node*>> levelBuckets(maxLevel+1);
for(auto& kv : circuitMap) levelBuckets[kv.second->level].push_back(kv.second);
for(auto* gate : OverallOutputs) levelBuckets[gate->level].push_back(gate);
for(int l=0; l<=maxLevel; ++l) {
    for(auto* node : levelBuckets[l]) {
        levelizedNodes.push_back(node);
    }
}
return levelizedNodes;

}
vector<Node*> sort_inputs_outputs(const vector<Node*>& nodes, int gate_type) {
    vector<Node*> result = nodes; // copy original
    vector<Node*> to_sort;
    for(auto* node : result) {
        if(node->type == gate_type)
            to_sort.push_back(node);
    }
    sort(to_sort.begin(), to_sort.end(), [](Node* a, Node* b){
        return a->id < b->id;
    });
    int index = 0;
    for(auto& node : result) {
        if(node->type == gate_type)
            node = to_sort[index++];
    }

    return result;
}

void simulation(unordered_map<int,Node*>& circuitMap,vector<Node*> OverallOutputs) {
    ifstream tb("testbench.txt"); //reading testbench
    string line;
    vector<vector<int>> testVectors;
    while(getline(tb, line)) {
        vector<int> vec;
        for(char c : line) {
            if(c == '0' || c == '1') vec.push_back(c - '0');
        }
        testVectors.push_back(vec);
    }
    tb.close(); //read and saved everything which was in testbench
    ofstream results("sim_output.txt");
    for(auto& inputVec : testVectors) {
        int inputIndex = 0;
        vector<Node*> levelizedNodes = sorter(circuitMap,OverallOutputs);
        levelizedNodes = sort_inputs_outputs(levelizedNodes,0);
        levelizedNodes = sort_inputs_outputs(levelizedNodes,1);
        for(auto* node : levelizedNodes) {
            if(node->type == 0) { 
                node->evaluate = inputVec[inputIndex++];
            }
        }
        for(auto* node : levelizedNodes) {
            if(node->type != 0) {
                int in1 = node->parents.size() > 0 ? node->parents[0]->evaluate : 0;
                int in2 = node->parents.size() > 1 ? node->parents[1]->evaluate : 0;
                node->evaluate = evaluateGate(node->type, in1, in2);
            }
        }
        for(auto* node : OverallOutputs) {
            results << node->evaluate;
            cout<<node->evaluate;
        }
        cout<<"\n";
        
        results << "\n";
    }

    results.close();
    cout << "Simulation complete. Results in sim_output.txt\n";
}
