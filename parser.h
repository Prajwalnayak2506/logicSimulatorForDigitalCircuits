#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "gatesIdentifier.h"
#include "nodify.h"

using namespace std;

// Utility function to remove all whitespace from a string
inline void removeAllWhitespace(string& str) {
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}

// Main parsing function
int parsingHere(string& filename);

#endif // PARSER_H
