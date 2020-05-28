#include <iostream>
#include <string>
#include <vector>

#include "Lexer.h"

int main()
{
	std::vector<std::string> code;
	code.push_back("pin 1 =	a");
	code.push_back("");
	code.push_back("  ");
	code.push_back("a");
	code.push_back("b");
	code.push_back("test a pin table .		 ( ) // jjsjjs");
	code.push_back("count table 10001 002 233 bbs22");
	code.push_back("/*");
	code.push_back("multi line comment");
	code.push_back("*/");
	code.push_back("a");

	Lexer lexer = Lexer(code);

	while (!lexer.isFinished())
		std::cout << lexer.next().value << std::endl;
}
