/*
 * Gal.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: elias
 */

#ifndef GAL_H_
#define GAL_H_

#include <vector>
#include <string>
#include <cstdint>
#include <utility>
#include <iostream>
#include <math.h>

#include "../Shared/TableData.h"

class Gal
{
private:
    vector<TableData> tables;

    vector<uint32_t> inputPins;
    vector<bool> inputValues;

    vector<uint32_t> outputPins;
    vector<bool> outputValues;

private:
    void eval();
    void error(string msg);
    uint32_t bool2Int(vector<bool> boolVec);

public:
    Gal(vector<TableData> tables, vector<uint32_t> inputPins, vector<uint32_t> outputPins);
    Gal(vector<TableData> tables, vector<uint32_t> inputPins, vector<uint32_t> outputPins, bool initValue);

public:
    void setInputPin(uint32_t pin, bool value);
    bool getOutputPin(uint32_t pin);

private:
    void setOutputPin(uint32_t pin, bool value);
    bool getInputPin(uint32_t pin);
};

#endif /* GAL_H_ */