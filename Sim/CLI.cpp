/*
 * CLI.cpp
 *
 *  Created on: Jul 6, 2020
 *      Author: elias
 */

#include "CLI.h"

CLI::CLI(Gal gal)
{
    this->gal = gal;
}

void CLI::input(string input)
{
    tokens = lex(input);
    quit();
    show();
}

void CLI::show()
{
    if (tokens.at(0) != "show")
        return;

    if (tokens.at(1) == "pin" && str2int(tokens.at(2)) != 0xff)

        if (tokens.at(1) == "output" && tokens.at(2) == "pins")
            for (uint32_t pin : gal.getOutputPins())
                cout << pin << " : " << gal.getOutputPin(pin) << ", " << endl;

    if (tokens.at(1) == "input" && tokens.at(2) == "pins")
        for (uint32_t pin : gal.getInputPins())
            cout << pin << " : " << gal.getInputPin(pin) << ", " << endl;

    if (tokens.at(1) == "data")
        for (TableData t : gal.getTabels())
            printTableData(t);
}

uint32_t CLI::str2Int(string str)
{
    uint32_t result = 0;
    for (uint32_t i = 0; i < str.size(); i++)
        if (getInt(str.at(i)) == 0xff)
            return 0xff;
        else
            result += getInt(str.at(i)) * pow(10, str.size() - i - 1);
    return result;
}

uint32_t CLI::getInt(char c)
{
    switch (c)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    default:
        return 0xff;
    }
}

void CLI::quit()
{
    if (!(tokens.at(0) == "exit" || tokens.at(0) == "quit" || tokens.at(0) == "q" || tokens.at(0) == "end"))
        return;

    cout << "ending simulation" << endl;
    exit(0);
}

vector<string> CLI::lex(string input)
{
    vector<string> result;

    string temp = "";
    for (char c : input)
        if (c == ' ')
        {
            if (!(input.size() == 0 || (input.size() == 1 && input.at(0) == ' ')))
                result.push_back(temp);
            temp = "";
        }
        else
            temp += c;
}

void CLI::printTableData(TableData tableData)
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