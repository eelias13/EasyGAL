#include "FunctionParser.hpp"

FunctionParser::FunctionParser() {}

vector<bool> FunctionParser::parse(vector<Token> Expression)
{
    vector<Token> Identifier = getNames(Expression);
    vector<vector<bool>> Vec2D = Helper::generateTable2D(Identifier.size());
    vector<bool> Result;

    LookUpTable LookUp;
    LookUp.setKey(Identifier);

    for (vector<bool> BoolVec : Vec2D)
    {
        LookUp.setValue(BoolVec);
        string exp = insert(Expression, LookUp);
        if (Parser::parse(exp) == ONE)
            Result.push_back(true);
        else if (Parser::parse(exp) == ZERO)
            Result.push_back(false);
        else
            error("", "can not parse expresion", -1);
    }

    return Result;
}

string FunctionParser::insert(vector<Token> Expression, LookUpTable LookUp)
{
    string out = string(1, PARENTHSESE_OPEN);
    for (Token t : Expression)
        if (t.key() == Token::Key::Identifier)
            if (LookUp.at(t))
                out += ONE;
            else
                out += ZERO;
        else
            out += t.value();

    out += PARENTHSESE_CLOSE;
    return out;
}

vector<Token> FunctionParser::getNames(vector<Token> Expression)
{
    vector<Token> Identifier;

    for (Token t : Expression)
        if (t.key() == Token::Key::Identifier)
            if (!isInVec(t, Identifier))
                Identifier.push_back(t);

    return Identifier;
}

bool FunctionParser::isInVec(Token t, vector<Token> TokenVec)
{
    if (TokenVec.empty())
        return false;

    for (Token i : TokenVec)
        if (t.value() == i.value())
            return true;

    return false;
}