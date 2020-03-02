#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>
#include <fstream>

#include "Compiler/Compiler.hpp"
#include "Translator/TableData.hpp"

using namespace std;

vector<string> ReadFile(string Path);
vector<int> getValidPins(string InStr);

void printTD(TableData);
void printTable(vector<bool>, vector<uint32_t>, uint32_t);
