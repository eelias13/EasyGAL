#pragma once
#include <vector>
#include <utility>
#include <stack>
#include "Helper.hpp"
#include "Table.hpp"
#include "Lexer/Token.hpp"
#include "Lexer/Lexer.hpp"
#include "../Translator/TableData.hpp"
using namespace std;

class Compiler
{
private:

public:
    Compiler();
    vector<TableData> compile(vector<string>);

private:
    Lexer m_Lexer;
    FunctionParser m_FP;
    vector<pair<string, int>> m_Alias;
    vector<Table> m_Tables;
    vector<string> m_IsD;
};