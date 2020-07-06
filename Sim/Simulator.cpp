/*
 * Simulator.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: elias
 */

#include <iostream>
#include "Gal.h"

#include <string>
#include <cstdint>
#include <utility>
#include <math.h>

#include "../Shared/TableData.h"

using namespace std;

void error(string msg)
{
    cout << msg << endl;
    exit(1);
}

int main()
{
    // load dummy data
    vector<TableData> tables = {
        {{10, 11, 12}, 0, {false, false, false, false, true, true, true, true}, false},
        {{13, 14}, 1, {false, false, false, true}, false}};
    vector<uint32_t> inputPins = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    vector<uint32_t> outputPins = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    Gal gal = Gal(tables, inputPins, outputPins);
    gal.setInputPin(13, true);
    cout << gal.getOutputPin(1) << endl;
    gal.setInputPin(14, true);
    cout << gal.getOutputPin(1) << endl;
}
