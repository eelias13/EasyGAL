#include "Token.hpp"

Token::Token(Key Key, string Value, int LineIndex)
{
    m_Key = Key;
    m_Value = Value;
    m_LineIndex = LineIndex;
}

#ifdef _Debug
string Token::printKey()
{
    switch (m_Key)
    {
    case Key::Keyword:
        return "Keyword";
    case Key::Number:
        return "Number";
    case Key::Identifier:
        return "Identifier";
    case Key::Equal:
        return "Equal";
    case Key::End:
        return "End";
    case Key::Parentheses:
        return "Parentheses";
    case Key::ExtraFunction:
        return "ExtraFunction";
    case Key::LogicalOperator:
        return "LogicalOperator";
    case Key::Arrow:
        return "Arrow";
    case Key::Boolean:
        return "Boolean";
    case Key::Comma:
        return "Comma";
    case Key::Point:
        return "Point";
    case Key::None:
        return "None";
    case Key::Comment:
        return "Comment";
    case Key::Space:
        return "Space";
    default:
        return "not defined in printKey()";
    }
}
#endif
