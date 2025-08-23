#pragma once
#include <unordered_map>
#include "node.h"
void printGraph(std::unordered_map<int, Node*>& circuitMap);
void buildGraph(std::unordered_map<int, Node*>& circuitMap,vector<Node*> OverallOutputs);