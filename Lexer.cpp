#include "Lexer.h"

Lexer::Lexer()
{
	isInit = false;
	current = 0;
	eof = true;
	charIndex = 0;
	charIndex = 0;
	lineIndex = 0;
}

uint16_t Lexer::getLineIndex()
{
	return lineIndex;
}

bool Lexer::isFinished()
{
	return eof;
}

void Lexer::init(char *path)
{
	inReader = std::ifstream(path);

	lineIndex = 1;
	charIndex = 0;

	if (!inReader)
		error("[IOError]: could not read file");
	inReader.getline(line, 255);
	nextChar();

	eof = false;
}

void Lexer::nextChar()
{
	if (eof)
	{
		current = 0;
		return;
	}

	if (line[charIndex] == 0)
	{
		if (inReader.eof())
		{
			eof = true;
			inReader.close();
			current = ' ';
			return;
		}

		charIndex = 0;
		lineIndex++;
		inReader.getline(line, 255);
		if (line[0] == 0)
		{
			lineIndex++;
			inReader.getline(line, 255);
			return nextChar();
		}
	}

	current = line[charIndex++];
}

std::string Lexer::next()
{
	if (isInit)
		error("you have to first initialize the Lexer before you use it");

	value = "";

	lexSpecial();
	if (!value.empty())
		return value;

	lexArrow();
	if (!value.empty())
		return value;

	lexBool();
	if (!value.empty())
		return value;

	lexNum();
	if (!value.empty())
		return value;

	lexWord();
	return value;
}

void Lexer::lexBool()
{
	if (current != ZERO && current != ONE)
		return;

	while (current == ZERO || current == ONE)
	{
		value += current;
		nextChar();
	}

	if (isNum())
		lexNum();
}

void Lexer::lexNum()
{
	if (!isNum())
		return;

	while (isNum())
	{
		value += current;
		nextChar();
	}
}

void Lexer::lexWord()
{
	if (isSpecial())
		return;

	while (!isSpecial())
	{
		value += current;
		nextChar();
	}
}

void Lexer::lexSpecial()
{
	switch (current)
	{
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
		value += current;
		nextChar();
	default:
		return;
	}
}

void Lexer::lexComment()
{
	if (current != '/')
		return;

	nextChar();

	if (current == '/')
	{
		uint16_t lastLine = lineIndex;
		while (lastLine == lineIndex)
			nextChar();
		return;
	}

	if (current == '*')
	{
		nextChar();

		char lastChar = current;
		while (!(lastChar == '*' && current == '/'))
		{
			lastChar = current;
			nextChar();
		}
		nextChar();
		return;
	}

	std::string msg = "unexpected character " + value + " at line ";
	msg += lineIndex;
	error(msg);
}

// void Lexer::lexArrow()
// {
// 	if (current != '=')
// 		return;

// 	value += current;
// 	nextChar();

// 	if (current == '>')
// 	{
// 		value += current;
// 		nextChar();
// 	}
// }

bool Lexer::isKeyword()
{

	if (value == PIN)
		return true;

	if (TABLE)
		return true;

	if (FILL)
		return true;

	if (COUNT)
		return true;

	if (DFF)
		return true;

	return false;
}

bool Lexer::isSpecial()
{
	switch (current)
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
	switch (current)
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
