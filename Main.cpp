#include <iostream>
#include <string>
#include <vector>

#include "Parser.h"
#include "TableData.h"

#include "FunctionParser.h"

using namespace std;

void printToken(Token token);
vector<Token> lex(string str);

int main()
{

	FunctionParser fp = FunctionParser();
	fp.test(lex("!a|b&c&d|f"));
}

vector<Token> lex(string str)
{
	vector<Token> tokens;
	for (char c : str)
	{
		Token token;
		token.value = c;
		switch (c)
		{
		case '(':
		case ')':
		case '{':
		case '}':
		case NOT:
		case OR:
		case AND:
		case XOR:
			token.type = Token::Type::symbol;
			break;
		default:
			token.type = Token::Type::identifier;
			break;
		}
		tokens.push_back(token);
	}
	return tokens;
}
