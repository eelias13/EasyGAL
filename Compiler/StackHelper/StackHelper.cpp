#include "StackHelper.hpp"

void StackHelper::check(Token T, Token::Key expected)
{
    if (T.key() != expected)
        error("Syntax Error", "unexpected key: " + T.printKey() + "  expected key is: " + TokenPrint::printKey(expected), T.lineIndex());
}

void StackHelper::check(Token T, string expected)
{
    if (T.value() != expected)
        error("Syntax Error", "unexpected string: " + T.value() + "   expected key is: " + expected, T.lineIndex());
}

void StackHelper::check(Token T, char expected)
{
    check(T, string(1, expected));
}

void StackHelper::savePop(stack<Token> &Stack, Token::Key expected)
{
    Token Temp = Stack.top();
    Stack.pop();
    if (Stack.empty())
        error("", "EOF", Temp.lineIndex());
    check(Stack.top(), expected);
}

void StackHelper::savePop(stack<Token> &Stack, string expected)
{
    Token Temp = Stack.top();
    Stack.pop();
    if (Stack.empty())
        error("", "EOF", Temp.lineIndex());
    check(Stack.top(), expected);
}

void StackHelper::savePop(stack<Token> &Stack, char expected)
{
    savePop(Stack, string(1, expected));
}

void StackHelper::savePop(stack<Token> &Stack)
{
    Token Temp = Stack.top();
    Stack.pop();
    if (Stack.empty())
        error("", "EOF", Temp.lineIndex());
}