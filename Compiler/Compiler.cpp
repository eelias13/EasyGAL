#include "Compiler.hpp"

Compiler::Compiler(vector<int> ValidPins)
{
    m_ValidPins = ValidPins;
}

void Compiler::prase(stack<Token> &Stack)
{
    if (Stack.top().key() == Token::Key::Keyword)
        if (Stack.top().value() == PIN)
            pinProcess(Stack);
        else if (Stack.top().value() == TABLE)
            tableProcess(Stack);
        else
            error("Syntax Error", "unknown keyword", Stack.top().lineIndex());
    else if (Stack.top().key() == Token::Key::Identifier)
    {
        Token Temp = Stack.top();
        Stack.pop();
        if (Stack.top().key() == Token::Key::Point)
        {
            savePop(Stack, Token::Key::dff);
            savePop(Stack, Token::Key::End);
            savePop(Stack);
            m_IsD.push_back(Temp.value());
        }
        else
        {
            Stack.push(Temp);
            functionProcess(Stack);
        }
    }
    else
        error("Syntax Error", "unknown statement", Stack.top().lineIndex());
}

vector<TableData> Compiler::compile(vector<string> code)
{
    Lexer lexer = Lexer(VALID_CHAR);
    vector<Token> TVec = lexer.lex(code);
    stack<Token> Stack = preParse(TVec);
    while (!Stack.empty())
        prase(Stack);

    return link();
}



// ------------------------ help with stack ---------------------------------------
void Compiler::check(Token T, Token::Key expected)
{
    if (T.key() != expected)
        error("Syntax Error", "unexpected key: " + T.printKey() + "  expected key is: " + TokenPrint::printKey(expected), T.lineIndex());
}

void Compiler::check(Token T, string expected)
{
    if (T.value() != expected)
        error("Syntax Error", "unexpected string: " + T.value() + "   expected key is: " + expected, T.lineIndex());
}

void Compiler::check(Token T, char expected)
{
    check(T, string(1, expected));
}

void Compiler::savePop(stack<Token> &Stack, Token::Key expected)
{
    Token Temp = Stack.top();
    Stack.pop();
    if (Stack.empty())
        error("", "EOF", Temp.lineIndex());
    check(Stack.top(), expected);
}

void Compiler::savePop(stack<Token> &Stack, string expected)
{
    Token Temp = Stack.top();
    Stack.pop();
    if (Stack.empty())
        error("", "EOF", Temp.lineIndex());
    check(Stack.top(), expected);
}

void Compiler::savePop(stack<Token> &Stack, char expected)
{
    savePop(Stack, string(1, expected));
}

void Compiler::savePop(stack<Token> &Stack)
{
    Token Temp = Stack.top();
    Stack.pop();
    if (Stack.empty())
        error("", "EOF", Temp.lineIndex());
}

// ---------------------------------------- preParse --------------------------------------
void Compiler::preParsePoint(stack<Token> &Stack, stack<Token> &Result)
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

bool Compiler::nextValid(Token t)
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

void Compiler::grouping(stack<Token> &Stack, stack<Token> &Result)
{
    Token Temp = Stack.top();
    savePop(Stack);
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
            savePop(Stack);
        }

        Result.push(Token(Token::Key::Identifier, Name, Line));
    }
    else
        Result.push(Temp);
}

stack<Token> Compiler::preParse(vector<Token> TokenVec)
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
            preParsePoint(Stack_1, Stack_2);
        else if (Stack_1.top().key() == Token::Key::Identifier)
            grouping(Stack_1, Stack_2);
        else if (Stack_1.top().key() == Token::Key::None)
            error("Syntax Error", Stack_1.top().value() + " is not definde", Stack_1.top().lineIndex());
        else if (Stack_1.top().key() == Token::Key::Equal)
        {
            Token Temp = Stack_1.top();
            savePop(Stack_1);
            if (Stack_1.top().value() == string(1, ARROW_HED))
            {
                Stack_2.push(Token(Token::Key::Arrow, ARROW, Stack_1.top().lineIndex()));
                savePop(Stack_1);
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

// -------------------------- usefull functions ------------------------------
vector<bool> Compiler::getBoolVec(stack<Token> &Stack)
{
    vector<bool> Result;
    while (Stack.top().key() == Token::Key::Boolean)
    {
        Result.push_back(Stack.top().value() == string(1, ONE));
        Stack.pop();
    }
    return Result;
}

vector<string> Compiler::getIdentifierList(stack<Token> &Stack)
{
    vector<string> Result;
    while (true)
    {
        if (Stack.top().key() == Token::Key::Identifier)
        {
            Result.push_back(Stack.top().value());
            savePop(Stack);
            if (Stack.top().key() == Token::Key::Comma)
                savePop(Stack);
            else
                break;
        }
        else
            break;
    }
    return Result;
}

vector<Token> Compiler::getExpresion(stack<Token> &Stack)
{
    vector<Token> Result;
    while (Stack.top().key() == Token::Key::Identifier || Stack.top().key() == Token::Key::LogicalOperator || Stack.top().key() == Token::Key::Parentheses)
    {
        Result.push_back(Stack.top());
        savePop(Stack);
    }
    return Result;
}

bool Compiler::pinIsValide(int Pin)
{
    for (int i : m_ValidPins)
        if (Pin == i)
            return true;
    return false;
}

// ----------------------------process functions -------------------------------

void Compiler::pinProcess(stack<Token> &Stack)
{
    savePop(Stack);
    int Num = Helper::str2Int(Stack.top().value());
    if (!pinIsValide(Num))
        error("", "invalid pin " + Num, Stack.top().lineIndex());

    savePop(Stack, Token::Key::Equal);

    savePop(Stack, Token::Key::Identifier);
    string Name = Stack.top().value();

    savePop(Stack, Token::Key::End);
    Stack.pop();

    m_Alias.push_back(pair<string, int>(Name, Num));
}

void Compiler::tableProcess(stack<Token> &Stack)
{
    bool IsFill = false;
    bool IsCount = false;
    bool Fill;

    savePop(Stack, PARENTHSESE_OPEN);
    savePop(Stack, Token::Key::Identifier);

    vector<string> InNames = getIdentifierList(Stack);

    check(Stack.top(), Token::Key::Arrow);
    savePop(Stack, Token::Key::Identifier);
    vector<string> OutNames = getIdentifierList(Stack);

    check(Stack.top(), PARENTHSESE_CLOSE);
    savePop(Stack);

    if (Stack.top().value() == string(1, POINT))
    {
        savePop(Stack);
        if (Stack.top().value() == FILL)
        {
            savePop(Stack);
            IsFill = true;
            check(Stack.top(), PARENTHSESE_OPEN);
            savePop(Stack, Token::Key::Boolean);
            Fill = Stack.top().value() == string(1, ONE);
            savePop(Stack, PARENTHSESE_CLOSE);
            savePop(Stack);
        }
        else
        {
            check(Stack.top(), COUNT);
            savePop(Stack);
            IsCount = true;
        }
    }

    check(Stack.top(), CURLYBRACES_OPEN);
    savePop(Stack);

    vector<bool> BoolVec = getBoolVec(Stack);

    check(Stack.top(), CURLYBRACES_CLOSE);
    Stack.pop();

    if (IsFill)
        m_Tables.push_back(Table(InNames, OutNames, BoolVec, Fill));

    else
    {
        if (IsCount)
            m_Tables.push_back(Table(InNames, OutNames, BoolVec, Table::Type::Count));

        else
            m_Tables.push_back(Table(InNames, OutNames, BoolVec, Table::Type::None));
    }
}

void Compiler::functionProcess(stack<Token> &Stack)
{
    Token First = Stack.top();
    savePop(Stack, Token::Key::Equal);
    savePop(Stack);
    vector<Token> Expresion = getExpresion(Stack);

    vector<string> Names = Helper::getNames(Expresion);
    vector<bool> BoolTable = m_FP.parse(Expresion);
    m_Tables.push_back(Table(vector<string>{First.value()}, Names, BoolTable, Table::Type::Count));

    check(Stack.top(), Token::Key::End);
    Stack.pop();
}