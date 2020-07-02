/*
 * EasyGAL.cpp
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
#include "Translator/Translator.hpp"

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
	for (uint32_t i = 0; i < tables.size(); i++)
	{
		for (uint32_t pin : tables.at(i).m_InputPins)
			if (!inVec(inputPins, pin))
#ifdef LANG_DE
				printError("Pin " + to_string(pin) + " ist kein input Pin");
#else
				printError("pin " + to_string(pin) + " is not an input pin");
#endif

		if (!inVec(outputPins, tables.at(i).m_OutputPin))
#ifdef LANG_DE
			printError("pin " + to_string(tables.at(i).m_OutputPin) + " ist kein input Pin");
#else
			printError("pin " + to_string(tables.at(i).m_OutputPin) + " is not an output pin");
#endif

		if (pow(2, tables.at(i).m_InputPins.size()) != tables.at(i).m_Table.size())
#ifdef LANG_DE
			printError("Tabelle am output Pin " + to_string(tables.at(i).m_OutputPin) + " hat die falsche Form");
#else
			printError("table at output pin " + to_string(tables.at(i).m_OutputPin) + " has the wrong shape");
#endif
		for (uint32_t j = i + 1; j < tables.size(); j++)
		{
			if (tables.at(i).m_OutputPin == tables.at(j).m_OutputPin)
#ifdef LANG_DE
				printError("Tabelle am output Pin " + to_string(tables.at(i).m_OutputPin) + " wurde zweimal definiert");
#else
				printError("table at output pin " + to_string(tables.at(i).m_OutputPin) + " was defined twice");
#endif
		}
	}
}

int main(int argc, char *argv[])
{

	if (argc != 3)
#ifdef LANG_DE
		printError("Sie müssen einen Pfad zu ihrem EasyGAL Code angeben und als zweites argument die output datei");
#else
		printError("you have to suply a path to your EasyGAL code and the name for the output file");
#endif

	Parser parser = Parser(argv[1]);
	vector<TableData> tableData = parser.parse();

	vector<uint32_t> inputPins = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
	vector<uint32_t> outputPins = {14, 15, 16, 17, 18, 19, 20, 21, 22, 23};

	validate(tableData, inputPins, outputPins);

	Translator::Process(tableData, argv[2]);
}
