#pragma once
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include "Lexer/Token.hpp"

using namespace std;
void error(string, string, int);

namespace Helper
{
int char2Int(char C);
int str2Int(string Str);
vector<bool> int2Bool(int);
vector<vector<bool>> generateTable2D(int);
int bool2Int(vector<bool>);
vector<string> getNames(vector<Token>);
bool inList(string, vector<string>);
} // namespace Helper