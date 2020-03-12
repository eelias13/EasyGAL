
#include "Parser.hpp"
/**
* @param exp boolean expression without variables e.g. (1 | 0) & 0
* @return zero or one
*/
char Parser::parse(string exp)
{
    if (exp.empty())
        error("", "exp can not be empty", -1);

    // checks for valid characters and right structure
    // exp = Preproces::preProcessing(exp);

    string outStr = parseRecursiv(exp);
    if (outStr.size() != 1)
        error("", "can not parse expresion", -1);

    char out = outStr.at(0);
    if (out == ZERO || out == ONE)
        return out;

    else
        error("", "can not parse expresion", -1);
    return '\0';
}

/**
 * Order of operations: Parentheses, Not, And, Or, Exclusive Or.
 * 
 * How it functions: if expression get's simplified (gets smaller) then parse
 * with next function while expression is not one char 
 */

string Parser::parseRecursiv(string exp)
{
    if (exp.size() == 1)
        return exp;

    string temp1 = Parentheses::simplefyParentheses(exp);
    if (exp.size() != temp1.size())
        return parseRecursiv(temp1);

    string temp2 = Not::simplefyNot(temp1);
    if (temp1.size() != temp2.size())
        return parseRecursiv(temp2);

    string temp3 = And::simplefyAnd(temp2);
    if (temp2.size() != temp3.size())
        return parseRecursiv(temp3);

    string temp4 = Or::simplefyOr(temp3);
    if (temp3.size() != temp4.size())
        return parseRecursiv(temp4);

    string temp5 = Xor::simplefyXor(temp4);
    if (temp4.size() != temp5.size())
        return parseRecursiv(temp5);

    return parseRecursiv(temp5);
}
