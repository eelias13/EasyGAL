/*
 * Error.cpp
 *
 *  Created on: May 28, 2020
 *      Author: elias
 */

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <math.h>

#include "Compiler/Parser.h"
#include "Shared/TableData.h"

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

int main()
{
	string path = "code.txt";

	Parser parser = Parser(path);
	vector<TableData> tableData = parser.parse();

	for (TableData td : tableData)
		printTableData(td);
}
