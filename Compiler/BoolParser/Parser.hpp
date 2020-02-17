#pragma once
#include <iostream>
#include <vector>

#include "../Symbols.hpp"
#include "Preproces.hpp"

#include "simplify/And.hpp"
#include "simplify/Or.hpp"
#include "simplify/Xor.hpp"
#include "simplify/Not.hpp"
#include "simplify/Parentheses.hpp"

namespace Parser
{
bool isCharValid(char);
bool isValid(std::string);
} // namespace Parser