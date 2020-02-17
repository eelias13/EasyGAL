#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include "Token.hpp"
#include "Pair.hpp"
#include "Symbols.hpp"

using namespace std;

namespace Helper
{
void print(std::string);
std::string getTokenName(Token);
void printPare(std::vector<Pair>);
void printStrVec(std::vector<std::string>);
} // namespace Helper
