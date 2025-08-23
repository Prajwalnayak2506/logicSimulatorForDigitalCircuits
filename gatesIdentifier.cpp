#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
int getGateValue(const string& gateName){
    static const unordered_map<string, int> gateTypes = {
        {"INPUT", 0},
        {"OUTPUT", 1},
        {"NAND", 2},
        {"AND", 3},
        {"OR",4},
        {"NOR",5},
        {"XOR",6},
        {"XNOR",7},
        {"NOT",8}
    };
    if (gateTypes.count(gateName) > 0) {
        return gateTypes.at(gateName);
    } else {
        return -1;
    }
}