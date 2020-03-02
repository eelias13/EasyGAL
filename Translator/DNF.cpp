#include "DNF.hpp"

using namespace DNF;

/*
*	DNF::Build(TableData) builds a DNF expression from a TableData datastructure.
*	It's return value is optional, because the function can fail in case the supplied
*	TableData structure is faulty. The expression is returned in the DNF::Expression datastructure.
*/

optional<Expression> DNF::Build(TableData& TruthTable)
{
	if (TruthTable.m_InputPins.size() > MAX_INPUTS) 
	{
		ERROR("%s", "Too many inputs");
		return {};
	} 
	else if(TruthTable.m_Table.size() != pow(2, TruthTable.m_InputPins.size()))
	{ 
		ERROR("%s", "Truth table size doesn't match input bits");
		return {};
	}

	vector<Row> Rows;

	for(uint32_t Index = 0; Index < TruthTable.m_Table.size(); Index++)
	{
		if(TruthTable.m_Table[Index])
		{
			Rows.push_back(BuildRow(bitset<MAX_INPUTS>(Index), TruthTable.m_InputPins));
		}
	}

	return Expression(TruthTable.m_OutputPin, TruthTable.m_EnableFlipFlop, Rows);
}

/*
*	DNF::Build(vector<TableData>&, vector<Expression>*) is basically a wrapper for DNF::Build(TableData)
*	and is able to build multiple DNF expressions at once by receiving a vector of TableData datastructures.
*	It stores the result in a vector which you need to supply to the function by pointer. The function
*	returns a boolean which indicates if the building of all expressions was successful.
*/

bool DNF::Build(vector<TableData>& TruthTables, vector<Expression>* pExpressionsOut)
{
	if (pExpressionsOut == nullptr)
	{
		ERROR("%s", "pExpressionsOut was nullpointer");
		return false;
	}

	vector<Expression> Expressions;

	for(TableData TruthTable : TruthTables)
	{
		optional<Expression> CurExpression = Build(TruthTable);

		if (CurExpression.has_value() == false)
		{
			ERROR("%s", "Couldn't build all DNF expressions");
			return false;
		}

		Expressions.push_back(*CurExpression);
	}

	*pExpressionsOut = Expressions;

	return true;
}

/*
*	DNF::BuildRow builds rows of chained "and" statements which always turn out true based off the input bits.
*	You have to supply the input pin numbers, so the function can "name" the variables used in the row.
*	The result is returned in the DNF::Row datastructure.
*/

Row DNF::BuildRow(bitset<MAX_INPUTS> Bits, vector<uint32_t> Inputs)
{
	vector<Pin> Pins;

	for(uint32_t Index = 0; Index < Inputs.size(); Index++)
	{
		if (Bits[Inputs.size() - 1 - Index] == false)
			Pins.push_back(Pin(true, Inputs[Index]));
		else
			Pins.push_back(Pin(false, Inputs[Index]));
	}

	return Row(Pins);
}

