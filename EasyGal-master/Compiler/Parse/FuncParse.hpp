#include <iostream>
#include <vector>
#include "BoolParser/Parser.hpp"

using namespace std;

namespace FuncParse
{
string boolFunc2table(string, vector<string>);
string substitute(string, string, vector<string>);
namespace Helper
{
bool isVarValide(vector<string>);
bool validChar(char);
vector<string> sortByLen(vector<string>);
vector<string> findeVarInFunc(string);
vector<string> removeDoubleVar(vector<string>);
string removeChar(string, char);
string replace(string, char, char);
string replaceStr(string, string, string);
vector<string> generateTable(int);
} // namespace Helper
} // namespace FuncParse