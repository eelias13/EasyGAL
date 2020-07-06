/*
 * Validate.h
 *
 *  Created on: Jul 6, 2020
 *      Author: elias
 */

#include <string>
#include <vector>
#include <math.h>
#include <iostream>

#include "TableData.h"

namespace Validate
{
    void printError(string msg);
    bool inVec(vector<uint32_t> vec, uint32_t value);
    void validate(vector<TableData> tables, vector<uint32_t> inputPins, vector<uint32_t> outputPins);
} // namespace Validate

