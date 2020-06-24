/*
 * Error.h
 *
 *  Created on: May 29, 2020
 *      Author: elias
 */

#ifndef ERROR_H_
#define ERROR_H_

#include <string>

#include "Token.h"
#include "Symbols.h"
#include "../Shared/Error.h"

using namespace std;

namespace Error
{
    enum Type
    {
        parsing,
        syntax,
        lexing
    };

    void makeError(Type, uint32_t, Token, string);
    void makeError(Type, uint32_t, Token, Token::Type);
    void makeError(Type, uint32_t, string);

    string tokenType2Str(Token::Type);
    string errorType2Str(Type);
} // namespace Error

#endif /* ERROR_H_ */