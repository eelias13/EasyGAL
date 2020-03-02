#include "Lexer.hpp"

Lexer::Lexer() {}

Lexer::Lexer(string ValidCahr)
{
    Lexer::validatCharInit(ValidCahr);
    Lexer::m_ValidCahr = ValidCahr;
}

vector<Token> Lexer::lex(vector<string> StrVec)
{
    vector<pair<string, int>> PairVec = Lexer::initLines(StrVec);
    int len;
    do
    {
        len = PairVec.size();
        PairVec = Lexer::split(PairVec);
    } while (len != PairVec.size());

    vector<Token> Result = Lexer::tokenize(PairVec);
    return Result;
}

bool Lexer::validatChar(char c)
{
    for (char x : Lexer::m_ValidCahr)
        if (x == c)
            return true;
    return false;
}

bool Lexer::validatString(string str)
{
    for (char c : str)
        if (!Lexer::validatChar(c))
            return false;
    return true;
}

vector<Token> Lexer::tokenize(vector<pair<string, int>> PairVec)
{
    vector<Token> Result;
    for (pair<string, int> P : PairVec)
    {
        Token Temp = Lexer::tokenizeKeyword(P);
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

Token Lexer::tokenizeKeyword(pair<string, int> P)
{
    if (P.first.length() == 1)
    {
        switch (P.first.at(0))
        {
        case PARENTHSESE_CLOSE:
        case PARENTHSESE_OPEN:
        case CURLYBRACES_CLOSE:
        case CURLYBRACES_OPEN:
            return Token(Token::Key::Parentheses, P.first, P.second);
        case OR:
        case AND:
        case NOT:
        case XOR:
            return Token(Token::Key::LogicalOperator, P.first, P.second);
        case SPACE:
        case TAB:
        case NEWL:
            return Token(Token::Key::Space, P.first, P.second);
        case ZERO:
        case ONE:
            return Token(Token::Key::Boolean, P.first, P.second);
        case END:
            return Token(Token::Key::End, P.first, P.second);
        case POINT:
            return Token(Token::Key::Point, P.first, P.second);
        case COMMA:
            return Token(Token::Key::Comma, P.first, P.second);
        case EQUAL:
            return Token(Token::Key::Equal, P.first, P.second);
        default:
            if (Lexer::validatChar(P.first.at(0)))
                return Token(Token::Key::Identifier, P.first, P.second);
            else
                return Token(Token::Key::None, P.first, P.second);
        }
    }
    else
    {
        if (SINGLE_COMMENT == P.first || BEGIN_COMMENT == P.first || END_COMMENT == P.first)
            return Token(Token::Key::Comment, P.first, P.second);
        if (PIN == P.first || TABLE == P.first)
            return Token(Token::Key::Keyword, P.first, P.second);
        if (FILL == P.first || COUNT == P.first)
            return Token(Token::Key::ExtraFunction, P.first, P.second);
        if (ARROW == P.first)
            return Token(Token::Key::Arrow, P.first, P.second);
        if (DFF == P.first)
            return Token(Token::Key::dff, P.first, P.second);

        if (Lexer::validatString(P.first))
            return Token(Token::Key::Identifier, P.first, P.second);
        else
            return Token(Token::Key::None, P.first, P.second);
    }
}

vector<pair<string, int>> Lexer::split(vector<pair<string, int>> PairVec)
{
    vector<string> StrVec = {PIN, TABLE, FILL, COUNT, ARROW, SINGLE_COMMENT, BEGIN_COMMENT, END_COMMENT, DFF};
    for (string str : StrVec)
    {
        vector<pair<string, int>> Temp;
        for (pair<string, int> P : PairVec)
            for (pair<string, int> P2 : Lexer::splitByStr(P, str))
                if (!P2.first.empty())
                    Temp.push_back(P2);
        PairVec = Temp;
    }

    vector<char> CharVec = {POINT, EQUAL, COMMA, END, AND, OR, XOR, NOT, ZERO, ONE, CURLYBRACES_OPEN,
                            CURLYBRACES_CLOSE, PARENTHSESE_OPEN, PARENTHSESE_CLOSE, SPACE, TAB, NEWL};
    for (char C : CharVec)
    {
        vector<pair<string, int>> Temp;
        for (pair<string, int> P : PairVec)
            for (pair<string, int> P2 : Lexer::splitByChar(P, C))
                if (!P2.first.empty())
                    Temp.push_back(P2);
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

vector<pair<string, int>> Lexer::splitByChar(pair<string, int> P, char Split)
{
    vector<pair<string, int>> Result;
    string Temp = "";
    for (int i = 0; i < P.first.size(); i++)
    {
        if (P.first.at(i) == Split)
        {
            Result.push_back(pair<string, int>(Temp, P.second));
            Temp = "";
            Result.push_back(pair<string, int>(string(1, P.first.at(i)), P.second));
        }
        else
            Temp += P.first.at(i);
    }
    Result.push_back(pair<string, int>(Temp, P.second));
    return Result;
}

bool Lexer::isChar(string Str)
{
    for (char C : Str)
    {
        bool Flag = false;
        for (char VC : Lexer::m_ValidCahr)
        {
            if (VC == C)
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
    for (char C : Str)
        switch (C)
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
    for (char C : ValidCahr)
        switch (C)
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
            //ERROR("faild to init Lexer \n" + string(1, c) + " can not be valid");
            break;
        default:
            break;
        }
}
