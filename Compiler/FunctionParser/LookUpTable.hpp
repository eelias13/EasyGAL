#include <vector>
#include <string>
#include "../Lexer/Token.hpp"
#include "../../Helper.hpp"

using namespace std;

class LookUpTable
{
public:
    bool at(Token);
    void setValue(vector<bool>);
    void addKey(Token);
    void setKey(vector<Token>);
    vector<Token> getKey();

private:
    vector<Token> m_Keys;
    vector<bool> m_Value;
};