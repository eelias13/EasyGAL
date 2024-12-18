/*
 * API.cpp
 *
 *  Created on: Aug 21, 2020
 *      Author: elias
 */

#include "API.h"

string api::code2TableData(string easyGALCode, string deviceName)
{
    Parser parser = Parser(easyGALCode);
    vector<TableData> tableData = parser.parse();

    if (!deviceName.empty())
    {
        Configs::CircuitConfig DeviceType;
        vector<uint32_t> inputPins;
        vector<uint32_t> outputPins;
        initDeviceType(DeviceType, deviceName, inputPins, outputPins);
        validate(tableData, inputPins, outputPins);
    }

    json out = json::array();

    for (TableData td : tableData)
    {
        json temp = json::object();

        temp["inputPins"] = td.m_InputPins;
        temp["outputPin"] = td.m_OutputPin;
        temp["table"] = td.m_Table;
        temp["dff"] = td.m_EnableFlipFlop;

        out.push_back(temp);
    }

    json result = json::object();
    result["TableData"] = out;

    return result.dump();
}

TableData api::parseTableData(json tdJson)
{
    // auto glambda = [](auto a, auto &&b) { return a < b; };
    auto check = [](string expected, json tdJson)
    {
        if (tdJson.find(expected) == tdJson.end())
        {
            cerr << "missing property " << expected << " in json object " << tdJson << endl;
            exit(1);
        }
    };

    check("dff", tdJson);
    check("outputPin", tdJson);
    check("inputPins", tdJson);
    check("table", tdJson);

    TableData tableData;

    tableData.m_EnableFlipFlop = tdJson["dff"];
    tableData.m_OutputPin = tdJson["outputPin"];
    for (uint32_t pin : tdJson["inputPins"])
        tableData.m_InputPins.push_back(pin);
    for (bool b : tdJson["table"])
        tableData.m_Table.push_back(b);
    return tableData;
}

vector<TableData> api::parseTableDataArray(json array)
{
    vector<TableData> result = vector<TableData>(array.size());
    for (uint32_t i = 0; i < array.size(); i++)
    {
        parseTableData(array[i]);
        // tableData.m_InputPins =
    }

    return result;
}

string api::tableData2jedec(string tableDataJson, string deviceName)
{

    json jsonFile = json::parse(tableDataJson);

    vector<TableData> tableData = parseTableDataArray(jsonFile["TableData"]);

    if (tableData.empty())
    {
        cerr << "on TableData found in json " << endl;
        exit(1);
    }

    Configs::CircuitConfig DeviceType;
    vector<uint32_t> inputPins;
    vector<uint32_t> outputPins;
    initDeviceType(DeviceType, deviceName, inputPins, outputPins);
    validate(tableData, inputPins, outputPins);

    return Translator::Process(tableData, DeviceType);
}