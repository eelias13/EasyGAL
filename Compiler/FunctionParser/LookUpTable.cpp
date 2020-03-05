#include "LookUpTable.hpp"

void LookUpTable::setKey(vector<Token> Keys)
{
    m_Keys = Keys;
}

vector<Token> LookUpTable::getKey()
{
    return m_Keys;
}

void LookUpTable::addKey(Token t)
{
    m_Keys.push_back(t);
}

bool LookUpTable::at(Token t)
{
    for (int i = 0; i < m_Keys.size(); i++)
        if (m_Keys.at(i).value() == t.value())
            return m_Value.at(i);

    error("", "valid to evaluate expresion", t.lineIndex());
}

void LookUpTable::setValue(vector<bool> Value)
{
    m_Value = Value;
}