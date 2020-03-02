#include "PreCompiler.hpp"

PreCompiler::PreCompiler()
{
}

void PreCompiler::preCompilerPoint(stack<Token> &Stack, stack<Token> &Result)
{
    Token Temp = Stack.top();
    Stack.pop();
    if (Stack.top().key() == Token::Key::dff || Stack.top().key() == Token::Key::ExtraFunction)
    {
        Result.push(Temp);
        Result.push(Stack.top());
        Stack.pop();
    }
    else
        error("Syntax Error",
              "unexpected key: " + Stack.top().printKey() + "  expected key is: " + TokenPrint::printKey(Token::Key::dff) + " or " + TokenPrint::printKey(Token::Key::ExtraFunction),
              Stack.top().lineIndex());
}

bool PreCompiler::nextValid(Token t)
{
    switch (t.key())
    {
    case Token::Key::dff:
    case Token::Key::ExtraFunction:
    case Token::Key::Keyword:
    case Token::Key::Number:
    case Token::Key::Boolean:
    case Token::Key::Identifier:
        return true;
    }
    return false;
}

void PreCompiler::grouping(stack<Token> &Stack, stack<Token> &Result)
{
    Token Temp = Stack.top();
    StackHelper::savePop(Stack);
    if (nextValid(Stack.top()))
    {
        Stack.push(Temp);
        string Name = "";
        int Line = Stack.top().lineIndex();

        while (nextValid(Stack.top()))
        {
            if (Line != Stack.top().lineIndex())
                break;
            Name += Stack.top().value();
            StackHelper::savePop(Stack);
        }

        Result.push(Token(Token::Key::Identifier, Name, Line));
    }
    else
        Result.push(Temp);
}

#include <iostream>
stack<Token> PreCompiler::compile(vector<Token> TokenVec)
{
    stack<Token> Stack_1;
    for (int i = TokenVec.size() - 1; i >= 0; i--)
        Stack_1.push(TokenVec.at(i));

    stack<Token> Stack_2;
    int CommentOneLine = false;
    bool Comment = false;

    while (!Stack_1.empty())
    {
        if (CommentOneLine)
        {
            if (Stack_1.top().value() == string(1, '\n'))
                CommentOneLine = false;
            Stack_1.pop();
        }
        else if (Comment)
        {
            if (Stack_1.top().value() == END_COMMENT)
                CommentOneLine = false;
            Stack_1.pop();
        }
        else if (Stack_1.top().key() == Token::Key::Comment)
        {
            if (Stack_1.top().value() == SINGLE_COMMENT)
                CommentOneLine = true;
            else if (Stack_1.top().value() == BEGIN_COMMENT)
                Comment = true;
            else
                error("Syntax Error", "there must be an opening comment before a closing one ", Stack_1.top().lineIndex());
        }

        else if (Stack_1.top().key() == Token::Key::Space)
            Stack_1.pop();
        else if (Stack_1.top().key() == Token::Key::Keyword)
            grouping(Stack_1, Stack_2);
        else if (Stack_1.top().key() == Token::Key::Point)
            preCompilerPoint(Stack_1, Stack_2);
        else if (Stack_1.top().key() == Token::Key::Identifier)
            grouping(Stack_1, Stack_2);
        else if (Stack_1.top().key() == Token::Key::None)
            error("Syntax Error", Stack_1.top().value() + " is not definde", Stack_1.top().lineIndex());
        else if (Stack_1.top().key() == Token::Key::Equal)
        {
            Token Temp = Stack_1.top();
            StackHelper::savePop(Stack_1);
            if (Stack_1.top().value() == string(1, ARROW_HED))
            {
                Stack_2.push(Token(Token::Key::Arrow, ARROW, Stack_1.top().lineIndex()));
                StackHelper::savePop(Stack_1);
            }
            else
                Stack_2.push(Temp);
        }
        else
        {
            Stack_2.push(Stack_1.top());
            Stack_1.pop();
        }
    }

    while (!Stack_2.empty())
    {
        Stack_1.push(Stack_2.top());
        Stack_2.pop();
    }

    return Stack_1;
}
