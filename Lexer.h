#ifndef LEXER_H_
#define LEXER_H_

#include <cstdint>
#include <fstream>
#include <strings.h>

#include "Symbols.h"
#include "Error.h"

class Lexer
{

public:
	void init(char *);
	std::string next();
	bool isFinished();
	uint16_t getLineIndex();

private:
	char current;
	char line[255];
	uint16_t lineIndex;
	uint8_t charIndex;
	std::ifstream inReader;

	bool eof;
	bool isInit;

	std::string value;

public:
	Lexer();

private:
	void lexBool();
	void lexNum();
	void lexWord();
	void lexArrow();
	void lexSpecial();
	void lexComment();

	bool isNum();
	bool isSpecial();
	bool isKeyword();

	void nextChar();
	void init();
};

#endif /* LEXER_H_ */
