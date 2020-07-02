#include "Translator.hpp"

/*
*		Translator::Process is the 'main' of the translator. The data processing happens in here in the following order:
*		TableData -> DNF::Expression -> Fuses -> JEDEC -> File on Disk. The boolean return value indicates if the translation
*		was a success and if the JEDEC file was written to the harddrive.
*/

bool Translator::Process(vector<TableData> TruthTables, std::string Filename)
{
	vector<DNF::Expression> Expressions;

	if(!DNF::Build(TruthTables, Expressions))
	{
		ERROR("%s", "couldn't build all DNF expressions");
		return false;
	}

	std::vector<bool> Fuses;

	if(!Fuses::Build(Expressions, Fuses))
	{
		ERROR("%s", "couldn't generate all fuses for given expressions");
		return false;
	}
	
	try
	{
		JEDEC(24, 5892, Fuses, Filename).Serialize();
	}
	catch(std::exception Error)
	{
		ERROR("%s", "couldn't serialize data");
		return false;
	}

	return true;
}

