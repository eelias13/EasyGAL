#pragma once
#include <vector>
#include <utility>
#include <stack>
#include "Helper.hpp"
#include "Table.hpp"
#include "FunctionParser/FunctionParser.hpp"
#include "Lexer/Token.hpp"
#include "Lexer/Lexer.hpp"
#include "../Translator/TableData.hpp"

using namespace std;

class Compiler
{
private:
    void check(Token, Token::Key);
    void check(Token, string);
    void check(Token, char);
    void savePop(stack<Token> &, Token::Key);
    void savePop(stack<Token> &, string);
    void savePop(stack<Token> &, char);
    void savePop(stack<Token> &);

    vector<bool> getBoolVec(stack<Token> &);
    vector<string> getIdentifierList(stack<Token> &);
    vector<Token> getExpresion(stack<Token> &);
    stack<Token> preParse(vector<Token>);
    vector<TableData> Compiler::link();
    bool nextValid(Token);
    bool pinIsValide(int);


    void grouping(stack<Token> &, stack<Token> &);
    void preParseIdentifier(stack<Token> &, stack<Token> &);
    void preParsePoint(stack<Token> &, stack<Token> &);
    void preParseKeyword(stack<Token> &, stack<Token> &);
    void prase(stack<Token> &);
    void pinProcess(stack<Token> &);
    void tableProcess(stack<Token> &);
    void functionProcess(stack<Token> &);

    
public:
    Compiler(vector<int>);
    vector<TableData> compile(vector<string>);

private:
    FunctionParser m_FP;
    vector<pair<string, int>> m_Alias;
    vector<Table> m_Tables;
    vector<string> m_IsD;

    vector<int> m_ValidPins;
};
