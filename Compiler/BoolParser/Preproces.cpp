#include "Preproces.hpp"

string Preproces::preProcessing(string exp)
{
    char c = exp.at(0);
    if (!(c == ZERO || c == ONE || c == PARENTHSESE_OPEN || c == NOT))
        ERROR("unexpectet cahr " + to_string(c) + " at index: " + to_string(0));

    int parentheses = 0;
    for (int i = 1; i < exp.length(); i++)
    {
        c = exp.at(i);
        char pc = exp.at(i - 1);
        if (pc == ZERO || pc == ONE)
            if (!(c == AND || c == OR || c == XOR || c == PARENTHSESE_CLOSE))
                ERROR("unexpectet cahr " + to_string(c) + " at index: " + to_string(i));
            else if (pc == PARENTHSESE_OPEN)
                parentheses++;
        if (!(c == PARENTHSESE_OPEN || c == ZERO || c == ONE || c == NOT))
            ERROR("unexpectet cahr " + to_string(c) + " at index: " + to_string(i));
        else if (pc == PARENTHSESE_CLOSE)
            parentheses--;
        if (!(c == AND || c == OR || c == XOR || c == PARENTHSESE_CLOSE))
            ERROR("unexpectet cahr " + to_string(c) + " at index: " + to_string(i));
        else if (pc == AND || pc == OR || pc == XOR)
            if (!(c == ZERO || c == ONE || c == PARENTHSESE_OPEN || c == NOT))
                ERROR("unexpectet cahr " + to_string(c) + " at index: " + to_string(i));
            else if (pc == NOT)
                if (!(c == ZERO || c == ONE || c == PARENTHSESE_OPEN || c == NOT))
                    ERROR("unexpectet cahr " + to_string(c) + " at index: " + to_string(i));
    }

    if (exp.at(exp.length() - 1) == PARENTHSESE_CLOSE)
        parentheses--;
    if (parentheses != 0)
        if (parentheses < 0)
            ERROR("you have forgot a opening parentheses");
        else
            ERROR("you have forgot a closing parentheses");
    return exp;
}

string Preproces::removeSpace(string exp)
{
    string out = "";
    for (int i = 0; i < exp.length(); i++)
    {
        char c = exp.at(i);
        if (c != SPACE)
            if (validChar(c))
                out += c;
            else
                ERROR("unknown cahr " + to_string(c));
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
