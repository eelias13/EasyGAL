#include "Compiler.hpp"

Compiler::Compiler(vector<int> ValidPins)
{
    m_ValidPins = ValidPins;
    m_FP = FunctionParser();
}

TablesAndNames Compiler::compile(stack<Token> Stack)
{
    while (!Stack.empty())
        prase(Stack);

    TablesAndNames Result;
    Result.Tables = m_Tables;
    Result.IsD = m_IsD;
    Result.Alias = m_Alias;

    return Result;
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
            StackHelper::savePop(Stack, Token::Key::dff);
            StackHelper::savePop(Stack, Token::Key::End);
            StackHelper::savePop(Stack);
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

// -------------------------- usefull functions ------------------------------
vector<string> Compiler::getNames(vector<Token> TokenVec)
{
    vector<string> Result;
    for (Token t : TokenVec)
        if (t.key() == Token::Key::Identifier)
            if (!Helper::inList(t.value(), Result))
                Result.push_back(t.value());
    return Result;
}

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
            StackHelper::savePop(Stack);
            if (Stack.top().key() == Token::Key::Comma)
                StackHelper::savePop(Stack);
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
        StackHelper::savePop(Stack);
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
    StackHelper::savePop(Stack);
    int Num = Helper::str2Int(Stack.top().value());
    if (!pinIsValide(Num))
        error("", "invalid pin " + Num, Stack.top().lineIndex());

    StackHelper::savePop(Stack, Token::Key::Equal);

    StackHelper::savePop(Stack, Token::Key::Identifier);
    string Name = Stack.top().value();

    StackHelper::savePop(Stack, Token::Key::End);
    Stack.pop();

    m_Alias.push_back(pair<string, int>(Name, Num));
}

void Compiler::tableProcess(stack<Token> &Stack)
{
    bool IsFill = false;
    bool IsCount = false;
    bool Fill;

    StackHelper::savePop(Stack, PARENTHSESE_OPEN);
    StackHelper::savePop(Stack, Token::Key::Identifier);

    vector<string> InNames = getIdentifierList(Stack);

    StackHelper::check(Stack.top(), Token::Key::Arrow);
    StackHelper::savePop(Stack, Token::Key::Identifier);
    vector<string> OutNames = getIdentifierList(Stack);

    StackHelper::check(Stack.top(), PARENTHSESE_CLOSE);
    StackHelper::savePop(Stack);

    if (Stack.top().value() == string(1, POINT))
    {
        StackHelper::savePop(Stack);
        if (Stack.top().value() == FILL)
        {
            StackHelper::savePop(Stack);
            IsFill = true;
            StackHelper::check(Stack.top(), PARENTHSESE_OPEN);
            StackHelper::savePop(Stack, Token::Key::Boolean);
            Fill = Stack.top().value() == string(1, ONE);
            StackHelper::savePop(Stack, PARENTHSESE_CLOSE);
            StackHelper::savePop(Stack);
        }
        else
        {
            StackHelper::check(Stack.top(), COUNT);
            StackHelper::savePop(Stack);
            IsCount = true;
        }
    }

    StackHelper::check(Stack.top(), CURLYBRACES_OPEN);
    StackHelper::savePop(Stack);

    vector<bool> BoolVec = getBoolVec(Stack);

    StackHelper::check(Stack.top(), CURLYBRACES_CLOSE);
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
    StackHelper::savePop(Stack, Token::Key::Equal);
    StackHelper::savePop(Stack);
    vector<Token> Expresion = getExpresion(Stack);

    vector<string> Names = getNames(Expresion);
    vector<bool> BoolTable = m_FP.parse(Expresion);
    m_Tables.push_back(Table(vector<string>{First.value()}, Names, BoolTable, Table::Type::Count));

    StackHelper::check(Stack.top(), Token::Key::End);
    Stack.pop();
}