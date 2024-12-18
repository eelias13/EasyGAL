/*
 * API.h
 *
 *  Created on: Aug 21, 2020
 *      Author: elias
 */

#ifndef API_H_
#define API_H_

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

#include "Dependencies/json.hpp"
#include "Utility.h"

#include "../Parser/Parser.h"
#include "../Translator/Translator.hpp"

using namespace std;
using json = nlohmann::json;

namespace api
{
    string code2TableData(string easyGALCode,  string deviceName);
    TableData parseTableData(json tdJson);
    vector<TableData> parseTableDataArray(json array);
    string tableData2jedec(string tableDataJson, string deviceName);
} // namespace api

#endif /* API_H_ */