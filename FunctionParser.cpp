#include "FunctionParser.h"

// for debuging
#include <iostream>
void printToken(Token token);

void FunctionParser::test(vector<Token> tokens)
{

    toPostfix(tokens);
    while (!tokenQueue.empty())
    {
        printToken(tokenQueue.front());
        tokenQueue.pop();
    }
}

FunctionParser::FunctionParser()
{
    operatorPrecedence[0] = OR;
    operatorPrecedence[1] = XOR;
    operatorPrecedence[2] = AND;
    operatorPrecedence[3] = NOT;
}

vector<bool> FunctionParser::parser(vector<Token> exception)
{
    return {};
}

// shunting yard
void FunctionParser::toPostfix(vector<Token> expression)
{

    for (Token token : expression)
        insertToken(token);

    while (!tokenStack.empty())
    {
        tokenQueue.push(tokenStack.top());
        tokenStack.pop();
    }
}

void FunctionParser::insertOperator(Token token)
{
    if (tokenStack.empty())
        return tokenStack.push(token);

    while (!isGreater(token.value.at(0)))
    {
        if (tokenStack.top().value.at(0) == '(')
        {
            tokenStack.pop();
            return tokenStack.push(token);
        }
        tokenQueue.push(tokenStack.top());
        tokenStack.pop();
    }
    tokenStack.push(token);
}

void clearStack()
{
}

bool FunctionParser::isGreater(char c)
{
    if (tokenStack.empty())
        return true;

    char stackChar = tokenStack.top().value.at(0);
    if (stackChar == '(' || stackChar == ')')
        return true;

    return precedenceOf(stackChar) < precedenceOf(c);
}

uint8_t FunctionParser::precedenceOf(char c)
{
    if (c == operatorPrecedence[0])
        return 1;
    if (c == operatorPrecedence[1])
        return 2;
    if (c == operatorPrecedence[2])
        return 3;
    if (c == operatorPrecedence[3])
        return 4;

    string msg = "charecter ";
    msg += c;
    msg += " is not an operator";
    Error::makeError(Error::Type::parsing, lineIndex, msg);
    return 0xff;
}

void FunctionParser::insertToken(Token token)
{
    if (token.type == Token::Type::identifier)
        return tokenQueue.push(token);

    if (token.type != Token::Type::symbol)
        return error(token, Token::Type::symbol);

    if (token.value.size() != 1)
        return error(token, "logical operator");

    switch (token.value.at(0))
    {
    case '(':
        return tokenStack.push(token);
    case ')':
        while (!tokenStack.empty())
        {
            if (tokenStack.top().value == "(")
                return tokenStack.pop();
            tokenQueue.push(tokenStack.top());
            tokenStack.pop();
        }
        return;
    case NOT:
    case AND:
    case XOR:
    case OR:
        return insertOperator(token);
    default:
        return error(token, "logical operator");
    }
}

void FunctionParser::error(Token got, Token::Type expected) { Error::makeError(Error::Type::syntax, lineIndex, got, expected); }
void FunctionParser::error(Token got, string expected) { Error::makeError(Error::Type::syntax, lineIndex, got, expected); }

vector<string> FunctionParser::getNames(vector<Token> exception)
{
    vector<string> names;
    for (Token t : exception)
        if (t.type == Token::Type::identifier)
            names.push_back(t.value);
    names = removeDouble(names);
    return names;
}

vector<string> FunctionParser::removeDouble(vector<string> names)
{
    vector<string> result;
    for (string name : names)
        if (!strInVec(result, name))
            result.push_back(name);
    return result;
}

bool FunctionParser::strInVec(vector<string> vec, string str)
{
    for (string s : vec)
        if (s == str)
            return true;
    return false;
}

void printToken(Token token)
{
    string msg = "value: ";
    msg += token.value;
    msg += "  type: ";
    msg += (token.type == Token::Type::identifier ? "{identifier}" : "{symbol}");
    cout << msg << endl;
}