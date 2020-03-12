#include "Not.hpp"

string Not::simplefyNot(string exp)
{
    string temp = simplefyOneNot(exp);
    if (exp.size() != temp.size())
        return simplefyNot(temp);
    return exp;
}

string Not::simplefyOneNot(string exp)
{
    string out = "";
    int i;
    for (i = 0; i < exp.size() - 1; i++)
        if (truthTableNot(string(1, exp.at(i)) + string(1, exp.at(i + 1))) == SPACE)
            out += exp.at(i);
        else
        {
            out += truthTableNot(string(1, exp.at(i)) + string(1, exp.at(i + 1)));
            i += 1;
        }

    if (i == exp.size() - 1)
        out += exp.at(exp.size() - 1);
    return out;
}

char Not::truthTableNot(string exp)
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
