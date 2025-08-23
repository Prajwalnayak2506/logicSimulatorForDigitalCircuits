#pragma once
#include <unordered_map>
#include "node.h"
void buildGraph(std::unordered_map<int, Node*>& circuitMap);
void printGraph(std::unordered_map<int, Node*>& circuitMap);
