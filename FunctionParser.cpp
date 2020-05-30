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

// shunting yard
void FunctionParser::toPostfix(vector<Token> expression)
{
    for (Token token : expression)
        // printToken(token);
        insertToken(token);

    while (!tokenStack.empty())
    {
        tokenQueue.push(tokenStack.top());
        tokenStack.pop();
    }
}

void FunctionParser::insertOperator(Token token)
{
    stack<Token> tempStack;
}

void FunctionParser::insertToken(Token token)
{
    if (token.type == Token::Type::identifier)
        return tokenQueue.push(token);

    if (token.type != Token::Type::symbol)
        return error("unexpected token type");

    switch (token.value.at(0))
    {
    case '(':
        return tokenStack.push(token);
    case ')':
        while (!tokenStack.empty())
        {
            if (tokenStack.top().value == "(")
                return tokenStack.pop();
            tokenQueue.push(token);
            tokenStack.pop();
        }
        return;
    case NOT:
    case AND:
    case OR:
    case XOR:
        return insertOperator(token);
    default:
        return error("unexpected token value: " + token.value);
    }
}

void FunctionParser::error(string msg)
{
    Error::printError(msg);
    exit(1);
}

void printToken(Token token)
{
    string msg = "value: ";
    msg += token.value;
    msg += "  type: ";
    msg += (token.type == Token::Type::identifier ? "{identifier}" : "{symbol}");
    cout << msg << endl;
}