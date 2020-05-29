#include <iostream>
#include <string>
#include <vector>

#include "Parser.h"
#include "TableData.h"

int main()
{
	Parser parser = Parser("code.txt");
	vector<TableData> tableData = parser.parse();
}
