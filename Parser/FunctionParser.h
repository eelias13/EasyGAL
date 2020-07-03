/*
 * FunctionParser.cpp
 *
 *  Created on: May 31, 2020
 *      Author: elias
 */
 
#define FUNCTIONPARSER_H_
#ifdef FUNCTIONPARSER_H_

#include <string>
#include <vector>
#include <stack>
#include <utility>
#include <math.h>

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
    bool isParentheses(vector<Token> expression);
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
    bool *lookupValues;
    uint32_t lookupLength;

    void initLookup();
    void updateLookup();
    void deleteLookup();
    bool *getBoolPtr(Token);

private:
    // for getNames
    void initNames(vector<Token>);
    vector<string> removeDouble(vector<string>);
    bool strInVec(vector<string>, string);
    vector<string> names;

private:
    // operator precedence
    uint8_t operatorPrecedence[4];
    uint8_t precedenceOf(char);

private:
    // validate
    void isValide(vector<Token>);
    bool isBinary(char);
    bool valideSymbol(char);

private:
    void syntaxError(Token, Token::Type);
    void syntaxError(Token, string);
    void parsingError(string);

public:
    FunctionParser();

public:
    vector<bool> parse(vector<Token>, uint32_t);
    vector<string> getNames();
};

#endif /* FUNCTIONPARSER_H_ */