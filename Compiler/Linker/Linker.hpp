#pragma once
#include <vector>
#include <stdint.h>
#include "../../Translator/TableData.hpp"
#include "../TablesAndNames.hpp"

using namespace std;

class Linker
{
public:
    struct TableName
    {
        string OutName;
        vector<bool> BoolTable;
        vector<string> InNames;
    };

private:
    vector<TableName> split(TablesAndNames);
    vector<TableData> matchPins(vector<TableName>, TablesAndNames);
    int findePin(string, vector<pair<string, int>>);
    void matchD(vector<TableName> &TNVec);

    void checkPin(int, bool);
    bool isValidPin(int, bool);

public:
    Linker();
    Linker(vector<int>, vector<int>);
    vector<TableData> link(TablesAndNames);

private:
    vector<int> m_ValidInPins;
    vector<int> m_ValidOutPins;
};
