#pragma once
#include <iostream>
#include <vector>
#include "Symbols.hpp"
#include "Token.hpp"
#include "Helper.cpp"
#include "Pair.hpp"
using namespace std;
namespace Lexer
{
vector<string> spit(vector<string>);
vector<string> splitBy(vector<string>, char);
vector<Pair> tokenize(vector<string>);
bool isNum(string);
bool charIsNum(char);
} // namespace Lexer