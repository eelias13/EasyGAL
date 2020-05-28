#ifndef LEXER_H_
#define LEXER_H_

#include <cstdint>
#include <string>
#include <vector>

#include "Symbols.h"
// #include "Error.h"
#include "Token.h"

class Lexer
{

public:
	Token next();
	bool isFinished();
	uint16_t getLineIndex();

private:
	uint16_t lineIndex;
	uint16_t charIndex;
	std::string line;
	bool eof;
	std::vector<std::string> code;

	char currentChar;
	Token token;

public:
	Lexer(std::vector<std::string>);

private:
	void lexBool();
	void lexNum();
	void lexWord();
	void lexArrow();
	void lexSymbol();
	void lexComment();

	bool isNum();
	bool isSpecial();
	bool isKeyword();

	void nextChar();
	void init();
};

#endif /* LEXER_H_ */
