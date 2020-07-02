#include "Fuses.h"

bool Fuses::Build(vector<DNF::Expression> Expressions, vector<bool>& FuseListOut)
{
	if (!Expressions.size())
	{
		ERROR("%s", "No expressions were given");
		return false;			
	}

	if (FuseListOut.size())
		FuseListOut.clear();

	//	Adjust fuselist size to the fuse list size of the integrated circuit.

	FuseListOut.resize(5892);
	
	//	Set AR Fuses to zero (we don't need them as of yet)

	std:fill(FuseListOut.begin(), FuseListOut.begin() + 44, false);
	
	//	Start writing expressions to FuseList.

	for(uint32_t Index = 0; Index < Expressions.size(); Index++)
	{
		uint32_t ExpIndexStart = [Expressions, Index]() -> uint32_t
		{
			uint32_t FuseIndex = 44;

			for (uint32_t OLMC = 23; OLMC > Expressions[Index].m_OutputPin; OLMC--)
				FuseIndex += (Fuses::Output::MaximumTerms(OLMC) + 1) * 44;
			
			return FuseIndex;
		}();

		vector<bool> ExpressionBuffer;

		if (!Fuses::BuildFromExpression(Expressions[Index], Fuses::Output::MaximumTerms(Expressions[Index].m_OutputPin) + 1, 44, ExpressionBuffer)) 
		{
			ERROR("%s", "Couldn't build all expression fuses");
			return false;
		}

		//	Copy ExpressionBuffer into the correct target destination in the fuse matrix.

		std::copy(ExpressionBuffer.begin(), ExpressionBuffer.end(), FuseListOut.begin() + ExpIndexStart);
	}

	//	Set SP fuses to zero because we also don't need them as of yet.

	std::fill(FuseListOut.begin() + 5764, FuseListOut.begin() + 5764 + 44, false);

	//	Set S0 & S1 fuses.

	for(DNF::Expression Expression : Expressions)
	{
		pair<uint32_t, uint32_t> ModeFuses;

		if(!Fuses::Output::ModeFuseIndices(Expression.m_OutputPin, ModeFuses))
		{
			ERROR("%s", "Invalid PIN");
			return false;
		}

		if(Expression.m_EnableFlipFlop)
		{
			FuseListOut[ModeFuses.first] = 1;
			FuseListOut[ModeFuses.second] = 0;
		}
		else
		{
			FuseListOut[ModeFuses.first] = 1;
			FuseListOut[ModeFuses.second] = 1;
		}
	}

	return true;
}

/*
*		Fuses::BuildFromExpression generates a fuselist for a specific expression and outputs the result in a supplied 
*		fuselist. It needs to know the term size and number of rows to correctly pad the fuselist with zeroes. 
*/

bool Fuses::BuildFromExpression(DNF::Expression Expression, uint32_t iNumRows, uint32_t iRowLength, vector<bool>& FuseList)
{
	if(!Fuses::Output::IsValid(Expression.m_OutputPin))
	{
		ERROR("%s", "Expression has invalid output pin");
		return false;
	}
	else if (!Expression.m_Rows.size() || !iNumRows || !iRowLength)
	{
		ERROR("%s", "Invalid parameters");
		return false;
	}
	else if (Expression.m_Rows.size() > Fuses::Output::MaximumTerms(Expression.m_OutputPin))
	{
		ERROR("%s", "Too many terms for given output pin");
		return false;
	}

	if (FuseList.size())
		FuseList.clear();

	FuseList.resize(iNumRows * iRowLength);

	//	Enable Output.

	std::fill(FuseList.begin(), FuseList.begin() + iRowLength, true);
	
	//	Start writing DNF terms.

	for(uint32_t TermIndex = 0; TermIndex < Expression.m_Rows.size(); TermIndex++)
	{
		std::fill(FuseList.begin() + iRowLength + TermIndex * iRowLength, FuseList.begin() + iRowLength + TermIndex * iRowLength + iRowLength, true);

		for(uint32_t PinIndex = 0; PinIndex < Expression.m_Rows[TermIndex].m_Pins.size(); PinIndex++)
		{
			int Index = Fuses::PinToIndex
			(
				Expression.m_Rows[TermIndex].m_Pins[PinIndex].m_PinNumber,
				Expression.m_Rows[TermIndex].m_Pins[PinIndex].m_Inverted,
				Expression.m_EnableFlipFlop ? MacrocellMode::MODE_REGISTERED_HIGH : MacrocellMode::MODE_COMBINATORIAL_HIGH
			);

			if(Index == -1)
			{
				ERROR("%s", "Couldn't resolve PIN index");
				return false;
			}

			FuseList[iRowLength + TermIndex * iRowLength + Index] = false;
		}
	}

	return true;
}

/*
*		Fuses::PinToIndex converts a PIN to a fuselist row index. It takes in a PIN number and a boolean
*		which indicates if the PIN is supposed to be inverted. It requires an extra parameter if the given  
*		PIN number correlates to an output pin. This parameter is called "Mode" and is an enum. The parameter
*		is needed because the output from the OLMC is inverted or not inverted depending on the mode it is
*		operating in (the mode is set through S0 and S1 fuses) so we need to know the mode to correctly pick
*		the inverted or non inverted output from the OLMC output. 
*		
*		Note: The "Mode" parameter is ignored if the PIN number correlates to an input pin. If the PIN is an 
*		output pin and the parameter is not set the function will return -1 which is not a valid index.
*		
*		Note: If the return value is -1 that means that the function couldn't find a valid index for the given
*		parameters.
*/

int Fuses::PinToIndex(uint32_t iPinNumber, bool bInverted, MacrocellMode Mode)
{
	//	INPUT PINS

	switch(iPinNumber)
	{
		case 1: return bInverted ? 1 : 0;
		case 2: return bInverted ? 5 : 4;
		case 3: return bInverted ? 9 : 8;
		case 4: return bInverted ? 13 : 12;
		case 5: return bInverted ? 17 : 16;
		case 6: return bInverted ? 21 : 20;
		case 7: return bInverted ? 25 : 24;
		case 8: return bInverted ? 29 : 28;
		case 9: return bInverted ? 33 : 32;
		case 10: return bInverted ? 37 : 36;
		case 11: return bInverted ? 41 : 40;
		case 13: return bInverted ? 43 : 42;
	}

	//	OUTPUT PINS

	if(Mode == MacrocellMode::MODE_COMBINATORIAL_HIGH)
	{
		switch (iPinNumber)
		{
			case 14: return bInverted ? 39 : 38;
			case 15: return bInverted ? 35 : 34;
			case 16: return bInverted ? 31 : 30;
			case 17: return bInverted ? 27 : 26;
			case 18: return bInverted ? 23 : 22;
			case 19: return bInverted ? 19 : 18;
			case 20: return bInverted ? 15 : 14;
			case 21: return bInverted ? 11 : 10;
			case 22: return bInverted ? 7 : 6;
			case 23: return bInverted ? 3 : 2;
		}
	}
	else if(Mode != MacrocellMode::MODE_NONE)
	{
		switch (iPinNumber)
		{
			case 14: return bInverted ? 38 : 39;
			case 15: return bInverted ? 34 : 35;
			case 16: return bInverted ? 30 : 31;
			case 17: return bInverted ? 26 : 27;
			case 18: return bInverted ? 22 : 23;
			case 19: return bInverted ? 18 : 19;
			case 20: return bInverted ? 14 : 15;
			case 21: return bInverted ? 10 : 11;
			case 22: return bInverted ? 6 : 7;
			case 23: return bInverted ? 2 : 3;
		}
	}

	//	Return -1 if we couldn't find an index which fits the given parameters.

	return -1;
}

/*
*		Fuses::Output::MaximumTerms returns the maximum amount of terms an output OLMC can handle.
*		if the function return value is -1 it means that the given pin number is not an valid output pin
*		thus the function can't return a valid term number.
*/

int Fuses::Output::MaximumTerms(uint32_t iPinNumber)
{
	switch (iPinNumber)
	{
		case 14: return 8;
		case 15: return 10;
		case 16: return 12;
		case 17: return 14;
		case 18: return 16;
		case 19: return 16;
		case 20: return 14;
		case 21: return 12;
		case 22: return 10;
		case 23: return 8;
		default: return -1;
	}
}

//		Fuses::Output::IsValid checks if a given pin is an output pin:

bool Fuses::Output::IsValid(uint32_t iPinNumber)
{
	return iPinNumber >= 14 && iPinNumber <= 23 ? true : false;
}

/*
*		Fuses::Output::ModeFuseIndices returns the mode control fuses for a given output pin.
*		The return value is a boolean which indicates if the fuse pair was written to the given 
*		std::pair reference. The function will only return false if the given pin number is
*		an input pin who has no OLMC connected and therefore no control mode pin.
*/

bool Fuses::Output::ModeFuseIndices(uint32_t iPinNumber, pair<uint32_t, uint32_t>& FusesOut)
{
	if (!Fuses::Output::IsValid(iPinNumber))
		return false;

	switch(iPinNumber)
	{
		case 23: FusesOut = pair<uint32_t, uint32_t>(5808, 5809); break;
		case 22: FusesOut = pair<uint32_t, uint32_t>(5810, 5811); break;
		case 21: FusesOut = pair<uint32_t, uint32_t>(5812, 5813); break;
		case 20: FusesOut = pair<uint32_t, uint32_t>(5814, 5815); break;
		case 19: FusesOut = pair<uint32_t, uint32_t>(5816, 5817); break;
		case 18: FusesOut = pair<uint32_t, uint32_t>(5818, 5819); break;
		case 17: FusesOut = pair<uint32_t, uint32_t>(5820, 5821); break;
		case 16: FusesOut = pair<uint32_t, uint32_t>(5822, 5823); break;
		case 15: FusesOut = pair<uint32_t, uint32_t>(5824, 5825); break;
		case 14: FusesOut = pair<uint32_t, uint32_t>(5826, 5827); break;
	}

	return true;
}

