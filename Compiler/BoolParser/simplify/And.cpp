#include "And.hpp"

string And::simplifyOne(string exp)
{
    string out = "";
    int i;
    for (i = 0; i < exp.length() - 2; i++)
    {
        string temp = "";
        temp += exp.at(i);
        temp += exp.at(i + 1);
        temp += exp.at(i + 2);
        if (And::truthTable(temp) == SPACE)
            out += exp.at(i);
        else
        {
            out += And::truthTable(temp);
            i += 2;
        }
    }
    if (i == exp.length() - 2)
    {
        out += exp.at(exp.length() - 2);
        i++;
    }
    if (i == exp.length() - 1)
        out += exp.at(exp.length() - 1);
    return out;
}

string And::simplify(string exp)
{
    if (exp.length() < 3)
        return exp;
    int len = exp.length();
    exp = And::simplifyOne(exp);
    if (exp.length() == 1)
        return exp;
    if (exp.length() != len)
        return And::simplify(exp);
    return exp;
}

char And::truthTable(string exp)
{
    if (exp.at(1) == AND)
        if (exp.at(0) == ZERO && exp.at(2) == ZERO)
            return ZERO;
    if (exp.at(0) == ZERO && exp.at(2) == ONE)
        return ZERO;
    if (exp.at(0) == ONE && exp.at(2) == ZERO)
        return ZERO;
    if (exp.at(0) == ONE && exp.at(2) == ONE)
        return ONE;
    return SPACE;
}