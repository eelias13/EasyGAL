#pragma once
#include <vector>
#include <stack>
#include <string>

#include "../Symbol.hpp"
#include "../Lexer/Token.hpp"

using namespace std;

namespace ShuntingYard
{
void sortIn(stack<Token> &, Token);
stack<Token> reversePolishNotation(vector<Token>);
} // namespace ShuntingYard
