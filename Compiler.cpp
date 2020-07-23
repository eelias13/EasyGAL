/*
 * EasyGAL.cpp
 *
 *  Created on: May 28, 2020
 *      Author: elias
 */

#include <iostream>
#include <vector>

#include "Shared/Validate.h"
#include "Shared/TableData.h"
#include "Shared/Dependencies/json.hpp"

#include "Parser/Parser.h"
#include "Parser/Error.h"

#include "Translator/Translator.hpp"
#include "Translator/Configs.h"

using namespace std;

// printTableData is for debuging
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

void showHelpMenu()
{
	cout << "usage of EasyGAL: " << endl;
	cout << '\t' << "EasyGAL [EasyGAl code] [name of output jedec] [gal type]" << endl;
	cout << "Exampel:" << endl;
	cout << '\t' << "EasyGAL code.txt out.jedec g22v10" << endl;
}

int main(int argc, char *argv[])
{
	if (argv[1] == "help")
	{
		showHelpMenu();
		exit(0);
	}

	if (argc != 4)
	{
		cerr << "invalid argument count" << endl;
		showHelpMenu();
		exit(1);
	}
	string easyGALCode = argv[1];
	string outputFileName = argv[2];
	string deviceName = argv[3];

	Parser parser = Parser(easyGALCode);
	vector<TableData> tableData = parser.parse();

	Configs::CircuitConfig DeviceType;
	if (!Configs::Load(deviceName.c_str(), &DeviceType))
	{
		cerr << "Couldn't get config for device" << deviceName << endl;
		exit(1);
	}

	vector<uint32_t> inputPins = DeviceType.m_Inputs;
	for (uint32_t i = 0; i < DeviceType.m_SpecialPins.size(); i++)
		inputPins.push_back(DeviceType.m_SpecialPins.at(i).first);

	vector<uint32_t> outputPins;
	for (uint32_t i = 0; i < DeviceType.m_Outputs.size(); i++)
		outputPins.push_back(DeviceType.m_Outputs.at(i).first);

	validate(tableData, inputPins, outputPins);

	Translator::Process(tableData, DeviceType, outputFileName);

	cout << "compilation successfully, one new file was created " << outputFileName << endl;
}