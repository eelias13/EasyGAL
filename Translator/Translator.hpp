#pragma once

#include <vector>

#include "DNF.hpp"
#include "Helper.hpp"
#include "TableData.hpp"

using namespace std;

/*
*	This is the interface which computes given truth tables to the JEDEC file format.
*	The Translator::Process is the entry point for the translator and processes everything translator related.
*/

namespace Translator 
{
	bool Process(vector<TableData> TruthTables);
}