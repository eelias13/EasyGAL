#pragma once
#include <vector>
#include <stack>
#include <string>

#include "LookUpTable.hpp"
#include "../Lexer/Token.hpp"
#include "../../Helper.hpp"
#include "../Symbol.hpp"

#include "Parser/Parser.hpp"

using namespace std;

class FunctionParser
{
private:
    bool isInVec(Token, vector<Token>);
    string insert(vector<Token>, LookUpTable);

public:
    FunctionParser();
    vector<bool> parse(vector<Token>);
    vector<Token> getNames(vector<Token>);
};
