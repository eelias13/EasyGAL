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

private:
    void error(string);
    void toPostfix(vector<Token>);
    void insertToken(Token);
    void insertOperator(Token);

public:
    vector<bool> parser(vector<Token>);
    vector<Token> getNames(vector<Token>);

    void test(vector<Token>);
};

#endif