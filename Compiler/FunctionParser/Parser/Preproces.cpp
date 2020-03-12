#include "Preproces.hpp"

string Preproces::preProcessing(string exp)
{
    // removing space and return null if unknown char
    string temp = removeSpace(exp);

    char c = temp.at(0);
    if (!(c == ZERO || c == ZERO || c == PARENTHSESE_OPEN || c == NOT))
        error("", "unexpectet cahr " + string(1, c) + " at index: 0", -1);
    int parentheses = 0;
    for (int i = 1; i < temp.size(); i++)
    {
        c = temp.at(i);
        char pc = temp.at(i - 1);
        if (pc == ZERO || pc == ONE)
            if (!(c == AND || c == OR || c == XOR || c == PARENTHSESE_CLOSE))
                error("", "unexpectet cahr " + string(1, c) + " at index: " + to_string(i), -1);
            else if (pc == PARENTHSESE_OPEN)
                parentheses++;
        if (!(c == PARENTHSESE_OPEN || c == ZERO || c == ONE || c == NOT))
            error("", "unexpectet cahr " + string(1, c) + " at index: " + to_string(i), -1);
        else if (pc == PARENTHSESE_CLOSE)
            parentheses--;
        if (!(c == AND || c == OR || c == XOR || c == PARENTHSESE_CLOSE))
            error("", "unexpectet cahr " + string(1, c) + " at index: " + to_string(i), -1);
        else if (pc == AND || pc == OR || pc == XOR)
            if (!(c == ZERO || c == ONE || c == PARENTHSESE_OPEN || c == NOT))
                error("", "unexpectet cahr " + string(1, c) + " at index: " + to_string(i), -1);
            else if (pc == NOT)
                if (!(c == ZERO || c == ONE || c == PARENTHSESE_OPEN || c == NOT))
                    error("", "unexpectet cahr " + string(1, c) + " at index: " + to_string(i), -1);
    }

    if (temp.at(temp.size() - 1) == PARENTHSESE_CLOSE)
        parentheses--;
    if (parentheses != 0)
        if (parentheses < 0)
            error("", "you have forgot a opening parentheses", -1);
        else
            error("", "you have forgot a closing parentheses", -1);
    return temp;
}

string Preproces::removeSpace(string exp)
{
    string out = "";
    for (int i = 0; i < exp.size(); i++)
    {
        char c = exp.at(i);
        if (c != SPACE)
            if (validChar(c))
                out += c;
            else
                error("", "unknown cahr " + string(1, c), -1);
    }
    return out;
}

bool Preproces::validChar(char c)
{
    switch (c)
    {
    case ZERO:
        return true;
    case ONE:
        return true;

    case NOT:
        return true;
    case AND:
        return true;
    case OR:
        return true;
    case XOR:
        return true;

    case PARENTHSESE_CLOSE:
        return true;
    case PARENTHSESE_OPEN:
        return true;

    default:
        return false;
    }
}
