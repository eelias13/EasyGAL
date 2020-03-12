#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include "../Helper.hpp"
#include "Symbol.hpp"
using namespace std;

class Table
{
public:
    enum class Type
    {
        None,
        Count,
    };
    bool m_InitSuccess;

private:
    vector<vector<bool>> splitRows(vector<bool>, int);
    pair<int, vector<bool>> matchLine(vector<bool>, int);
    vector<vector<bool>> match(vector<vector<bool>>, int, bool);

public:
    Table(vector<string>, vector<string>, vector<bool>, bool);
    Table(vector<string>, vector<string>, vector<bool>, Type);
    vector<bool> getDate(string);
    vector<string> getInNames();
    vector<string> getOutNames();

private:
    vector<string> m_InNames;
    vector<string> m_OutNames;
    vector<vector<bool>> m_BoolVec;
    bool m_Fill;
};
