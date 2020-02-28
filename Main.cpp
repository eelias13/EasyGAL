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

    vector<int> ValidPins;
    string Temp;
    for (char c : VALID_PINS)
        if (c == ' ')
        {
            ValidPins.push_back(Helper::str2Int(Temp));
            Temp = "";
        }
        else
            Temp += c;

    // Compiler compiler = Compiler(ValidPins);
    // vector<TableData> tb = compiler.compile(code);
}