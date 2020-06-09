#define FUNCTIONPARSER_H_
#ifdef FUNCTIONPARSER_H_

#include <string>
#include <vector>
#include <stack>
#include <utility>

#include "Token.h"
#include "Symbols.h"
#include "Error.h"

using namespace std;

class FunctionParser
{
private:
    bool finished;
    uint32_t lineIndex;

private:
    // split functions
    struct Bundle;
    Bundle split(vector<Token>);
    Bundle splitParentheses(vector<Token>);
    Bundle splitNot(vector<Token>);
    Bundle splitBineryOperator(vector<Token>);
    uint32_t splitIndex(vector<Token>);

private:
    // nodes
    struct Node;
    struct Node *newNode(Token, Node *);
    Node *nextNode(vector<Token>, Node *);
    bool evalNode(Node *);
    void deleteNode(Node *);

private:
    // lookup
    vector<pair<string, bool *>> lookup;
    bool *values;
    uint32_t valueLength;

    void initLookup(vector<Token>);
    void updateLookup();
    void deleteLookup();
    bool *getBoolPtr(Token);

private:
    // for getNames
    vector<string> removeDouble(vector<string>);
    bool strInVec(vector<string>, string);

private:
    // operator precedence
    uint8_t operatorPrecedence[4];
    uint8_t precedenceOf(char);

public:
    FunctionParser();

public:
    vector<bool> parse(vector<Token>, uint32_t);
    vector<string> getNames(vector<Token>);
};

#endif /* FUNCTIONPARSER_H_ */