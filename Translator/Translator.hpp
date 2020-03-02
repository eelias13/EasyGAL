#pragma once

/*
*	This is the interface which computes given truth tables to the JEDEC file format.
*	The Translator::Process is the entry point for the translator and processes everything translator related.
*/

#include <vector>

#include "DNF.hpp"
#include "Helper.hpp"
#include "TableData.hpp"

using namespace std;

namespace Translator 
{
	bool Process(vector<TableData> TruthTables);
}