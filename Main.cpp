#include <iostream>
#include <string>
#include <vector>

#include "Parser.h"
#include "TableData.h"

string int2Str(uint32_t i);
char getChar(uint32_t i);
uint32_t getInt(char c);

using namespace std;

int main()
{
	Parser parser = Parser("code.txt");
	vector<TableData> tableData = parser.parse();
}