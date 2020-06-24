/*
 * Error.cpp
 *
 *  Created on: May 28, 2020
 *      Author: elias
 */

#include <iostream>

#include <string>
#include <vector>
#include <math.h>

#include "Compiler/Parser.h"
#include "Shared/TableData.h"
#include "Shared/Error.h"

using namespace std;

void printTableData(TableData tableData)
{
	cout << "output pin: " << tableData.m_OutputPin << endl;

	cout << "input pins:";
	for (uint32_t pin : tableData.m_InputPins)
		cout << " " << pin;
	cout << endl;

	cout << "table:\t    ";
	for (bool b : tableData.m_Table)
		cout << b;
	cout << endl;

	cout << "is dff:\t    " << tableData.m_EnableFlipFlop << endl;

	cout << endl;
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
	for (TableData table : tables)
	{
		for (uint32_t pin : table.m_InputPins)
			if (!inVec(inputPins, pin))
				printError("pin " + to_string(pin) + " is not an input pin");

		if (!inVec(outputPins, table.m_OutputPin))
			printError("pin " + to_string(table.m_OutputPin) + " is not an output pin");

		if (pow(2, table.m_InputPins.size()) != table.m_Table.size())
			printError("tabel at output pin " + to_string(table.m_OutputPin) + " has the wrong shape");
	}
}

int main()
{
	string path = "code.txt";

	Parser parser = Parser(path);
	vector<TableData> tableData = parser.parse();

	vector<uint32_t> inputPins = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
	vector<uint32_t> outputPins = {14, 15, 16, 17, 18, 19, 20, 21, 22, 23};

	validate(tableData, inputPins, outputPins);

	for (TableData td : tableData)
		printTableData(td);
}
