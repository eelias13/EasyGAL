#include "Parentheses.hpp"

string Parentheses::simplefyParentheses(string exp)
{
    if (exp.size() == 1)
        return exp;
    string temp = simplefyOneParentheses(exp);
    if (exp.size() != temp.size())
        return simplefyParentheses(temp);
    return exp;
}

string Parentheses::simplefyOneParentheses(string exp)
{
    string out = "";
    int i;
    for (i = 0; i < exp.size() - 2; i++)
        if (truthTableParentheses(string(1, exp.at(i)) + string(1, exp.at(i + 1)) + string(1, exp.at(i + 2))) == SPACE)
            out += exp.at(i);
        else
        {
            out += truthTableParentheses(string(1, exp.at(i)) + string(1, exp.at(i + 1)) + string(1, exp.at(i + 2)));
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

char Parentheses::truthTableParentheses(string exp)
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
