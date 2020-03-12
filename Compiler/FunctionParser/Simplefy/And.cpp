#include "And.hpp"

string And::simplefyAnd(string exp)
{
    string temp = simplefyOneAnd(exp);
    if (exp.size() != temp.size())
        return simplefyAnd(temp);
    return exp;
}

string And::simplefyOneAnd(string exp)
{
    string out = "";
    int i;
    for (i = 0; i < exp.size() - 2; i++)
        if (truthTableAnd(string(1, exp.at(i)) + string(1, exp.at(i + 1)) + string(1, exp.at(i + 2))) == SPACE)
            out += exp.at(i);
        else
        {
            out += truthTableAnd(string(1, exp.at(i)) + string(1, exp.at(i + 1)) + string(1, exp.at(i + 2)));
            i += 2;
        }

    if (i == exp.size() - 2)
    {
        out += exp.at(exp.size() - 2);
        i++;
    }

    if (i == exp.size() - 1)
        out += exp.at(exp.size() - 1);
    return out;
}

char And::truthTableAnd(string exp)
{
    if (exp.at(1) == AND)
    {
        if (exp.at(0) == ZERO && exp.at(2) == ZERO)
            return ZERO;
        if (exp.at(0) == ZERO && exp.at(2) == ONE)
            return ZERO;
        if (exp.at(0) == ONE && exp.at(2) == ZERO)
            return ZERO;
        if (exp.at(0) == ONE && exp.at(2) == ONE)
            return ONE;
    }

    return SPACE;
}
