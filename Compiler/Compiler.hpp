#pragma once
#include <vector>
#include <utility>
#include <stack>

#include "Table.hpp"
#include "../Helper.hpp"
#include "Lexer/Token.hpp"
#include "Lexer/Lexer.hpp"
#include "TablesAndNames.hpp"
#include "../Translator/TableData.hpp"
#include "StackHelper/StackHelper.hpp"
#include "PreCompiler/PreCompiler.hpp"
#include "Linker/Linker.hpp"
#include "FunctionParser/FunctionParser.hpp"

using namespace std;

class Compiler
{
private:
    vector<bool> getBoolVec(stack<Token> &);
    vector<string> getIdentifierList(stack<Token> &);
    vector<Token> getExpresion(stack<Token> &);

    bool pinIsValide(int);
    vector<string> getNames(vector<Token>);

    void prase(stack<Token> &);
    void pinProcess(stack<Token> &);
    void tableProcess(stack<Token> &);
    void functionProcess(stack<Token> &);

public:
    Compiler(vector<int>, vector<int>);
    vector<TableData> compile(vector<string>);

private:
    vector<pair<string, int>> m_Alias;
    vector<Table> m_Tables;
    vector<string> m_IsD;

    FunctionParser m_FP;
    vector<int> m_ValidPins;

    Lexer m_Lexer;
    PreCompiler m_PreCompiler;
    Linker m_Linker;
};
