#include "Main.hpp"

int main()
{
    vector<string> code;
    code.push_back("pin 1 = in1;");
    code.push_back("pin 2 = in2;");
    code.push_back("pin 3 = and;");
    code.push_back("pin 4 = xor;");
    code.push_back("pin 5 = a;");
    code.push_back("pin 6 = b;");
    code.push_back("pin 5 = c;");

    code.push_back("in1.dff;");

    code.push_back("table(in1, in2 => and, xor){");
    code.push_back("00 00");
    code.push_back("01 01");
    code.push_back("10 01");
    code.push_back("11 10");
    code.push_back("}");

    code.push_back("c = (a & b);");

    vector<int> validPins;
    string temp;
    for (char c : VALID_PINS)
        if (c == ' ')
        {
            validPins.push_back(Helper::str2Int(temp));
            temp = "";
        }
        else
            temp += c;

    Lexer lexer = Lexer(VALID_CHAR);
    PreCompiler preCompiler = PreCompiler();
    Compiler compiler = Compiler(validPins);
    Linker linker = Linker();

    vector<Token> tokens = lexer.lex(code);
    stack<Token> tokenStack = preCompiler.compile(tokens);
    TablesAndNames tempTable = compiler.compile(tokenStack);
    vector<TableData> tdVec = linker.link(tempTable);

    for (TableData td : tdVec)
        printTD(td);
}

void printTD(TableData td)
{
    cout << "Is D: " << td.m_EnableFlipFlop;

    cout << "  Output Pin: " << td.m_OutputPin;
    cout << "  Boolean Table: ";
    for (bool b : td.m_Table)
        cout << b;
    cout << "  Input Pins: ";
    for (uint32_t i : td.m_InputPins)
        cout << i << " ";
    cout << endl;
}