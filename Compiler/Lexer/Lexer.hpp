#pragma once
#include <iostream>
#include <vector>
#include "Symbols.hpp"
#include "Token.hpp"
#include "Helper.cpp"
#include "Pair.hpp"

namespace Lexer
{
std::vector<std::string> spit(std::vector<std::string>);
std::vector<std::string> splitBy(std::vector<std::string>, char);
std::vector<Pair> tokenize(std::vector<std::string>);
bool isNum(std::string);
bool charIsNum(char);
} // namespace Lexer