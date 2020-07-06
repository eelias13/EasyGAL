/*
 * Gal.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: elias
 */

#include "Gal.h"

Gal::Gal(vector<TableData> tables, vector<uint32_t> inputPins, vector<uint32_t> outputPins)
{
    this->tables = tables;
    this->inputPins = inputPins;
    this->outputPins = outputPins;

    for (uint32_t i = 0; i < outputPins.size(); i++)
        outputValues.push_back(false);
    for (uint32_t i = 0; i < inputPins.size(); i++)
        inputValues.push_back(false);

    eval();
}

Gal::Gal(vector<TableData> tables, vector<uint32_t> inputPins, vector<uint32_t> outputPins, bool initValue)
{
    this->tables = tables;
    this->inputPins = inputPins;
    this->outputPins = outputPins;

    for (uint32_t i = 0; i < outputPins.size(); i++)
        outputValues.push_back(false);
    for (uint32_t i = 0; i < inputPins.size(); i++)
        inputValues.push_back(initValue);

    eval();
}

void Gal::setInputPin(uint32_t pin, bool value)
{
    for (uint32_t i = 0; i < inputPins.size(); i++)
        if (inputPins.at(i) == pin)
            inputValues.at(i) = value;
    eval();
}

void Gal::setOutputPin(uint32_t pin, bool value)
{
    for (uint32_t i = 0; i < outputPins.size(); i++)
        if (outputPins.at(i) == pin)
            outputValues.at(i) = value;
}

bool Gal::getOutputPin(uint32_t pin)
{
    for (uint32_t i = 0; i < outputPins.size(); i++)
        if (outputPins.at(i) == pin)
            return outputValues.at(i);
    return 0xff;
}

bool Gal::getInputPin(uint32_t pin)
{
    for (uint32_t i = 0; i < inputPins.size(); i++)
        if (inputPins.at(i) == pin)
            return inputValues.at(i);
    cout << "error" << endl;
    return false;
}

void Gal::eval()
{
    for (TableData table : tables)
    {

        vector<bool> index;
        for (uint32_t pin : table.m_InputPins)
            index.push_back(getInputPin(pin));

        setOutputPin(table.m_OutputPin, table.m_Table.at(bool2Int(index)));
    }
}

uint32_t Gal::bool2Int(vector<bool> boolVec)
{
    uint32_t result = 0;
    for (uint32_t i = 0; i < boolVec.size(); i++)
        if (boolVec.at(i))
            result += pow(2, boolVec.size() - i - 1);
    return result;
}

void Gal::error(string msg)
{
    cout << msg << endl;
    exit(0);
}