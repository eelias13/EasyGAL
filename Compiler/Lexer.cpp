#include "Lexer.hpp"

int main()
{
    vector<string> code;
    code.push_back("pin 22 = iPin;");
    code.push_back("pin 3 = oPin1;");
    code.push_back("pin 4 = oPin2;");
    code.push_back("iPin = oPin1 & oPin2;");

    Lexer lexer = Lexer("AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZzÄäÖöÜü-_$");
    printTokens(lexer.lex(code));
}

Lexer::Lexer(string ValidCahr)
{
    Lexer::validatCharInit(ValidCahr);
    Lexer::m_ValidCahr = ValidCahr;
}

vector<Token> Lexer::lex(vector<string> StrVec)
{
    vector<pair<string, int>> PairVec = Lexer::initLines(StrVec);
    PairVec = Lexer::split(PairVec);
    vector<Token> Result = Lexer::tokenize(PairVec);
    Result = Lexer::removeComments(Result);
    return Result;
}

vector<Token> Lexer::removeComments(vector<Token> TokVec)
{
    return TokVec;
}

vector<Token> Lexer::tokenize(vector<pair<string, int>> PairVec)
{
    vector<Token> Result;
    for (pair<string, int> p : PairVec)
    {
        Token Temp = Lexer::tokenizeKeyword(p);
        if (Temp.isKey(Token::Key::None))
            if (Lexer::isBool(Temp.value()))
                Temp.key(Token::Key::Boolean);
            else if (Lexer::isNum(Temp.value()))
                Temp.key(Token::Key::Number);
            else if (Lexer::isChar(Temp.value()))
                Temp.key(Token::Key::Identifier);
        Result.push_back(Temp);
    }
    return Result;
}

Token Lexer::tokenizeKeyword(pair<string, int> p)
{
    if (p.first.length() == 1)
    {
        switch (p.first.at(0))
        {
        case PARENTHSESE_CLOSE:
        case PARENTHSESE_OPEN:
        case CURLYBRACES_CLOSE:
        case CURLYBRACES_OPEN:
            return Token(Token::Key::Parentheses, p.first, p.second);
        case OR:
        case AND:
        case NOT:
        case XOR:
            return Token(Token::Key::LogicalOperator, p.first, p.second);
        case SPACE:
        case TAB:
        case NEWL:
            return Token(Token::Key::Space, p.first, p.second);
        case ZERO:
        case ONE:
            return Token(Token::Key::Boolean, p.first, p.second);
        case END:
            return Token(Token::Key::End, p.first, p.second);
        case POINT:
            return Token(Token::Key::Point, p.first, p.second);
        case COMMA:
            return Token(Token::Key::Comma, p.first, p.second);
        case EQUAL:
            return Token(Token::Key::Equal, p.first, p.second);
        default:
            return Token(Token::Key::None, p.first, p.second);
        }
    }
    else
    {
        if (SINGLE_COMMENT == p.first || BEGIN_COMMENT == p.first || END_COMMENT == p.first)
            return Token(Token::Key::Comment, p.first, p.second);
        if (PIN == p.first || TABLE == p.first)
            return Token(Token::Key::Keyword, p.first, p.second);
        if (FILL == p.first || COUNT == p.first)
            return Token(Token::Key::ExtraFunction, p.first, p.second);
        if (ARROW == p.first)
            return Token(Token::Key::Arrow, p.first, p.second);
        return Token(Token::Key::None, p.first, p.second);
    }
}

vector<pair<string, int>> Lexer::split(vector<pair<string, int>> PairVec)
{
    vector<string> StrVec = {PIN, TABLE, FILL, COUNT, ARROW, SINGLE_COMMENT, BEGIN_COMMENT, END_COMMENT};
    for (string str : StrVec)
    {
        vector<pair<string, int>> Temp;
        for (pair<string, int> p : PairVec)
            for (pair<string, int> p2 : Lexer::splitByStr(p, str))
                if (!p2.first.empty())
                    Temp.push_back(p2);
        PairVec = Temp;
    }

    vector<char> CharVec = {POINT, EQUAL, COMMA, END, AND, OR, XOR, NOT, ZERO, ONE, CURLYBRACES_OPEN,
                            CURLYBRACES_CLOSE, PARENTHSESE_OPEN, PARENTHSESE_CLOSE, SPACE, TAB, NEWL};
    for (char c : CharVec)
    {
        vector<pair<string, int>> Temp;
        for (pair<string, int> p : PairVec)
            for (pair<string, int> p2 : Lexer::splitByChar(p, c))
                if (!p2.first.empty())
                    Temp.push_back(p2);
        PairVec = Temp;
    }
    return PairVec;
}

vector<pair<string, int>> Lexer::initLines(vector<string> VecIn)
{
    vector<pair<string, int>> Result;
    for (int i = 0; i < VecIn.size(); i++)
        if (!VecIn.at(i).empty())
            Result.push_back(pair<string, int>(VecIn.at(i), i));
    return Result;
}

vector<pair<string, int>> Lexer::splitByStr(pair<string, int> p, string Split)
{
    vector<pair<string, int>> Result;
    string Temp = "";
    for (int i = 0; i < p.first.size(); i++)
    {
        if (Temp == Split)
        {
            Result.push_back(pair<string, int>(Temp, p.second));
            Temp = "";
            Temp += p.first.at(i);
        }
        else
            Temp += p.first.at(i);
    }
    Result.push_back(pair<string, int>(Temp, p.second));

    return Result;
}

vector<pair<string, int>> Lexer::splitByChar(pair<string, int> p, char Split)
{
    vector<pair<string, int>> Result;
    string Temp = "";
    for (int i = 0; i < p.first.size(); i++)
    {
        if (p.first.at(i) == Split)
        {
            Result.push_back(pair<string, int>(Temp, p.second));
            Temp = "";
            Result.push_back(pair<string, int>(string(1, p.first.at(i)), p.second));
        }
        else
            Temp += p.first.at(i);
    }
    Result.push_back(pair<string, int>(Temp, p.second));
    return Result;
}

bool Lexer::isChar(string Str)
{
    for (char c : Str)
    {
        bool Flag = false;
        for (char vc : Lexer::m_ValidCahr)
        {
            if (vc == c)
            {
                Flag == true;
                break;
            }
        }
        if (!Flag)
            return false;
    }
    return true;
}

bool Lexer::isNum(string Str)
{
    for (char c : Str)
        switch (c)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            break;
        default:
            return false;
        }
    return true;
}

bool Lexer::isBool(string Str)
{
    for (char c : Str)
        if (c != ZERO && c != ONE)
            return false;
    return true;
}

void Lexer::validatCharInit(string ValidCahr)
{
    for (char c : ValidCahr)
        switch (c)
        {
        case PARENTHSESE_CLOSE:
        case PARENTHSESE_OPEN:
        case CURLYBRACES_CLOSE:
        case CURLYBRACES_OPEN:
        case OR:
        case AND:
        case NOT:
        case XOR:
        case SPACE:
        case TAB:
        case NEWL:
        case END:
        case POINT:
        case COMMA:
        case EQUAL:
            ERROR("faild to init Lexer \n" + string(1, c) + " can not be valid");
            break;
        default:
            break;
        }
}

#ifdef _Debug
#include <iostream>
void printTokens(vector<Token> Tokens)
{
    for (Token t : Tokens)
        cout << "key: " << t.printKey() << '\t' << "value: " << t.value() << endl;
}

void printPair(vector<pair<string, int>> PairVec, bool line)
{
    for (pair<string, int> p : PairVec)
        if (line)
            cout << p.first << '\t' << p.second << endl;
        else
            cout << p.first << endl;
}
#endif