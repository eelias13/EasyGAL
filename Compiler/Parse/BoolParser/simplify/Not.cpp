
#include "Not.hpp"

string Not::simplify(string exp)
{
    if (exp.length() == 1)
        return exp;
    int len = exp.length();
    exp = Not::simplifyOne(exp);
    if (exp.length() != len)
        return Not::simplify(exp);
    return exp;
}

string Not::simplifyOne(string exp)
{
    string out = "";
    int i;
    for (i = 0; i < exp.length() - 1; i++)
    {
        string temp = "";
        temp += exp.at(i);
        temp += exp.at(i + 1);
        if (Not::truthTable(temp) == SPACE)
            out += exp.at(i);
        else
        {
            out += Not::truthTable(temp);
            i += 1;
        }
    }

    if (i == exp.length() - 1)
        out += exp.at(exp.length() - 1);
    return out;
}

char Not::truthTable(string exp)
{
    if (exp.at(0) == NOT)
    {
        if (exp.at(1) == ONE)
            return ZERO;
        if (exp.at(1) == ZERO)
            return ONE;
    }
    return SPACE;
}