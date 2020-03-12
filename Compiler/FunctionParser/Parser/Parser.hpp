#include <string>

#include "../../Symbol.hpp"
#include "../../../Helper.hpp"
#include "Preproces.hpp"

#include "../Simplefy/And.hpp"
#include "../Simplefy/Or.hpp"
#include "../Simplefy/Xor.hpp"
#include "../Simplefy/Not.hpp"
#include "../Simplefy/Parentheses.hpp"

using namespace std;

namespace Parser
{
char parse(string);
string parseRecursiv(string);
} // namespace Parser