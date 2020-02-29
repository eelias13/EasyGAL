#pragma once
#include <vector>
#include <stdint.h>
#include "../../TableData.hpp"
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
    uint32_t findePin(string, vector<pair<string, int>>);
    void matchD(vector<TableName> &TNVec);

public:
    Linker();
    vector<TableData> link(TablesAndNames);
};
