#pragma once

#include <bitset>

#include "Helper.hpp"
#include "TableData.hpp"

namespace DNF 
{
	//	DNF::Pin stores a pin number and if it is inverted.

	struct Pin 
	{
		bool m_Inverted;
		uint32_t m_PinNumber;
	};

	//	DNF::Row stores pins which represent one logical "and" row in a DNF.

	struct Row 
	{ 
		vector<Pin> m_Pins; 
	};

	//	DNF::Expression stores all "and" rows which are or'd together in the DNF expression.

	struct Expression 
	{
		vector<Row> m_Rows; 
	};

	Expression ConvertTruthTable(TableData TruthTable);
	vector<Expression> ConvertTruthTables(vector<TableData> TruthTables);
}