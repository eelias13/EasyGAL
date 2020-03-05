#include <string>
#include <vector>
#include <stack>
#include "../Lexer/Token.hpp"
#include "../Symbol.hpp"
#include "../../Helper.hpp"
#include "LookUpTable.hpp"

using namespace std;

class Node
{
public:
    Node(stack<Token> &);
    Node(Node *, stack<Token> &);
    void insert(stack<Token> &);
    bool eval(LookUpTable);

private:
    Node *m_Parent;
    Node *m_Left;
    Node *m_Right;
    Token *m_Value;
};