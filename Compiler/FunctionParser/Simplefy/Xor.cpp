#include "Xor.hpp"

string Xor::simplefyXor(string exp)
{
    string temp = simplefyOneXor(exp);
    if (exp.size() != temp.size())
        return simplefyXor(temp);
    return exp;
}

string Xor::simplefyOneXor(string exp)
{
    string out = "";
    int i;
    for (i = 0; i < exp.size() - 2; i++)
        if (truthTableXor(string(1, exp.at(i)) + string(1, exp.at(i + 1)) + string(1, exp.at(i + 2))) == SPACE)
            out += exp.at(i);
        else
        {
            out += truthTableXor(string(1, exp.at(i)) + string(1, exp.at(i + 1)) + string(1, exp.at(i + 2)));
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

char Xor::truthTableXor(string exp)
{
    if (exp.at(1) == XOR)
    {
        if (exp.at(0) == ZERO && exp.at(2) == ZERO)
            return ZERO;
        if (exp.at(0) == ZERO && exp.at(2) == ONE)
            return ONE;
        if (exp.at(0) == ONE && exp.at(2) == ZERO)
            return ONE;
        if (exp.at(0) == ONE && exp.at(2) == ONE)
            return ZERO;
    }
    return SPACE;
}
