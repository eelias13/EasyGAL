#ifndef ERROR_H_
#define ERROR_H_

#include <string>
#include <iostream>

#include "Token.h"

using namespace std;

namespace Error
{
    void makeError(string, uint32_t, Token, string);
    void makeError(string, uint32_t, Token, Token::Type);
    void makeError(string, uint32_t, string);
    void printError(string);
    string type2Str(Token::Type);
} // namespace Error

#endif /* ERROR_H_ */