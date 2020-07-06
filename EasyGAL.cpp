/*
 * EasyGAL.cpp
 *
 *  Created on: May 28, 2020
 *      Author: elias
 */

#include <iostream>
#include <vector>

#include "Shared/TableData.h"
#include "Shared/Validate.h"
#include "Parser/Parser.h"
#include "Parser/Error.h"
#include "Translator/Translator.hpp"

using namespace std;

// for debuging
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



int main(int argc, char *argv[])
{
	if (argc != 3)
		Error::printError("you have to suply a path to your EasyGAL code and the name for the output file");

	Parser parser = Parser(argv[1]);
	vector<TableData> tableData = parser.parse();

	vector<uint32_t> inputPins = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
	vector<uint32_t> outputPins = {14, 15, 16, 17, 18, 19, 20, 21, 22, 23};

	Validate::validate(tableData, inputPins, outputPins);

	Translator::Process(tableData, argv[2]);
}