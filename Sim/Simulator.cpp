/*
 * Simulator.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: elias
 */

#include <iostream>
#include "Gal.h"
#include "CLI.h"

#include <string>
#include <cstdint>
#include <utility>
#include <math.h>

#include "../Shared/TableData.h"

using namespace std;

void printError(string msg)
{
    cerr << msg << endl;
    exit(1);
}

bool inVec(vector<uint32_t> vec, uint32_t value)
{
    for (uint32_t temp : vec)
        if (value == temp)
            return true;
    return false;
}

void validate(vector<TableData> tables, vector<uint32_t> inputPins, vector<uint32_t> outputPins)
{
    for (uint32_t i = 0; i < tables.size(); i++)
    {
        for (uint32_t pin : tables.at(i).m_InputPins)
            if (!inVec(inputPins, pin))
                printError("pin " + to_string(pin) + " is not an input pin");

        if (!inVec(outputPins, tables.at(i).m_OutputPin))
            printError("pin " + to_string(tables.at(i).m_OutputPin) + " is not an output pin");

        if (pow(2, tables.at(i).m_InputPins.size()) != tables.at(i).m_Table.size())
            printError("table at output pin " + to_string(tables.at(i).m_OutputPin) + " has the wrong shape");

        for (uint32_t j = i + 1; j < tables.size(); j++)
        {
            if (tables.at(i).m_OutputPin == tables.at(j).m_OutputPin)
                printError("table at output pin " + to_string(tables.at(i).m_OutputPin) + " was defined twice");
        }
    }
}

int main()
{
    // load dummy data
    vector<TableData> tableData = {
        {{9, 10, 11}, 14, {false, false, false, false, true, true, true, true}, false},
        {{13, 14}, 15, {false, false, false, true}, false}};

    vector<uint32_t> inputPins = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
    vector<uint32_t> outputPins = {14, 15, 16, 17, 18, 19, 20, 21, 22, 23};

    validate(tableData, inputPins, outputPins);

    Gal gal = Gal(tableData, inputPins, outputPins);
    CLI cli = CLI(gal);

    // while (true)
    // {
    //     cout << "EasyGAL simulator >";
    //     string input;
    //     cin >> input;
    //     cout << endl;
    //     cli.input(input);
    // }
}