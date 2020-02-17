
#include "Not.hpp"

using namespace std;
namespace Not
{
string simplefy(string exp)
{
    int len = exp.length();
    exp = simplefyOne(exp);
    if (exp.length() != len)
        return simplefy(exp);
    return exp;
}

string simplefyOne(string exp)
{
    string out = "";
    int i;
    for (i = 0; i < exp.length() - 1; i++)
    {
        string temp = "";
        temp += exp.at(i);
        temp += exp.at(i + 1);
        if (truthTable(temp) == SPACE)
            out += exp.at(i);
        else
        {
            out += truthTable(temp);
            i += 1;
        }
    }

    if (i == exp.length() - 1)
        out += exp.at(exp.length() - 1);
    return out;
}

char truthTable(string exp)
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
} // namespace Not