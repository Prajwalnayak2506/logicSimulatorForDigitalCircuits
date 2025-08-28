#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <cctype>
using namespace std;

struct Gate {
    string type;
    int output_id;
    vector<int> input_ids;
};
string stripComment(const string& line) {
    size_t pos = line.find("--");
    if (pos != string::npos) {
        return line.substr(0, pos); 
    }
    return line;
}
string trim(const string& str) {
    const string whitespace = " \t\n\r\f\v";
    size_t first = str.find_first_not_of(whitespace);
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(whitespace);
    return str.substr(first, (last - first + 1));
}

string toUpper(string s) {
    transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return toupper(c); });
    return s;
}

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

int getSignalId(const string& signalName, map<string, int>& signalMap, int& nextId) {
    if (signalMap.find(signalName) == signalMap.end()) {
        signalMap[signalName] = nextId++;
    }
    cout<<"signalName :"<<signalName<<" :"<<signalMap[signalName]<<endl;
    return signalMap[signalName];
}
void vectorHadler(string& line,string& dir, int left, int right, map<string, int>& signalMap, int& nextId, string& portName, vector<int>& input_ids,vector<int>& output_ids){
    if (toUpper(dir) == "DOWNTO") {
                            for (int i = left; i >= right; --i) {
                            //    cout<<line<<endl;
                               stringstream ss(line);
                               string portNamesStr, colon, direction, type;
                               getline(ss, portNamesStr, ':');
                               ss >> direction; 
                               vector<string> portNames = split(trim(portNamesStr), ','); 
                            //    cout<< portNamesStr<<endl;
                            //    for (const auto& name : portNames) {
                            //         cout << name << endl;
                            //      }
                               if (toUpper(trim(direction)) == "IN") {
                                    //    cout<<"hi"<<endl; checking if this is working during debugging
                                    for (const auto& name : portNames) {
                                         string bitName = name + "(" + to_string(i) + ")";
                                         cout << bitName << endl;
                                         input_ids.push_back(getSignalId(bitName, signalMap, nextId));
                                       }
                                   } else if (toUpper(direction) == "OUT") {
                                   for (const auto& name : portNames) {
                                        string bitName = name + "(" + to_string(i) + ")";
                                         cout << bitName << endl;
                                        output_ids.push_back(getSignalId(bitName, signalMap, nextId));
                                      }      
                                 }
                             }       
                             } else if (toUpper(dir) == "TO") {
                              for (int i = left; i <= right; ++i) {
                                 stringstream ss(line);
                               string portNamesStr, colon, direction, type;
                               getline(ss, portNamesStr, ':');
                               ss >> direction; 
                               vector<string> portNames = split(trim(portNamesStr), ','); 
                            //    cout<< portNamesStr<<endl;
                            //    for (const auto& name : portNames) {
                            //         cout << name << endl;
                            //      }
                               if (toUpper(trim(direction)) == "IN") {
                                    //    cout<<"hi"<<endl; checking if this is working during debugging
                                    for (const auto& name : portNames) {
                                         string bitName = name + "(" + to_string(i) + ")";
                                         cout << bitName << endl;
                                         input_ids.push_back(getSignalId(bitName, signalMap, nextId));
                                       }
                                   } else if (toUpper(direction) == "OUT") {
                                   for (const auto& name : portNames) {
                                        string bitName = name + "(" + to_string(i) + ")";
                                         cout << bitName << endl;
                                        output_ids.push_back(getSignalId(bitName, signalMap, nextId));
                                      }      
                                 }
                              }
                            }

}
void parseVHDL(ifstream& vhdlFile,
               string& circuitName,
               vector<int>& input_ids,
               vector<int>& output_ids,
               vector<Gate>& gates,
               map<string, int>& signalMap,
               int& nextId) {

    string line;
    bool inEntity = false;
    bool inArchitecture = false;

    while (getline(vhdlFile, line)) {
        line = trim(line);
        line = stripComment(line);
        if(line.find("--")!= string::npos){

        }
        string upperLine = toUpper(line);
        if (upperLine.find("ENTITY") != string::npos && upperLine.find(" IS") != string::npos) {
            stringstream ss(line);
            string keyword;
            ss >> keyword >> circuitName;
            inEntity = true;
            continue;
        }
        if (inEntity) {
            if (upperLine.find("PORT") != string::npos) { 
                while (getline(vhdlFile, line)) {
                    line = trim(line);
                    line = stripComment(line);
                    upperLine = toUpper(line);
                    // cout<<line<<endl;
                    if (line.find(");") != string::npos && line.find("(") == string::npos) { 
                        inEntity = false;
                        break;
                    }
                    // cout<<line<<endl;
                    string line1 = toUpper(line);
                    if(line1.find("VECTOR")!= string::npos){
                        // cout<<"there is a vector"<<endl;
                        string portName = trim(line.substr(0, line.find(':')));
                        size_t open = line.find('(');
                        size_t close = line.find(')');
                        string range = trim(line.substr(open + 1, close - open - 1));
                        // cout<<range<<endl;
                        int left, right;
                        string dir;
                        stringstream ss(range);
                        ss >> left >> dir >> right; 
                        // cout<<left<<" "<<dir<<right<<endl;
                        vectorHadler(line,dir,left,right,signalMap,nextId,portName,input_ids,output_ids);
                    }
                    else{
                    stringstream ss(line);
                    string portNamesStr, colon, direction, type; 
                    getline(ss, portNamesStr, ':');
                    ss >> direction; 
                    vector<string> portNames = split(trim(portNamesStr), ','); 
                    if (toUpper(trim(direction)) == "IN") {
                        for (const auto& name : portNames) {
                            input_ids.push_back(getSignalId(name, signalMap, nextId));
                        }
                    } else if (toUpper(direction) == "OUT") {
                        for (const auto& name : portNames) {
                            output_ids.push_back(getSignalId(name, signalMap, nextId));
                        }      
                    }
                }
            }
            }
        }
        if (upperLine.find("ARCHITECTURE") != string::npos || upperLine == "BEGIN") {
            inArchitecture = true;
            continue;
        }
        if (inArchitecture) {
            size_t assignPos = line.find("<=");
            if (assignPos != string::npos) {
                Gate currentGate;
                string outputName = trim(line.substr(0, assignPos));
                currentGate.output_id = getSignalId(outputName, signalMap, nextId);
                string logicPart = trim(line.substr(assignPos + 2));
                if (logicPart.back() == ';') {
                    logicPart.pop_back();
                }
                string logicUpper = toUpper(logicPart);
                vector<string> gateKeywords = {"NAND", "NOR", "AND", "XNOR", "XOR","NOT", "OR"};
                string foundKeyword;
                for(const auto& keyword : gateKeywords) {
                    if (logicUpper.find(keyword) != string::npos) {
                        foundKeyword = keyword;
                        break;
                    }
                }
                if (!foundKeyword.empty()) {
                    currentGate.type = foundKeyword;
                    size_t keywordPos = logicUpper.find(foundKeyword);
                    string input1_str = trim(logicPart.substr(0, keywordPos));
                    string input2_str = trim(logicPart.substr(keywordPos + foundKeyword.length()));
                    size_t endPos = input2_str.find(';');
                    string input3_str = trim(input2_str.substr(0,endPos));
                    // cout<<input3_str<<endl;
                    currentGate.input_ids.push_back(getSignalId(input1_str, signalMap, nextId));
                    currentGate.input_ids.push_back(getSignalId(input3_str, signalMap, nextId));
                    
                    gates.push_back(currentGate);
                }
            }
            else if (upperLine.find("PORT MAP") != string::npos) {
                Gate currentGate;
                size_t colonPos = line.find(':');
                size_t portMapPos = upperLine.find("PORT MAP");
                if (colonPos != string::npos) {
                    currentGate.type = trim(line.substr(colonPos + 1, portMapPos - (colonPos + 1)));
                    currentGate.type.erase(remove_if(currentGate.type.begin(), currentGate.type.end(), ::isdigit), currentGate.type.end());
                    currentGate.type = toUpper(currentGate.type);
                }

                size_t openParen = line.find('(');
                size_t closeParen = line.find(')');
                string connections = line.substr(openParen + 1, closeParen - openParen - 1);
                vector<string> portMaps = split(connections, ',');

                for (const auto& pm : portMaps) {
                    vector<string> mapping = split(pm, '=');
                    if (mapping.size() < 2) continue;
                    
                    string portName = trim(mapping[0]);
                    string signalName = trim(split(mapping[1], '>')[1]);

                    if (portName.length() > 0 && (portName[0] == 'o' || portName[0] == 'O')) {
                        currentGate.output_id = getSignalId(signalName, signalMap, nextId);
                    } else {
                        currentGate.input_ids.push_back(getSignalId(signalName, signalMap, nextId));
                    }
                }
                gates.push_back(currentGate);
            }
        }
    }
}

void writeBench(ofstream& benchFile,
                const string& circuitName,
                const vector<int>& input_ids,
                const vector<int>& output_ids,
                const vector<Gate>& gates) {

    map<string, int> gateCounts;
    int inverterCount = 0;
    for (const auto& gate : gates) {
        gateCounts[gate.type]++;
        if (gate.type == "NOT" || gate.type == "INV") {
            inverterCount++;
        }
    }

    benchFile << "# " << (circuitName.empty() ? "circuit" : circuitName) << endl;
    benchFile << "# " << input_ids.size() << " inputs" << endl;
    benchFile << "# " << output_ids.size() << " outputs" << endl;
    benchFile << "# " << inverterCount << " inverter" << (inverterCount != 1 ? "s" : "") << endl;

    stringstream gateSummary;
    gateSummary << "# " << gates.size() << " gates ( ";
    for (auto const& pair : gateCounts) {
        string type = pair.first;
        int count = pair.second;
        gateSummary << count << " " << type << (count > 1 ? "s" : "") << " ";
    }
    gateSummary << ")";
    benchFile << gateSummary.str() << endl << endl;

    for (int id : input_ids) {
        cout<<id<<endl;
        benchFile << "INPUT(" << id << ")" << endl;
    }
    benchFile << endl;

    for (int id : output_ids) {
        benchFile << "OUTPUT(" << id << ")" << endl;
    }
    benchFile << endl;

    for (const auto& gate : gates) {
        benchFile << gate.output_id << " = " << gate.type << "(";
        for (size_t i = 0; i < gate.input_ids.size(); ++i) {
            benchFile << gate.input_ids[i] << (i == gate.input_ids.size() - 1 ? "" : ", ");
        }
        benchFile << ")" << endl;
    }
}


int main() {
    string vhdlFileName;
    cout << "Enter the name of the VHDL input file: ";
    cin >> vhdlFileName;

    string benchFileName = vhdlFileName;
    size_t dotPos = benchFileName.rfind('.');
    if (dotPos != string::npos) {
        benchFileName.replace(dotPos, string::npos, ".bench");
    } else {
        benchFileName += ".bench";
    }

    ifstream vhdlFile(vhdlFileName);
    if (!vhdlFile.is_open()) {
        cerr << "Error: Could not open input file " << vhdlFileName << endl;
        return 1;
    }

    string circuitName;
    vector<int> input_ids;
    vector<int> output_ids;
    vector<Gate> gates;
    map<string, int> signalMap;
    int nextSignalId = 1;

    parseVHDL(vhdlFile, circuitName, input_ids, output_ids, gates, signalMap, nextSignalId);
    vhdlFile.close();

    ofstream benchFile(benchFileName);
    if (!benchFile.is_open()) {
        cerr << "Error: Could not open output file " << benchFileName << endl;
        return 1;
    }

    writeBench(benchFile, circuitName, input_ids, output_ids, gates);
    benchFile.close();

    cout << "Conversion successful!" << endl;
    cout << "Converted " << vhdlFileName << " to " << benchFileName << endl;

    return 0;
}