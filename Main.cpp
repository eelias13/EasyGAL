#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>

#include "Parser.h"
#include "TableData.h"

#include "Lexer.h"
#include "Token.h"
#include "Symbols.h"
// #include "FunctionParser.h"

using namespace std;

class Main
{
public:
	char currentChar;
	uint32_t charIndex;
	uint32_t lineIndex;
	fstream inReader;
	bool eof;
	string line;

public:
	void nextChar();
	Main(string);
};

Main::Main(string path)
{
	inReader.open(path);
	currentChar = '\0';
	charIndex = 0;
	lineIndex = 0;

	eof = false;
	line = "";
}

void Main::nextChar()
{
	if (eof)
	{
		currentChar = 0;
		return;
	}

	if (line.size() == 0 || charIndex == line.size())
	{

		if (getline(inReader, line))
		{

			lineIndex++;
			charIndex = 0;

			if (line.empty())
				return nextChar();
		}
		else
		{
			eof = true;
			currentChar = 0;
			return;
		}
	}

	currentChar = line.at(charIndex);
	charIndex++;
}

void printTableData(TableData tableData)
{
	cout << "output pin: " << tableData.m_OutputPin << endl;

	cout << "input pins:";
	for (uint32_t pin : tableData.m_InputPins)
		cout << " " << pin;
	cout << endl;

	cout << "table:\t    ";
	for (bool b : tableData.m_Table)
		cout << b;
	cout << endl;

	cout << "is dff:\t    " << tableData.m_EnableFlipFlop << endl;

	cout << endl;
}

int main()
{
	string path = "code.txt";

	// Main main = Main(path);
	// uint32_t old = 1;
	// while (!main.eof)
	// {
	// 	main.nextChar();
	// 	if (old != main.lineIndex)
	// 	{
	// 		cout << endl;
	// 		old = main.lineIndex;
	// 	}
	// 	cout << main.currentChar;
	// }
	// cout << endl;

	Parser parser = Parser(path);
	vector<TableData> tableData = parser.parse();

	for (TableData td : tableData)
		printTableData(td);

	// Lexer lexer = Lexer(path);
	// uint32_t old = 0;
	// while (!lexer.isFinished())
	// {
	// 	cout << lexer.next().value << " ";
	// 	if (old != lexer.getLineIndex())
	// 	{
	// 		cout << endl;
	// 		old = lexer.getLineIndex();
	// 	}
	// }
}
