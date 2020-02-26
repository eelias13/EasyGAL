#include <vector>
#include "../Lexer/Token.hpp"
using namespace std;

class FunctionParser
{
private:
public:
    FunctionParser();
    vector<bool> parse(vector<Token>);
};
