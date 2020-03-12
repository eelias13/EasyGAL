#include "Or.hpp"

string Or::simplefyOr(string exp)
{
    string temp = simplefyOneOr(exp);
    if (exp.size() != temp.size())
        return simplefyOr(temp);
    return exp;
}

string Or::simplefyOneOr(string exp)
{
    string out = "";
    int i;
    for (i = 0; i < exp.size() - 2; i++)
        if (truthTableOr(string(1, exp.at(i)) + string(1, exp.at(i + 1)) + string(1, exp.at(i + 2))) == SPACE)
            out += exp.at(i);
        else
        {
            out += truthTableOr(string(1, exp.at(i)) + string(1, exp.at(i + 1)) + string(1, exp.at(i + 2)));
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

char Or::truthTableOr(string exp)
{
    if (exp.at(1) == OR)
    {
        if (exp.at(0) == ZERO && exp.at(2) == ZERO)
            return ZERO;
        if (exp.at(0) == ZERO && exp.at(2) == ONE)
            return ONE;
        if (exp.at(0) == ONE && exp.at(2) == ZERO)
            return ONE;
        if (exp.at(0) == ONE && exp.at(2) == ONE)
            return ONE;
    }
    return SPACE;
}