#pragma once
#include <stack>
#include <string>
#include "../../Helper.hpp"
#include "../Lexer/Token.hpp"
#include "../StackHelper/StackHelper.hpp"
#include "../Symbol.hpp"

using namespace std;

class PreCompiler
{
private:
    void grouping(stack<Token> &, stack<Token> &);
    void preCompilerPoint(stack<Token> &, stack<Token> &);
    bool nextValid(Token);

public:
    PreCompiler();
    stack<Token> compile(vector<Token> TokenVec);
};
