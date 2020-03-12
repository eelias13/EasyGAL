#pragma once
#include <string>
#include "../../Symbol.hpp"
using namespace std;

namespace Or
{
string simplefyOr(string exp);
string simplefyOneOr(string exp);
char truthTableOr(string exp);
} // namespace Or
