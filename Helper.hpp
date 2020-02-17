#pragma once

#include <cstring>
#include <string>
#include <vector>

using namespace std;

namespace Helper 
{
	namespace String 
	{
		vector<string> Tokenize(const string& InputString, string Delimiters);
		vector<string> TokenizeEx(const string& InputString, string Delimiters);

		int Find(const string& String, char Character, unsigned int StartIndex = 0);
		int Find(const string& String, const string& Characters, unsigned int StartIndex = 0);
		int FindNot(const string& String, const string& Characters, unsigned int StartIndex = 0);

		bool IsNumber(const string& String);
	}
}
