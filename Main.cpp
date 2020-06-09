#include <iostream>
#include <string>
#include <vector>
#include <utility>

// #include "Parser.h"
#include "TableData.h"
#include "Token.h"
#include "Symbols.h"

#include "FunctionParser.h"

using namespace std;

void printToken(Token token);
vector<Token> lex(string str);

int main()
{

	vector<Token> expression = lex("a|b");

	FunctionParser fp = FunctionParser();
	vector<string> names = fp.getNames(expression);
	for (string name : names)
		cout << name << endl;
	fp.parse(expression, 0);
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
