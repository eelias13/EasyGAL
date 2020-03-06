#include "FunctionParser.hpp"

FunctionParser::FunctionParser() {}

vector<bool> FunctionParser::parse(vector<Token> Expression)
{
    vector<Token> Identifier = getNames(Expression);
    vector<vector<bool>> Vec2D = Helper::generateTable2D(Identifier.size());
    stack<Token> Stack = ShuntingYard::reversePolishNotation(Expression);

    Node Tree = Node(Stack);
    vector<bool> Result;

    LookUpTable LookUp;
    LookUp.setKey(Identifier);

    for (vector<bool> BoolVec : Vec2D)
    {
        LookUp.setValue(BoolVec);
        Result.push_back(Tree.eval(LookUp));
    }

    return Result;
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