#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>

#include "Compiler/Lexer/Lexer.hpp"
#include "Compiler/Lexer/Token.hpp"

#include "Compiler/PreCompiler/PreCompiler.hpp"

#include "Compiler/Compiler.hpp"

#include "Compiler/Linker/Linker.hpp"
#include "Compiler/TablesAndNames.hpp"

#include "TableData.hpp"
#include "Helper.hpp"
using namespace std;

void printTD(TableData);
void printTable(vector<bool>, vector<uint32_t>, uint32_t);