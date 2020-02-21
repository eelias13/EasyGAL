#pragma once
#include <string>

#include "../../Symbol.hpp"
#include "Preproces.hpp"
#include "../../Error.hpp"

#include "simplify/And.hpp"
#include "simplify/Or.hpp"
#include "simplify/Xor.hpp"
#include "simplify/Not.hpp"
#include "simplify/Parentheses.hpp"

using namespace std;

namespace Parser
{
char parse(string);
string parseRecursiv(string);
} // namespace Parser