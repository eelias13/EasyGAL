#include "Lexer.hpp"
namespace Lexer
{
    
vector<Pair> tokenize(vector<string> strVec)
{
    vector<Pair> result;
    for (int i = 0; i < strVec.size(); i++)
    {
        string symbol = strVec.at(i);
        if (symbol.length() != 1)
        {
            if (symbol == PIN)
                result.push_back({Token::keywordPin, symbol});
            else if (symbol == TABLE)
                result.push_back({Token::keywordTable, symbol});
            else if (symbol == FILL)
                result.push_back({Token::extraFunction, symbol});
            else if (symbol == COUNT)
                result.push_back({Token::extraFunction, symbol});
            else if (isNum(symbol))
                result.push_back({Token::num, symbol});
            else
                result.push_back({Token::var, symbol});
        }
        else
        {
            char c = symbol.at(0);
            switch (c)
            {
            case AND:
                result.push_back({Token::logicalOperator, symbol});
                break;
            case NOT:
                result.push_back({Token::logicalOperator, symbol});
                break;
            case OR:
                result.push_back({Token::logicalOperator, symbol});
                break;
            case XOR:
                result.push_back({Token::logicalOperator, symbol});
                break;

            case PARENTHSESE_OPEN:
                result.push_back({Token::parentheses, symbol});
                break;
            case PARENTHSESE_CLOSE:
                result.push_back({Token::parentheses, symbol});
                break;
            case CURLYBRACES_OPEN:
                result.push_back({Token::parentheses, symbol});
                break;
            case CURLYBRACES_CLOSE:
                result.push_back({Token::parentheses, symbol});
                break;

            case END:
                result.push_back({Token::end, symbol});
                break;
            case SPACE:
                break;
            case EQUAL:
                if (i != strVec.size() - 1)
                {
                    if (strVec.at(i + 1).length() == 1)
                        if (strVec.at(i + 1).at(0) == ARROW_TIP)
                        {
                            i++;
                            result.push_back({Token::arrow, (symbol + strVec.at(i + 1).at(0))});
                            break;
                        }
                }
                result.push_back({Token::equal, symbol});
                break;
            default:
                if (charIsNum(c))
                    result.push_back({Token::num, symbol});
                else
                    result.push_back({Token::none, symbol});
                break;
            }
        }
    }
    return result;
}

bool isNum(string str)
{
    for (int i = 0; i < str.length(); i++)
        if (!charIsNum(str.at(i)))
            return false;
    return true;
}

bool charIsNum(char c)
{
    switch (c)
    {
    case '0':
        return true;
    case '1':
        return true;
    case '2':
        return true;
    case '3':
        return true;
    case '4':
        return true;
    case '5':
        return true;
    case '6':
        return true;
    case '7':
        return true;
    case '8':
        return true;
    case '9':
        return true;
    default:
        return false;
    }
}

vector<string> spit(vector<string> code)
{
    vector<string> result = splitBy(code, SPACE);
    char splitChar[] = {EQUAL, END, AND, OR, XOR, NOT, PARENTHSESE_OPEN, PARENTHSESE_CLOSE, CURLYBRACES_OPEN, CURLYBRACES_CLOSE};
    for (int i = 0; i < sizeof(splitChar); i++)
        result = splitBy(result, splitChar[i]);

    vector<string> temp;
    for (int i = 0; i < result.size(); i++)
        if ((result.at(i)).length() != 0)
            if (result.at(i).at(0) != SPACE)
                temp.push_back(result.at(i));

    return temp;
}

vector<string> splitBy(vector<string> code, char c)
{
    vector<string> result;
    for (int i = 0; i < code.size(); i++)
    {
        string line = code.at(i);
        string temp = "";
        for (int j = 0; j < line.length(); j++)
        {

            if (line.at(j) == c)
            {
                result.push_back(temp);
                temp = line.at(j);
                result.push_back(temp);
                temp = "";
            }
            else
            {
                temp += line.at(j);
            }
        }
        result.push_back(temp);
    }
    return result;
}
} // namespace Lexer