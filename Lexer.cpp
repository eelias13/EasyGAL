#include "Lexer.h"

Lexer::Lexer(string path)
{

	inReader.open(path);
	currentChar = '\0';
	charIndex = 0;
	lineIndex = 0;

	eof = false;
	line = "";

	if (inReader.eof())
		lexingError("file is empty");

	nextChar();
}

Lexer::Lexer() {}

uint16_t Lexer::getLineIndex() { return lineIndex; }
bool Lexer::isFinished() { return eof; }

Token Lexer::next()
{
	if (eof)
		return {};

	token.value = "";

	lexComment();
	if (!token.value.empty())
		return next();

	lexSymbol();
	if (!token.value.empty())
		return token.type == Token::ignore ? next() : token;

	lexArrow();
	if (!token.value.empty())
		return token;

	lexBool();
	if (!token.value.empty())
		return token;

	lexNum();
	if (!token.value.empty())
		return token;

	lexWord();
	if (!token.value.empty())
		return token;

	lexingError("couldn't lex " + currentChar);
	return {};
}

// ------------------------------------ lex functions ------------------------------------
void Lexer::lexComment()
{
	if (currentChar != '/')
		return;

	token.value += currentChar;
	nextChar();

	if (currentChar == '/')
	{
		uint16_t lastLine = lineIndex;
		while (lastLine == lineIndex)
			nextChar();
		return;
	}

	if (currentChar == '*')
	{
		nextChar();

		char lastChar = currentChar;
		while (!(lastChar == '*' && currentChar == '/'))
		{
			lastChar = currentChar;
			nextChar();
		}
		nextChar();
		return;
	}

	lexingError("unexpected character " + token.value);
}

void Lexer::lexSymbol()
{
	switch (currentChar)
	{
	case '\n':
	case ' ':
	case '\t':
		token.value += currentChar;
		token.type = Token::Type::ignore;
		nextChar();
		break;
	case ',':
	case ';':
	case '.':
	case '(':
	case ')':
	case '{':
	case '}':
	case NOT:
	case OR:
	case AND:
	case XOR:
		token.value += currentChar;
		token.type = Token::Type::symbol;
		nextChar();
		break;
	default:
		break;
	}
}

void Lexer::lexArrow()
{
	if (currentChar != '=')
		return;

	token.value += currentChar;
	token.type = Token::Type::symbol;
	nextChar();

	if (currentChar == '>')
	{
		token.value += currentChar;
		nextChar();
	}
}

void Lexer::lexBool()
{
	if (currentChar != ZERO && currentChar != ONE)
		return;

	token.type = Token::Type::boolean;
	while (currentChar == ZERO || currentChar == ONE)
	{
		token.value += currentChar;
		nextChar();
	}

	if (isNum())
		lexNum();
}

void Lexer::lexNum()
{
	if (!isNum())
		return;

	token.type = Token::Type::number;
	while (isNum())
	{
		token.value += currentChar;
		nextChar();
	}
}

void Lexer::lexWord()
{
	if (isSpecial())
		return;

	while (!isSpecial())
	{
		token.value += currentChar;
		nextChar();
	}
	token.type = isKeyword() ? Token::Type::keyword : Token::Type::identifier;
}

// ------------------------------------ helpful functions ------------------------------------
bool Lexer::isNum()
{
	switch (currentChar)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return true;
	default:
		return false;
	}
}

bool Lexer::isKeyword()
{
	if (token.value == PIN)
		return true;

	if (token.value == TABLE)
		return true;

	if (token.value == FILL)
		return true;

	if (token.value == COUNT)
		return true;

	if (token.value == DFF)
		return true;

	return false;
}

bool Lexer::isSpecial()
{
	switch (currentChar)
	{
	case '=':
	case ';':
	case '.':
	case ',':
	case '\n':
	case ' ':
	case '\t':
	case '(':
	case ')':
	case '{':
	case '}':
	case NOT:
	case OR:
	case AND:
	case XOR:
	case '/':
		return true;
	default:
		return false;
	}
}

void Lexer::nextChar()
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

// ------------------------------------ error handling ------------------------------------
void Lexer::lexingError(string msg) { Error::makeError(Error::Type::lexing, lineIndex, msg); }