#include "Error.h"

void Error::makeError(string errorType, uint32_t lineIndex, Token got, string expected)
{
    string msg = '[' + errorType + ']';
    msg += " at line " + to_string(lineIndex + 1);
    msg += " expected value: " + expected;
    msg += " got instade: " + got.value;
    printError(msg);
    exit(1);
}

void Error::makeError(string errorType, uint32_t lineIndex, Token got, Token::Type expected)
{
    string msg = '[' + errorType + ']';
    msg += " at line " + to_string(lineIndex + 1);
    msg += " expected type: " + expected;
    msg += " got instade: " + got.type;
    printError(msg);
    exit(1);
}

void Error::makeError(string errorType, uint32_t lineIndex, string input)
{
    string msg = '[' + errorType + ']';
    msg += " at line " + to_string(lineIndex + 1) + " ";
    msg += input;
    printError(msg);
    exit(1);
}

string Error::type2Str(Token::Type type)
{
    switch (type)
    {
    case Token::Type::boolean:
        return "{boolean}";
    case Token::Type::identifier:
        return "{identifier}";
    case Token::Type::ignore:
        return "{ignore}";
    case Token::Type::keyword:
        return "{keyword}";
    case Token::Type::number:
        return "{number}";
    case Token::Type::symbol:
        return "{symbol}";
    default:
        return "{undifinde}";
    }
}

void Error::printError(std::string msg) { std::cout << msg << std::endl; }
