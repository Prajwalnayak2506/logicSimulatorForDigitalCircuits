#include <iostream>
#include <unordered_map>
#include <string>
#include "node.h"
using namespace std;
void printGraph(unordered_map<int, Node*>& circuitMap) {
    for (auto& kv : circuitMap) {
        Node* gate = kv.second;
        cout << "Gate " << gate->id << " (output=" << gate->output << ") has parents: ";
        
        if (gate->parents.empty()) {
            cout << "None";
        } else {
            for (Node* parent : gate->parents) {
                cout << parent->id << " ";
            }
        }
        cout << endl;
    }
}
void buildGraph(unordered_map<int,Node*>& circuitMap){
    for (auto& gate_value : circuitMap){
        int out = gate_value.first;
        Node* gate = gate_value.second;
        for (int in : gate->inputs) {
            if (circuitMap.count(in)) {
                gate->parents.push_back(circuitMap[in]);
    }
    printGraph(circuitMap);
}}}
