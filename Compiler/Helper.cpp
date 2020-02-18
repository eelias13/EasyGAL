#include "Helper.hpp"

void ERROR(string err)
{
    cout << "[Error] " << err << endl;
}

void Helper::print(string str)
{
    cout << str << endl;
}

string Helper::getTokenName(Token t)
{
    switch (t)
    {
    case Token::logicalOperator:
        return "logicalOperator";
    case Token::arrow:
        return "arrow";
    case Token::boolean:
        return "boolean";
    case Token::end:
        return "end";
    case Token::equal:
        return "epual";
    case Token::extraFunction:
        return "extraFunction";
    case Token::keywordPin:
        return "keywordPin";
    case Token::keywordTable:
        return "keywordTable";
    case Token::none:
        return "none";
    case Token::num:
        return "num";
    case Token::parentheses:
        return "parentheses";
    case Token::var:
        return "var";
    default:
        return "not defined";
    }
}

void Helper::printPare(vector<Pair> p)
{
    for (int i = 0; i < p.size(); i++)
        print(getTokenName(p.at(i).key) + ":" + p.at(i).value);
}

void Helper::printStrVec(vector<string> strVec)
{
    for (int i = 0; i < strVec.size(); i++)
        print(strVec.at(i));
}

