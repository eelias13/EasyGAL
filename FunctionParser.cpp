#include "FunctionParser.h"

// ------------------------------------ split functions ------------------------------------
struct FunctionParser::Bundle
{
    vector<Token> left;
    vector<Token> right;
    Token center;
};

FunctionParser::Bundle FunctionParser::split(vector<Token> expression)
{

    // is leavnode
    if (expression.size() == 1)
    {
        Bundle bundle;
        bundle.center = expression.at(0);
        bundle.left = {};
        bundle.right = {};
        return bundle;
    }

    if (expression.at(0).value.at(0) == '(')
        return splitParentheses(expression);
    if (expression.at(0).value.at(0) == NOT)
        return splitNot(expression);
    return splitBineryOperator(expression);
}

FunctionParser::Bundle FunctionParser::splitParentheses(vector<Token> expression)
{
    Bundle bundle;
    uint32_t index = 1;
    while (expression.at(index).value.at(0) != ')')
        bundle.left.push_back(expression.at(index));
    index++;

    if (expression.size() - 1 == index)
        return split(bundle.left);
    index++;

    bundle.center = expression.at(index);
    for (uint32_t i = index; i < expression.size(); i++)
        bundle.right.push_back(expression.at(i));
    return bundle;
}

FunctionParser::Bundle FunctionParser::splitNot(vector<Token> expression)
{
    Bundle bundle;
    bundle.center = expression.at(0);
    for (uint32_t i = 1; i < expression.size(); i++)
        bundle.left.push_back(expression.at(i));
    bundle.right = {};
    return bundle;
}

FunctionParser::Bundle FunctionParser::splitBineryOperator(vector<Token> expression)
{
    uint32_t index = splitIndex(expression);
    if (index == 0)
        Error::makeError(Error::Type::parsing, lineIndex, "can not split");

    Bundle bundle;
    for (uint32_t i = 0; i < index; i++)
        bundle.left.push_back(expression.at(i));
    bundle.center = expression.at(index);
    for (uint32_t i = index; i < expression.size(); i++)
        bundle.right.push_back(expression.at(i));
    return bundle;
}

uint32_t FunctionParser::splitIndex(vector<Token> expression)
{
    uint32_t lowestOperatorIndex = 0;
    uint8_t lowestOperatorScore = 0xff;
    uint8_t parentheses = 0;

    for (uint32_t i = 0; i < expression.size(); i++)
    {
        Token t = expression.at(0);
        if (t.type != Token::Type::symbol)
            continue;

        if (parentheses > 0)
        {
            if (t.value.at(0) == ')')
                parentheses--;
            if (t.value.at(0) == '(')
                parentheses++;
            continue;
        }

        if (t.value.at(0) == '(')
            parentheses++;

        if (precedenceOf(t.value.at(0)) < lowestOperatorScore)
        {
            lowestOperatorScore = precedenceOf(t.value.at(0));
            lowestOperatorIndex = i;
            if (lowestOperatorScore == 0)
                break;
        }
    }

    return lowestOperatorIndex;
}

// ------------------------------------ nodes ------------------------------------
struct FunctionParser::Node
{
    Node *parent;
    Node *left;
    Node *right;

    Token token;
    bool *value;
};

struct FunctionParser::Node *FunctionParser::newNode(Token token, FunctionParser::Node *parent)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->token = token;
    node->value = getBoolPtr(token);
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    return (node);
};

FunctionParser::Node *FunctionParser::nextNode(vector<Token> expression, Node *pNode)
{
    Bundle bundle;
    bundle = split(expression);
    Node *node = newNode(bundle.center, pNode);
    if (bundle.left.size() != 0)
        (*node).left = nextNode(bundle.left, node);
    if (bundle.right.size() != 0)
        (*node).right = nextNode(bundle.right, node);
    return node;
}

bool FunctionParser::evalNode(Node *node)
{
    if ((*node).value != NULL)
        return *((*node).value);

    switch ((*node).token.value.at(0))
    {
    case AND:
        return evalNode((*node).left) & evalNode((*node).right);
    case OR:
        return evalNode((*node).left) | evalNode((*node).right);
    case XOR:
        return evalNode((*node).left) ^ evalNode((*node).right);
    case NOT:
        return !evalNode((*node).left);
    default:
        Error::makeError(Error::Type::parsing, lineIndex, "can not resolve token " + (*node).token.value);
        return false;
    }
}

void FunctionParser::deleteNode(Node *node)
{
    if ((*node).left != NULL)
        deleteNode((*node).left);
    if ((*node).right != NULL)
        deleteNode((*node).right);
    free(node);
}

// ------------------------------------ lookup ------------------------------------
void FunctionParser::initLookup(vector<Token> expression)
{
    vector<string> names = getNames(expression);
    valueLength = names.size();
    values = (bool *)malloc((valueLength - 1) * sizeof(bool));
    finished = true;

    for (uint32_t i = 0; i < valueLength; i++)
    {
        pair<string, bool *> p;
        p.first = names.at(i);
        p.second = (values + (sizeof(bool) * i));
        lookup.push_back(p);

        *(p.second) = false;
    }
}

void FunctionParser::updateLookup()
{
    for (int i = valueLength - 1; i >= 0; i--)
    {
        bool *currentValue = values + (sizeof(bool) * i);
        *currentValue = !(*currentValue);
        if (*currentValue == true)
            return;
    }
    finished = true;
}

void FunctionParser::deleteLookup()
{
    free(values);
    valueLength = 0;
    lookup = {};
}

bool *FunctionParser::getBoolPtr(Token token)
{
    for (pair<string, bool *> p : lookup)
        if (p.first == token.value)
            return p.second;
    return NULL;
}

// ------------------------------------ functions for getNames ------------------------------------

vector<string> FunctionParser::removeDouble(vector<string> names)
{
    vector<string> result;
    for (string name : names)
        if (!strInVec(result, name))
            result.push_back(name);
    return result;
}

bool FunctionParser::strInVec(vector<string> vec, string str)
{
    for (string s : vec)
        if (s == str)
            return true;
    return false;
}

// ------------------------------------ operator precedence ------------------------------------
uint8_t FunctionParser::precedenceOf(char c)
{
    if (c == operatorPrecedence[0])
        return 0;
    if (c == operatorPrecedence[1])
        return 1;
    if (c == operatorPrecedence[2])
        return 2;
    if (c == operatorPrecedence[3])
        return 3;

    return 0xff;
}

// ------------------------------------ constructor ------------------------------------
FunctionParser::FunctionParser()
{
    operatorPrecedence[0] = OR;
    operatorPrecedence[1] = XOR;
    operatorPrecedence[2] = AND;
    operatorPrecedence[3] = NOT;
}

// ------------------------------------ public functions ------------------------------------

vector<bool> FunctionParser::parse(vector<Token> expression, uint32_t lineIndex)
{
    this->lineIndex = lineIndex;
    vector<bool> table;
    Node *tree = nextNode(expression, NULL);

    initLookup(expression);

    while (!finished)
    {
        table.push_back(evalNode(tree));
        updateLookup();
    }

    deleteNode(tree);
    deleteLookup();

    return table;
}

vector<string> FunctionParser::getNames(vector<Token> expression)
{
    vector<string> names;
    for (Token t : expression)
        if (t.type == Token::Type::identifier)
            names.push_back(t.value);
    names = removeDouble(names);
    return names;
}