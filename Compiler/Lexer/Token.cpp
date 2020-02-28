#include "Token.hpp"

Token::Token(Key Key, string Value, int LineIndex)
{
    m_Key = Key;
    m_Value = Value;
    m_LineIndex = LineIndex;
}

string Token::printKey()
{
    return TokenPrint::printKey(m_Key);
}

string TokenPrint::printKey(Token::Key key)
{
    switch (key)
    {
    case Token::Key::Keyword:
        return "Keyword";
    case Token::Key::Number:
        return "Number";
    case Token::Key::Identifier:
        return "Identifier";
    case Token::Key::Equal:
        return "Equal";
    case Token::Key::End:
        return "End";
    case Token::Key::Parentheses:
        return "Parentheses";
    case Token::Key::ExtraFunction:
        return "ExtraFunction";
    case Token::Key::LogicalOperator:
        return "LogicalOperator";
    case Token::Key::Arrow:
        return "Arrow";
    case Token::Key::Boolean:
        return "Boolean";
    case Token::Key::Comma:
        return "Comma";
    case Token::Key::Point:
        return "Point";
    case Token::Key::None:
        return "None";
    case Token::Key::Comment:
        return "Comment";
    case Token::Key::Space:
        return "Space";
    default:
        return "not defined in printKey()";
    }
}

Token::Key Token::key()
{
    return Token::m_Key;
}

void Token::key(Token::Key key)
{
    Token::m_Key = key;
}

string Token::value()
{
    return Token::m_Value;
}

int Token::lineIndex()
{
    return Token::m_LineIndex;
}

bool Token::isKey(Token::Key key)
{
    return key == Token::m_Key;
}