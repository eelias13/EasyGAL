#pragma once

#include <vector>
#include <cstring>
#include <string>

using namespace std;

namespace Helper
{
	namespace String
	{
		vector<string> Tokenize(const string &InputString, string Delimiters);
		vector<string> TokenizeEx(const string &InputString, string Delimiters);

		int Find(const string &String, char Character, unsigned int StartIndex = 0);
		int Find(const string &String, const string &Characters, unsigned int StartIndex = 0);
		int FindNot(const string &String, const string &Characters, unsigned int StartIndex = 0);

		bool IsNumber(const string &String);
	}
} 