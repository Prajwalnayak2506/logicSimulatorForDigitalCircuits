#include <iostream>
#include <unordered_map>
#include "node.h"
#include <queue>
#include <algorithm>
using namespace std;
// void printGraphLevels(unordered_map<int, Node*>& circuitMap) {
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
//         cout<<"Level : "<<gate->level<<endl;
//         cout << endl;
//         cout << "\n----------------------\n";
//     }
// }
void levelize(unordered_map<int,Node*>& circuitMap,vector<Node*> OverallOutputs){
    queue<Node*> q;
    unordered_map<Node*, int> remainingParents;  
    for (auto& kv: circuitMap){
        Node* gate = kv.second;
        remainingParents[gate] = gate->parents.size();
        if(gate->level == 0){
            q.push(gate);
        }
    }
     while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        for (Node* child : node->children) {
            if(child->level == 0)
            continue;
            child->level = max(child->level, node->level + 1);
            remainingParents[child]--;
            if (remainingParents[child] == 0) {
                q.push(child);
            }
        }
    }
    for(int i=0;i<OverallOutputs.size();i++){
        Node* parent = circuitMap[OverallOutputs[i]->output];
        OverallOutputs[i]->level = parent->level + 1;
    }
    // printGraphLevels(circuitMap);
}