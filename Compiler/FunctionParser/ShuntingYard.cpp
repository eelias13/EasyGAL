#include "ShuntingYard.hpp"

void ShuntingYard::sortIn(stack<Token> &Stack, Token t)
{
    stack<Token> Temp;
    while (Stack.top().value() != string(1, OR))
    {
        Temp.push(Stack.top());
        Stack.pop();
    }
    Stack.push(t);
    while (!Temp.empty())
    {
        Stack.push(Temp.top());
        Temp.pop();
    }
}

stack<Token> ShuntingYard::reversePolishNotation(vector<Token> Expression)
{
    // add Parentheses for parsing
    vector<Token> m_Expression;
    m_Expression.push_back(Token(Token::Key::Parentheses, string(1, PARENTHSESE_OPEN), Expression.at(0).lineIndex()));
    for (Token t : Expression)
        m_Expression.push_back(t);
    m_Expression.push_back(Token(Token::Key::Parentheses, string(1, PARENTHSESE_CLOSE), m_Expression.at(m_Expression.size() - 1).lineIndex()));

    stack<Token> Result;
    stack<Token> Stack;
    for (Token t : m_Expression)
    {
        if (t.key() == Token::Key::Identifier)
            Result.push(t);
        else if (t.key() == Token::Key::LogicalOperator)
        {
            if (t.value() == string(1, AND))
                if (Stack.top().value() == string(1, OR))
                    sortIn(Stack, t);
                else
                    Stack.push(t);
            else if (t.value() == string(1, OR))
                if (Stack.top().value() == string(1, OR))
                    sortIn(Stack, t);
                else
                    Stack.push(t);
            else if (t.value() == string(1, XOR))
                if (Stack.top().value() == string(1, OR))
                    sortIn(Stack, t);
                else
                    Stack.push(t);
            else if (t.value() == string(1, NOT))
                if (Stack.top().value() == string(1, OR))
                    sortIn(Stack, t);
                else
                    Stack.push(t);
        }
        else if (t.key() == Token::Key::Parentheses)
            if (t.value() == string(1, PARENTHSESE_CLOSE))
                while (!Stack.empty())
                {
                    if (Stack.top().value() == string(1, PARENTHSESE_OPEN))
                    {
                        Stack.pop();
                        break;
                    }
                    Result.push(Stack.top());
                    Stack.pop();
                }
            else if (t.value() == string(1, PARENTHSESE_OPEN))
                Stack.push(t);
    }

    while (!Stack.empty())
    {
        Result.push(Stack.top());
        Stack.pop();
    }

    return Result;
}