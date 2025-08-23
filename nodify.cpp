#include <iostream>
#include <vector>
#include <string>
#include "node.h"
#include <unordered_map>
#include "graphiphy.h"
using namespace std;
void nodeMaker(vector<int> gate_id, vector<int> gate_type, vector<vector<int>> inputs, vector<int> outputs){
    unordered_map<int, Node*> circuitOutputs;
    vector<Node*> OverAllOutputs;
    //  for (int i=0;i < outputs.size();i++){
    //     cout << gate_id[i] << ": " << gate_type[i] << " | OUTPUT : " << outputs[i] << "| INPUTS : "<<inputs[i][0] << " and " <<inputs[i][1];
    //     cout << "\n----------------------\n";
    //     // Node* gate = new Node(gate_id[i],gate_type[i],inputs[i],outputs[i]);
    // }
    for(int i = 0;i< gate_id.size();i++){
        if(gate_type[i]==1){
            Node* gate = new Node(gate_id[i],gate_type[i],inputs[i],outputs[i]);
            OverAllOutputs.push_back(gate);
        }
        else{
        Node* gate = new Node(gate_id[i],gate_type[i],inputs[i],outputs[i]);
        circuitOutputs[gate->output] = gate;
        }
    }
    

    //testing
   int node_count = 0;
    for (auto& pair : circuitOutputs) {
    cout<<"node counter : "<<node_count<<"\n";
    Node* gate = pair.second; // get the Node*
    cout << "Node ID: " << gate->id << "\n";
    cout << "Type: " << gate->type << "\n";
    cout << "Output: " << gate->output << "\n";
    cout << "Inputs: ";
    for (int in : gate->inputs) {
        cout << in << " ";
    }
    cout << "\n----------------------\n";

    node_count++;
}
    cout << "\n----------------------\n";
    cout << "\n----------------------\n";
    cout << "\n----------------------\n";
    cout << "\n----------------------\n";
    cout << "\n----------------------\n";
    for(int i=0;i<OverAllOutputs.size();i++){
        cout << "OUTPUT "<<i+1<<" has ID "<<OverAllOutputs[i]->id<<"and inputs: "<<(OverAllOutputs[i]->inputs)[0]<<" and "<<(OverAllOutputs[i]->inputs)[1]<<"\n";
    }
    buildGraph(circuitOutputs,OverAllOutputs);
}