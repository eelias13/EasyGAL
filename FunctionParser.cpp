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

    if (isParentheses(expression))
        return splitParentheses(expression);
    return splitBineryOperator(expression);
}

bool FunctionParser::isParentheses(vector<Token> expression)
{
    if (expression.at(0).value.at(0) != '(')
        return false;
    if (expression.at(expression.size() - 1).value.at(0) != ')')
        return false;

    int counter = 1;
    for (uint32_t i = 1; i < expression.size() - 1; i++)
    {
        if (counter == 0)
            return false;
        char c = expression.at(i).value.at(0);
        if (c == '(')
            counter++;
        if (c == ')')
            counter--;
    }
    return true;
}

FunctionParser::Bundle FunctionParser::splitParentheses(vector<Token> expression)
{
    vector<Token> temp;
    for (uint32_t i = 1; i < expression.size() - 1; i++)
        temp.push_back(expression.at(i));
    return split(temp);
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
    {
        if (expression.at(0).value.at(0) == NOT)
            return splitNot(expression);

        string msg = "can not split expression: ";
        for (Token t : expression)
            msg += t.value;
        parsingError(msg);
    }

    Bundle bundle;
    for (uint32_t i = 0; i < index; i++)
        bundle.left.push_back(expression.at(i));
    bundle.center = expression.at(index);
    for (uint32_t i = index + 1; i < expression.size(); i++)
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
        Token t = expression.at(i);
        if (t.type != Token::Type::symbol)
            continue;

        if (parentheses != 0)
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
    Bundle bundle = split(expression);
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
        parsingError("can not resolve token" + (*node).token.value);
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
void FunctionParser::initLookup()
{
    lookupLength = names.size();
    lookupValues = (bool *)malloc((lookupLength - 1) * sizeof(bool));
    finished = false;

    for (uint32_t i = 0; i < lookupLength; i++)
    {
        pair<string, bool *> p;
        p.first = names.at(i);
        p.second = (lookupValues + (sizeof(bool) * i));
        lookup.push_back(p);

        *(p.second) = false;
    }
}

void FunctionParser::updateLookup()
{
    for (int i = lookupLength - 1; i >= 0; i--)
    {
        bool *currentValue = lookupValues + (sizeof(bool) * i);
        *currentValue = !(*currentValue);
        if (*currentValue == true)
            return;
    }
    finished = true;
}

void FunctionParser::deleteLookup()
{
    free(lookupValues);
    lookupLength = 0;
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

void FunctionParser::initNames(vector<Token> expression)
{
    for (Token t : expression)
        if (t.type == Token::Type::identifier)
            names.push_back(t.value);
    names = removeDouble(names);
}

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
// ------------------------------------ validate ------------------------------------

void FunctionParser::isValide(vector<Token> expression)
{
    if (expression.size() == 0)
        parsingError("no expression");

    uint32_t counterParentheses = 0;
    uint32_t counterBinaryOperator = 0;
    bool lastIdentifier = false;
    for (Token t : expression)
    {
        if (t.type == Token::Type::symbol)
        {
            char c = t.value.at(0);
            if (!valideSymbol(c))
            {
                string msg = "(, ), ";
                msg += AND;
                msg += ", ";
                msg += OR;
                msg += ", ";
                msg += NOT;
                msg += ", ";
                msg += XOR;
                syntaxError(t, msg);
            }

            if (isBinary(c))
                counterBinaryOperator++;

            if (c == '(')
                counterParentheses++;
            if (c == ')')
            {
                if (counterParentheses < 0)
                    syntaxError(t, "(");
                counterParentheses--;
            }
            lastIdentifier = false;
        }
        else
        {
            if (t.type != Token::Type::identifier)
                syntaxError(t, Token::Type::symbol);
            if (lastIdentifier == true)
                syntaxError(t, Token::Type::symbol);
            lastIdentifier = true;
        }
    }

    if (counterBinaryOperator != names.size() - 1)
        syntaxError(expression.at(expression.size() - 1), Token::Type::identifier);

    if (counterParentheses != 0)
        syntaxError(expression.at(expression.size() - 1), ")");
}

bool FunctionParser::isBinary(char c)
{
    switch (c)
    {
    case AND:
    case OR:
    case XOR:
        return true;

    default:
        return false;
    }
}

bool FunctionParser::valideSymbol(char c)
{
    switch (c)
    {
    case '(':
    case ')':
    case AND:
    case OR:
    case XOR:
    case NOT:
        return true;

    default:
        return false;
    }
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

    names = {};
    initNames(expression);
    isValide(expression);

    initLookup();
    Node *tree = nextNode(expression, NULL);

    vector<bool> table;

    for (uint32_t index = 0; index < pow(2, names.size()); index++)
    {
        table.push_back(evalNode(tree));
        updateLookup();
    }

    deleteNode(tree);
    deleteLookup();

    return table;
}

vector<string> FunctionParser::getNames() { return names; }

void FunctionParser::syntaxError(Token got, string expected) { Error::makeError(Error::Type::syntax, lineIndex, got, expected); }
void FunctionParser::syntaxError(Token got, Token::Type expected) { Error::makeError(Error::Type::syntax, lineIndex, got, expected); }
void FunctionParser::parsingError(string msg) { Error::makeError(Error::Type::parsing, lineIndex, msg); }