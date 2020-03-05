#include <vector>
#include <stack>
#include <string>
#include "LookUpTable.hpp"
#include "ShuntingYard.hpp"
#include "Node.hpp"
#include "../Lexer/Token.hpp"
#include "../Helper.hpp"
using namespace std;

class FunctionParser
{
private:
    vector<Token> getNames(vector<Token>);
    bool isInVec(Token, vector<Token>);

public:
    FunctionParser();
    vector<bool> parse(vector<Token>);
};
