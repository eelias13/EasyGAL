/*
 * CLI.h
 *
 *  Created on: Jul 6, 2020
 *      Author: elias
 */

#include <iostream>

#include "Gal.h"
#include "../Shared/TableData.h"

using namespace std;

class CLI
{
private:
    Gal gal;
    vector<string> tokens;
    string next;

private:
    void printTableData(TableData tableData);

private:
    void show();
    void set();
    void help();
    void add();

private:
    bool inOutput(uint32_t pin);
    bool inInput(uint32_t pin);

public:
    void run();

public:
    CLI(Gal gal);
};
