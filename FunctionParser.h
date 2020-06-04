#define FUNCTIONPARSER_H_
#ifdef FUNCTIONPARSER_H_

#include <string>
#include <vector>
#include <queue>
#include <stack>

#include "Token.h"
#include "Symbols.h"
#include "Error.h"
#include "TableData.h"

using namespace std;

class FunctionParser
{
private:
    stack<Token> tokenStack;
    queue<Token> tokenQueue;
    uint32_t lineIndex;
    char operatorPrecedence[4];

private:
    void error(Token, Token::Type);
    void error(Token, string);
    void toPostfix(vector<Token>);
    void insertToken(Token);
    void insertOperator(Token);

    uint8_t precedenceOf(char);
    bool isGreater(char);

    vector<string> removeDouble(vector<string>);
    bool strInVec(vector<string>, string);

public:
    FunctionParser();
    vector<bool> parser(vector<Token>);
    vector<string> getNames(vector<Token>);

    void test(vector<Token>);
};

#endif /* FUNCTIONPARSER_H_ */