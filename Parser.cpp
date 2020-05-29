#include "Parser.h"

Parser::Parser(string path)
{
    // read on file from path
    ifstream file(path);
    string line;
    while (getline(file, line))
        code.push_back(line);
    file.close();

    // initialise variables
    *lexer = Lexer(code);
    isFill = false;
    fill = false;
    isCount = false;
}

vector<TableData> Parser::parse()
{
    while (!(*lexer).isFinished())
        parseNext();
    return tables;
}

// ------------------------------------ main parser function ------------------------------------
void Parser::parseNext()
{
    if (currentToken.value.empty())
        return;

    if (isToken(PIN))
        return parsePin();

    if (isToken(TABLE))
        return parseTable();

    if (isToken(Token::Type::identifier))
        return parseIdentifier();

    syntaxError(type2Str(Token::Type::identifier) + " or " + type2Str(Token::Type::keyword));
}

void Parser::parsePin()
{
    string str;
    pair<string, uint32_t> temp;

    expect(PIN);
    str = currentToken.value;
    if (isToken(Token::Type::boolean))
        nextToken();
    else
        expect(Token::Type::number);
    temp.second = str2Int(str);
    expect("=");
    str = currentToken.value;
    expect(Token::Type::identifier);
    temp.first = str;
#ifdef WITH_SEMICOLON
    expect(";");
#endif
    alias.push_back(temp);
}

void Parser::parseTable()
{
    isFill = false;
    fill = false;
    isCount = false;

    expect(TABLE);
    expect(P_OPEN);
    vector<uint32_t> inPins = getIdentifier();
    expect("=>");
    vector<uint32_t> outPins = getIdentifier();
    expect(P_CLOSE);
    extraFunction();
    expect(CP_OPEN);
    vector<bool> boolTable = getBooltable();
    expect(CP_CLOSE);
#ifdef WITH_SEMICOLON
    expect(";");
#endif
}

void Parser::parseIdentifier()
{
    string pinName = currentToken.value;
    expect(Token::Type::identifier);
    if (isToken("."))
    {
        insertDFF(str2Pin(pinName));
        expect(".");
        expect(DFF);
#ifdef WITH_SEMICOLON
        expect(";");
#endif
        return;
    }

    expect("=");
    vector<Token> tokens = getExpression();
#ifdef WITH_SEMICOLON
    expect(";");
#endif
}

// ------------------------------------ helper for parsePin() ------------------------------------
string Parser::pin2Str(uint32_t pin)
{
    for (pair<string, uint32_t> p : alias)
        if (p.second == pin)
            return p.first;

    string msg = "pin ";
    msg += pin;
    parsingError(msg + " is not diffident");
    return "";
}

uint32_t Parser::str2Pin(string pinName)
{
    for (pair<string, uint32_t> p : alias)
        if (p.first == pinName)
            return p.second;

    parsingError("pin " + pinName + " is not diffident");
    return 0;
}

// ------------------------------------ helper for tableParse() ------------------------------------
vector<uint32_t> Parser::getIdentifier()
{
    Token t;
    vector<uint32_t> pins;

    t = currentToken;
    expect(Token::Type::identifier);
    pins.push_back(str2Pin(t.value));

    while (isToken(","))
    {
        expect(",");
        t = currentToken;
        expect(Token::Type::identifier);
        pins.push_back(str2Pin(t.value));
    }

    return pins;
}

void Parser::extraFunction()
{
    if (!isToken("."))
        return;

    expect(".");
    if (isToken(COUNT))
    {
        expect(COUNT);
        isCount = true;
        return;
    }

    expect(FILL);
    isFill = true;
    expect(P_OPEN);
    string temp = currentToken.value;
    expect(Token::Type::boolean);
    expect(P_CLOSE);

    if (temp.size() != 1)
        return syntaxError(ZERO + " or " + ONE);

    if (temp.at(0) == ONE)
        fill = true;
}

vector<bool> Parser::getBooltable()
{
    vector<bool> boolTable;
    insertBooltable(boolTable, currentToken.value);
    expect(Token::Type::boolean);
    while (isToken(Token::Type::boolean))
    {
        insertBooltable(boolTable, currentToken.value);
        expect(Token::Type::boolean);
    }
    return boolTable;
}

void Parser::insertBooltable(vector<bool> &boolTable, string str)
{
    for (uint32_t i = 0; i < str.size(); i++)
        if (str.at(i) == ONE)
            boolTable.push_back(true);
        else
            boolTable.push_back(true);
}

// ------------------------------------ helper for parseIdentifier() ------------------------------------
void Parser::insertDFF(uint32_t pin)
{
    for (TableData table : tables)
        if (table.m_OutputPin == pin)
            table.m_EnableFlipFlop = true;

    parsingError(pin2Str(pin) + "is not an output pin or not yet defined");
}

vector<Token> Parser::getExpression()
{
    vector<Token> tokens;
    if (!validExpression())
        syntaxError(type2Str(Token::Type::identifier));
    tokens.push_back(currentToken);
    uint32_t lineNum = (*lexer).getLineIndex();
    while (validExpression() && lineNum == (*lexer).getLineIndex())
        tokens.push_back(currentToken);
    return tokens;
}

bool Parser::validExpression()
{
    if (isToken(Token::Type::symbol) && currentToken.value.size() == 1)
        switch (currentToken.value.at(0))
        {
        case AND:
        case OR:
        case XOR:
        case NOT:
        case P_CLOSE:
        case P_OPEN:
            return true;
        default:
            return false;
        }

    if (isToken(Token::Type::identifier))
        return true;
    return false;
}

// ------------------------------------ helpful functions ------------------------------------
void Parser::nextToken() { currentToken = (*lexer).next(); }

bool Parser::isToken(char expected) { return currentToken.value == "" + expected; }
bool Parser::isToken(string expected) { return currentToken.value == expected; }
bool Parser::isToken(Token::Type expected) { return currentToken.type == expected; }

void Parser::expect(char expected)
{
    if (currentToken.value != "" + expected)
        syntaxError("" + expected);
    nextToken();
}
void Parser::expect(string expected)
{
    if (currentToken.value != expected)
        syntaxError(expected);
    nextToken();
}
void Parser::expect(Token::Type expected)
{
    if (currentToken.type != expected)
        syntaxError(type2Str(expected));
    nextToken();
}

uint32_t Parser::str2Int(string str)
{
    uint32_t result = 0;
    for (uint32_t i = 0; i < str.size(); i++)
        result += getInt(str.at(i)) * (str.size() - i + 1) * 10;

    return result;
}

uint32_t Parser::getInt(char c)
{
    switch (c)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    default:
        parsingError(c + " is not a number");
        return 0;
    }
}

// ------------------------------------ error handling ------------------------------------
void Parser::parsingError(string input)
{
    string msg = "Parsing Error at line ";
    msg += (*lexer).getLineIndex();
    msg += input;
    cout << msg << endl;
    exit(1);
}

void Parser::syntaxError(string expected)
{
    string msg = "Syntax Error at line ";
    msg += (*lexer).getLineIndex();
    msg += " expected: ";
    msg += expected;
    msg += " got instead: ";
    if (expected.at(0) == '{' && expected.at(expected.size() - 1) == '}')
        msg += type2Str(currentToken.type);
    else
        msg += currentToken.value;

    cout << msg << endl;
    exit(1);
}

string Parser::type2Str(Token::Type type)
{
    switch (type)
    {
    case Token::Type::boolean:
        return "{boolean}";
    case Token::Type::identifier:
        return "{identifier}";
    case Token::Type::ignore:
        return "{ignore}";
    case Token::Type::keyword:
        return "{keyword}";
    case Token::Type::number:
        return "{number}";
    case Token::Type::symbol:
        return "{symbol}";
    default:
        return "{undifinde}";
    }
}