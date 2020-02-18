#pragma once
#include <iostream>
#include <vector>
#include "../Symbols.hpp"

using namespace std;

void ERROR(string);

namespace Preproces
{

string preProcessing(string);
string removeSpace(string);
bool validChar(char c);

} // namespace Preproces
