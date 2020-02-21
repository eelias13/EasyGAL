#include "FuncParse.hpp"

string FuncParse::boolFunc2table(string exp, vector<string> var)
{
    if (var.empty())
        var = FuncParse::Helper::findeVarInFunc(exp);
    else
    {
        var = FuncParse::Helper::removeDoubleVar(var);
        var = FuncParse::Helper::sortByLen(var);
    }

    if (var.empty())
        ERROR("can not finde variables");

    if (!FuncParse::Helper::isVarValide(var))
        ERROR("var contains invaled char");

    vector<string> table = FuncParse::Helper::generateTable(var.size());
    string out = "";
    for (int i = 0; i < table.size(); i++)
    {
        string temp = substitute(exp, table[i], var);
        char c = Parser::parse(temp);
        out += c;
    }
    return out;
}

string FuncParse::substitute(string exp, string table, vector<string> var)
{
    for (int i = 0; i < var.size(); i++)
        exp = FuncParse::Helper::replaceStr(exp, var[i], to_string(table.at(i)));
    return exp;
}

bool FuncParse::Helper::isVarValide(vector<string> var)
{
    for (int i = 0; i < var.size(); i++)
        for (int j = 0; j < var[i].length(); j++)
            if (!FuncParse::Helper::validChar(var[i].at(j)))
                return false;

    return true;
}

vector<string> FuncParse::Helper::findeVarInFunc(string function)
{
    function = FuncParse::Helper::removeChar(function, SPACE);

    string temp;
    char c = function.at(0);
    if ((c == NOT) || (c == PARENTHSESE_OPEN))
        temp = "";
    else
        temp = to_string(SPACE);

    function = FuncParse::Helper::replace(function, NOT, SPACE);
    function = FuncParse::Helper::replace(function, AND, SPACE);
    function = FuncParse::Helper::replace(function, OR, SPACE);
    function = FuncParse::Helper::replace(function, XOR, SPACE);
    function = FuncParse::Helper::replace(function, PARENTHSESE_OPEN, SPACE);
    function = FuncParse::Helper::replace(function, PARENTHSESE_CLOSE, SPACE);

    for (int i = 0; i < function.length(); i++)
    {
        if (i == function.length() - 1)
        {
            if (!(function.at(i) == SPACE))
                temp += function.at(i);
        }
        else if (!((function.at(i) == SPACE) && (function.at(i + 1) == SPACE)))

            temp += function.at(i);
    }

    int index = 0;
    for (int i = 0; i < temp.length(); i++)
        if (temp.at(i) == SPACE)
            index++;

    vector<string> var;
    index = -1;
    for (int i = 0; i < temp.length(); i++)
    {
        if (temp.at(i) == SPACE)
        {
            index++;
            i++;
            var[index] = "";
        }
        if (index != -1)
            var[index] += temp.at(i);
    }
    var = FuncParse::Helper::removeDoubleVar(var);
    var = FuncParse::Helper::sortByLen(var);
    return var;
}

vector<string> FuncParse::Helper::removeDoubleVar(vector<string> var)
{
    vector<string> newVar;
    newVar.push_back(var.at(0));
    for (int i = 0; i < var.size; i++)
    {
        bool b = true;
        for (int j = 0; j < newVar.size(); j++)
            if (newVar.at(j) == var.at(i))
                b = false;
        if (b)
            newVar.push_back(var[i]);
    }

    vector<string> out;
    for (int i = 0; i < newVar.size(); i++)
        out[i] = newVar.at(i);
    return out;
}

bool FuncParse::Helper::validChar(char c)
{
    switch (c)
    {
    case NOT:
        return false;
    case AND:
        return false;
    case OR:
        return false;
    case XOR:
        return false;

    case PARENTHSESE_OPEN:
        return false;
    case PARENTHSESE_CLOSE:
        return false;

    case SPACE:
        return false;

    default:
        return true;
    }
}

string FuncParse::Helper::replace(string str, char c, char r)
{
    string result = "";
    for (int i = 0; i < str.size(); i++)
        if (str.at(i) == c)
            result += r;
        else
            result += str.at(i);

    return result;
}

string FuncParse::Helper::removeChar(string str, char r)
{
    string result = "";
    for (int i = 0; i < str.size(); i++)
        if (str.at(i) != r)
            result += str.at(i);
    return result;
}

string FuncParse::Helper::replaceStr(string exp, string str, string replace)
{
    return exp;
}

vector<string> FuncParse::Helper::sortByLen(vector<string> var)
{
    return {""};
}

vector<string> FuncParse::Helper::generateTable(int len)
{
    return {""};
}