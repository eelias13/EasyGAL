#include <vector>
#include "../Lexer/Token.hpp"
using namespace std;

class FunctionParser
{
public:
    FunctionParser();
    vector<bool> parse(vector<Token>);
};
