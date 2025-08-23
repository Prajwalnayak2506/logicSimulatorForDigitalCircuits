#include <iostream>
#include <unordered_map>
#include <string>
#include "node.h"
using namespace std;
// void printGraph(unordered_map<int, Node*>& circuitMap) {
//     int node_count = 0;
//     for (auto& kv : circuitMap) {
//         cout<<"node counter : "<<node_count<<"\n";
//         Node* gate = kv.second;
//         cout << "Node ID: " << gate->id << "\n";
//         cout << "Type: " << gate->type << "\n";
//         cout << "Output: " << gate->output << "\n";
//         cout << "Inputs: ";
//         for (int in : gate->inputs) {
//             cout << in << " ";
//         }
//         cout<<endl;
//         node_count++;
//         if (gate->parents.empty()) {
//             cout << "None";
//         } else {
//             cout<<"parents are: ";
//             for (Node* parent : gate->parents) {
//                 cout << parent->id << " ";
//             }
//         }
//         if (gate->children.empty()) {
//             cout << "None";
//         } else {
//             cout<<"children are: ";
//             for (Node* children : gate->children) {
//                 cout << children->id << " ";
//             }
//         }
//         cout << endl;
//         cout << "\n----------------------\n";
//     }
// }
void buildGraph(unordered_map<int,Node*>& circuitMap,vector<Node*> OverallOutputs){
    for (auto& gate_value : circuitMap){
        Node* gate = gate_value.second;
        for (int in : gate->inputs) {
            if(in == -1)
            continue;
        gate->parents.push_back(circuitMap[in]);
        circuitMap[in]->children.push_back(gate);
    }   
}
for (int i=0;i<OverallOutputs.size();i++){
    Node* gate = OverallOutputs[i];
    for (int in : gate->inputs) {
            if(in == -1)
            continue;
    gate->parents.push_back(circuitMap[in]);
    circuitMap[in]->children.push_back(gate);
}}
//testing
// printGraph(circuitMap);

}
