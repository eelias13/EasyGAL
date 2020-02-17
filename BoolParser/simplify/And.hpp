#pragma once
#include <iostream>
#include <vector>
#include "../../Symbols.hpp"

namespace And
{
char truthTable(std::string);
std::string simplifyOne(std::string);
std::string simplify(std::string);
} // namespace And