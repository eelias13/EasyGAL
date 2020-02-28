#pragma once
#include <string>
#include <vector>
#include <utility>
#include "Token.hpp"
#include "../Symbol.hpp"

using namespace std;

class Lexer
{
private:
    vector<pair<string, int>> initLines(vector<string>);

    vector<pair<string, int>> splitByStr(pair<string, int>, string);
    vector<pair<string, int>> splitByChar(pair<string, int>, char);

    bool isChar(string);
    bool isNum(string);
    bool isBool(string);

    void validatCharInit(string);
    bool validatChar(char);
    bool validatString(string);

    vector<Token> tokenize(vector<pair<string, int>>);
    Token tokenizeKeyword(pair<string, int>);
    vector<pair<string, int>> split(vector<pair<string, int>>);

public:
    Lexer(string ValidCahr);
    vector<Token> lex(vector<string>);

private:
    string m_ValidCahr;
};
