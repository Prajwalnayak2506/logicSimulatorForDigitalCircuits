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
        vector<int> gate_id;
        vector<int> gate_type;
        vector<int> inputs;
        vector<int> outputs;
    string line;
    int count=0;
    while (getline(inputFile, line)) { //reads one line and feeds it to the variable named line in the form of a string
        if(line[0]=='#'|| line.empty()){ //ignore comments and empty lines
            continue;
        }
        //now the task is to convert whatever is left into gates : we create 4 vectors : gates_id, gates_type, inputs, outputs  
        gate_id.push_back(count);
        removeAllWhitespace(line);
        string gate;
        size_t gate_start_pos = 0;
         if (line.find('=') != string::npos) {
            size_t gate_start_pos = line.find('=')+1;
            size_t gate_close_pos = line.find('(');
            gate = line.substr(gate_start_pos, gate_close_pos-gate_start_pos);//lmao rememeber that the second argument is not tje closing argumen tbut the argument of length
            // cout << count << "  " << line << " ==== not I/O " << gate <<" \n";
            // cout<<"\n"<<getGateValue(gate)<<"\n";
            gate_type.push_back(getGateValue(gate));
        }
            else {
            size_t gate_close_pos = line.find('(');
            gate = line.substr(gate_start_pos, gate_close_pos);
            // cout << count << "  " << line << " ==== I/O " << gate <<" \n";
            // cout<<"\n"<<getGateValue(gate)<<"\n";
            gate_type.push_back(getGateValue(gate));
         }
         count++;        
    }
    inputFile.close();
}