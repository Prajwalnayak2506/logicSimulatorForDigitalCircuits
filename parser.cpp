#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "gatesIdentifier.h"
using namespace std;
void removeAllWhitespace(string& str) {
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
}
int main() {
  ifstream inputFile("c17.bench");
//   if file cant be opened then :
 if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
// when file is found and is readable : 
        vector<int> gate_type;
        vector<vector<int>> inputs;
        vector<int> outputs;
    string line;
    while (getline(inputFile, line)) { //reads one line and feeds it to the variable named line in the form of a string
        if(line[0]=='#'|| line.empty()){ //ignore comments and empty lines
            continue;
        }
        //now the task is to convert whatever is left into gates : we create 4 vectors : gates_id, gates_type, inputs, outputs  
        removeAllWhitespace(line);
        string gate;
        size_t gate_start_pos = 0;
         if (line.find('=') != string::npos) {
            gate_start_pos = line.find('=')+1;
            size_t gate_close_pos = line.find('(');
            gate = line.substr(gate_start_pos, gate_close_pos-gate_start_pos);//lmao rememeber that the second argument is not tje closing argumen tbut the argument of length
            // cout << count << "  " << line << " ==== not I/O " << gate <<" \n";
            // cout<<"\n"<<getGateValue(gate)<<"\n";
            gate_type.push_back(getGateValue(gate));
            size_t input1 = line.find(',');
            size_t input2 = line.find(')');
            int n1 = stoi(line.substr(gate_close_pos+1,input1-(gate_close_pos+1)));
            int n2 = stoi(line.substr(input1+1,input2-input1-1));
            vector<int> in;
            in.push_back(n1);
            in.push_back(n2);
            inputs.push_back(in);
            outputs.push_back(stoi(line.substr(0,line.find('='))));
        }
            else {
            size_t gate_close_pos = line.find('(');
            size_t number_close_pos = line.find(')');
            gate = line.substr(gate_start_pos, gate_close_pos); //storing the type of gate INPUT/OUTPUTS
            // cout << count << "  " << line << " ==== I/O " << gate <<" \n";
            // cout<<"\n"<<getGateValue(gate)<<"\n";
            gate_type.push_back(getGateValue(gate));
            vector<int> in;
            in.push_back(-1);
            int n=stoi(line.substr(gate_close_pos+1,number_close_pos-gate_close_pos-1));
            in.push_back(n);
            outputs.push_back(n);
            inputs.push_back(in);
         }       
    }
    inputFile.close();
}