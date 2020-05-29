#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>

#include "TableData.h"
#include "Lexer.h"
#include "Token.h"
#include "Symbols.h"
#include "Error.h"

using namespace std;

class Parser
{
public:
    Parser(string);
    vector<TableData> parse();

private:
    vector<string> code;

    vector<TableData> tables;
    vector<pair<string, uint32_t>> alias;

    Lexer lexer;
    Token currentToken;

    bool isFill;
    bool fill;
    bool isCount;

private:
    // main parser function
    void parseNext();
    void parsePin();
    void parseTable();
    void parseIdentifier();

    // helper for parsePin()
    uint32_t str2Pin(string);
    string pin2Str(uint32_t);

    // helper for tableParse()
    vector<uint32_t> getIdentifier();
    void extraFunction();
    vector<bool> getBooltable();
    void insertBooltable(vector<bool> &, string);

    // helper for parseIdentifier()
    void insertDFF(uint32_t);
    vector<Token> getExpression();
    bool validExpression();

    // helpful functions
    void nextToken();

    bool isToken(char);
    bool isToken(string);
    bool isToken(Token::Type);

    void expect(char);
    void expect(string);
    void expect(Token::Type);

    uint32_t getInt(char c);
    uint32_t str2Int(string);

    // error handling
    void parsingError(string);
    void syntaxError(string);
    string type2Str(Token::Type);
};

#endif /* PARSER_H_ */