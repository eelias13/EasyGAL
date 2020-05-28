#include "Lexer.h"

Lexer::Lexer(std::vector<std::string> code)
{
	this->code = code;
	eof = false;
	lineIndex = 0;
	charIndex = 0;
}

uint16_t Lexer::getLineIndex()
{
	return lineIndex;
}

bool Lexer::isFinished()
{
	return eof;
}

void Lexer::nextChar()
{
	if (eof)
		return;

	if (lineIndex == code.size())
	{
		eof = true;
		return;
	}

	line = code.at(lineIndex);

	if (charIndex == line.size())
	{
		charIndex = 0;
		lineIndex++;
		currentChar = '\n';
		return;
	}

	if (line.empty())
	{
		charIndex = 0;
		lineIndex++;
		currentChar = '\n';
		return;
	}

	currentChar = line.at(charIndex);
	charIndex++;
}

Token Lexer::next()
{
	if (eof)
		return {};

	token.value = "";

	lexComment();
	if (token.value != "")
		return next();

	lexSymbol();
	if (token.value != "")
		return token.type == Token::ignore ? next() : token;

	lexArrow();
	if (token.value != "")
		return token;

	lexBool();
	if (token.value != "")
		return token;

	lexNum();
	if (token.value != "")
		return token;

	lexWord();
	return token;
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
	token.type = isKeyword() ? Token::Type::identifier : Token::Type::keyword;
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
	case P_OPEN:
	case P_CLOSE:
	case CP_OPEN:
	case CP_CLOSE:
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

	std::string msg = "unexpected character " + token.value + " at line ";
	msg += lineIndex;
	// error(msg);
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
	case P_OPEN:
	case P_CLOSE:
	case CP_OPEN:
	case CP_CLOSE:
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