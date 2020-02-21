#pragma once
#include <string>
#include "../../Symbol.hpp"
#include "../../Error.hpp"

using namespace std;

namespace Preproces
{
string preProcessing(string);
string removeSpace(string);
bool validChar(char c);
} // namespace Preproces
