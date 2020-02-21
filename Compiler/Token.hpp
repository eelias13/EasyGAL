#pragma once
#include <string>
#define _Debug

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
        Comment,         // "//", "/*", "*/"
        Space,           // " ", "\t" , "\n"
        None             //
    };

    Token(Key, string, int);

    Key key() { return m_Key; }
    void key(Key key) { m_Key = key; }
    string value() { return m_Value; }
    int lineIndex() { return m_LineIndex; }
    bool isKey(Key key) { return key == m_Key; }

#ifdef _Debug
    string printKey();
#endif

private:
    Key m_Key;
    string m_Value;
    int m_LineIndex;
};