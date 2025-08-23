#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "node.h"
using namespace std;
int evaluateGate(int type, int in1, int in2);
vector<Node*> sorter(unordered_map<int, Node*>& circuitMap, vector<Node*> OverallOutputs);
void simulation(unordered_map<int, Node*>& circuitMap, vector<Node*> OverallOutputs);
#endif
