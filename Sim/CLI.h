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

private:
    void printTableData(TableData tableData);
    vector<string> lex(string input);
    bool isEmpty(string input);
    void quit();
    void show();

    uint32_t str2int(string str);
    uint32_t getInt(char c);

public:
    void input(string input);

public:
    CLI(Gal gal);
};
