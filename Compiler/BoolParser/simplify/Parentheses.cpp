
#include "Parentheses.hpp"
using namespace std;
namespace Parentheses
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
    for (i = 0; i < exp.length() - 2; i++)
    {
        string temp = "";
        temp += exp.at(i);
        temp += exp.at(i + 1);
        temp += exp.at(i + 2);
        if (truthTable(temp) == SPACE)
            out += exp.at(i);
        else
        {
            out += truthTable(temp);
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

char truthTable(string exp)
{
    if (exp.at(0) == PARENTHSESE_OPEN && exp.at(2) == PARENTHSESE_CLOSE)
    {
        if (exp.at(1) == ZERO)
            return ZERO;
        if (exp.at(1) == ONE)
            return ONE;
    }
    return SPACE;
}
} // namespace Parentheses
