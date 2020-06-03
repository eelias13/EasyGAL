#define FUNCTIONPARSER_H_
#ifdef FUNCTIONPARSER_H_

#include <string>
#include <vector>
#include <queue>
#include <stack>

#include "Token.h"
#include "Symbols.h"
#include "Error.h"

using namespace std;

class FunctionParser
{
private:
    stack<Token> tokenStack;
    queue<Token> tokenQueue;
    uint32_t lineIndex;
    char operatorPrecedence[4];

private:
    void error(Token got, Token::Type expected);
    void error(Token got, string expected);
    void toPostfix(vector<Token>);
    void insertToken(Token);
    void insertOperator(Token);

    uint8_t precedenceOf(char);
    bool isGreater(char);

public:
    vector<bool> parser(vector<Token>, uint16_t);
    vector<Token> getNames(vector<Token>);
    FunctionParser();

    void test(vector<Token>);
};

#endif /* FUNCTIONPARSER_H_ */