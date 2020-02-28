#pragma once
#include <string>

using namespace std;

class Token
{

public:
    enum class Key
    {
        Keyword,         // "pin", "table"
        Number,          // "0"-"9"
        Identifier,      // valid chars
        Equal,           // "="
        End,             // ";"
        Parentheses,     // "(", ")", "{", "}"
        ExtraFunction,   // "fill", "count"
        LogicalOperator, // "&","|","!","?"
        Arrow,           // "=>"
        Boolean,         // "0", "1"
        Comma,           // ","
        Point,           // "."
        dff,             // "DFF"
        Comment,         // "//", "/*", "*/"
        Space,           // " ", "\t" , "\n"
        None             //
    };

    Token(Key, string, int);

    Key key();
    void key(Key);
    string value();
    int lineIndex();
    bool isKey(Key);
    string printKey();

private:
    Key m_Key;
    string m_Value;
    int m_LineIndex;
};

namespace TokenPrint
{
string printKey(Token::Key);
}