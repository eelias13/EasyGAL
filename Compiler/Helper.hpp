#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include "Token.hpp"
#include "Pair.hpp"
#include "Symbols.hpp"

using namespace std;

void ERROR(string);

namespace Helper
{
void print(string);
string getTokenName(Token);
void printPare(vector<Pair>);
void printStrVec(vector<string>);
} // namespace Helper
