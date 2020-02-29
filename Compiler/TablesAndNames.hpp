#pragma once
#include <vector>
#include <string>
#include <utility>
#include "Table.hpp"

using namespace std;

struct TablesAndNames
{
    vector<pair<string, int>> Alias;
    vector<Table> Tables;
    vector<string> IsD;
};
