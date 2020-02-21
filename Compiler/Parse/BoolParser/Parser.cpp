#include "Parser.hpp"

char Parser::parse(string exp)
{
    if (exp.empty())
        ERROR("exp can not be null");

    // checks for valid characters and right structure
    exp = Preproces::preProcessing(exp);

    string outStr = Parser::parseRecursiv(exp);
    if (outStr.length() != 1)
        ERROR("can not parse expresion");
    char out = outStr.at(0);
    if (out == ZERO || out == ONE)
        return out;
    else
        ERROR("can not parse expresion");
    return ' ';
}

string Parser::parseRecursiv(string exp)
{
    if (exp.length() == 1)
        return exp;
    int len;

    len = exp.length();
    exp = Parentheses::simplify(exp);
    if (exp.length() != len)
        return Parser::parseRecursiv(exp);

    len = exp.length();
    exp = Not::simplify(exp);
    if (exp.length() != len)
        return Parser::parseRecursiv(exp);

    len = exp.length();
    exp = And::simplify(exp);
    if (exp.length() != len)
        return Parser::parseRecursiv(exp);

    len = exp.length();
    exp = Or::simplify(exp);
    if (exp.length() != len)
        return Parser::parseRecursiv(exp);

    len = exp.length();
    exp = Xor::simplify(exp);
    if (exp.length() != len)
        return Parser::parseRecursiv(exp);
    return Parser::parseRecursiv(exp);
}