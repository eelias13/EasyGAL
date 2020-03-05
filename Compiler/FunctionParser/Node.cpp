#include "Node.hpp"

void Node::insert(stack<Token> &Stack)
{
    if ((*m_Value).key() == Token::Key::Identifier)
        exit(EXIT_FAILURE);
    if ((*m_Value).value() == string(1, NOT))
        (*m_Parent).insert(Stack);
    m_Left = new Node(this, Stack);
}

Node::Node(stack<Token> &Stack)
{
    m_Parent = nullptr;
    if (Stack.top().key() == Token::Key::Identifier)
    {
        m_Right = nullptr;
        m_Left = nullptr;
        m_Value = &Stack.top();
        Stack.pop();
        if (!Stack.empty())
            error("", "valid to evaluate expresion", Stack.top().lineIndex());
    }
    else
    {
        m_Value = &Stack.top();
        Stack.pop();
        if (Stack.empty())
            error("", "valid to evaluate expresion", Stack.top().lineIndex());
        m_Left = nullptr;
        m_Right = new Node(this, Stack);
    }
}

Node::Node(Node *Parent, stack<Token> &Stack)
{
    m_Parent = Parent;
    if (Stack.top().key() == Token::Key::Identifier)
    {
        m_Right = nullptr;
        m_Left = nullptr;
        m_Value = &Stack.top();
        Stack.pop();
        if (!Stack.empty())
            (*Parent).insert(Stack);
    }
    else
    {
        m_Value = &Stack.top();
        Stack.pop();
        if (Stack.empty())
            error("", "valid to evaluate expresion", Stack.top().lineIndex());
        m_Left = nullptr;
        m_Right = new Node(this, Stack);
    }
}

bool Node::eval(LookUpTable LookUp)
{
    if ((*m_Value).key() == Token::Key::Identifier)
    {
        cout << LookUp.at((*m_Value)) << endl;
        return LookUp.at((*m_Value));
    }

    if ((*m_Value).value() == string(1, NOT))
        return ~(*m_Right).eval(LookUp);
    if ((*m_Value).value() == string(1, AND))
    {

        bool l = (*m_Left).eval(LookUp);
        bool r = (*m_Right).eval(LookUp);
        return r & l;
    }
    if ((*m_Value).value() == string(1, OR))
        return (*m_Right).eval(LookUp) | (*m_Left).eval(LookUp);
    if ((*m_Value).value() == string(1, XOR))
        return (*m_Right).eval(LookUp) ^ (*m_Left).eval(LookUp);
    error("", "valid to evaluate expresion", (*m_Value).lineIndex());
}