#pragma once
#include <stack>
#include <string>
#include "../../Helper.hpp"
#include "../Lexer/Token.hpp"

using namespace std;

namespace StackHelper
{
void check(Token, Token::Key);
void check(Token, string);
void check(Token, char);
void savePop(stack<Token> &, Token::Key);
void savePop(stack<Token> &, string);
void savePop(stack<Token> &, char);
void savePop(stack<Token> &);
} // namespace StackHelper
