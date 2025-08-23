#pragma once
#include <unordered_map>
#include "node.h"
using namespace std;
void printGraphLevels(unordered_map<int, Node*>& circuitMap);
void levelize(unordered_map<int,Node*>& circuitMap,vector<Node*> OverallOutputs);