#include "Main.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        cout << "you have to enter a file" << endl;
        exit(EXIT_FAILURE);
    }
    if (argc > 2)
    {
        cout << "this progatam dose  not suport more then one argument" << endl;
        exit(EXIT_FAILURE);
    }

    string Path = argv[1];
    vector<string> Code = ReadFile(Path);

    vector<int> ValidInPins = getValidPins(VALID_IN_PINS);
    vector<int> ValidOutPins = getValidPins(VALID_OUT_PINS);

    Compiler compiler = Compiler(ValidInPins, ValidOutPins);

    vector<TableData> TD = compiler.compile(Code);

    for (TableData t : TD)
        printTD(t);
}

vector<string> ReadFile(string Path)
{
    ifstream InReader(Path);
    vector<string> Code;

    if (!InReader)
    {
        cout << "Cannot open input file." << endl;
        exit(EXIT_FAILURE);
    }

    char str[255];

    while (InReader)
    {
        InReader.getline(str, 255);
        Code.push_back(str);
    }

    for (int i = 0; i < Code.size(); i++)
        Code.at(i) += '\n';

    InReader.close();
    return Code;
}

vector<int> getValidPins(string InStr)
{
    vector<int> ValidPins;
    string Temp;
    for (char c : InStr)
        if (c == ' ')
        {
            ValidPins.push_back(Helper::str2Int(Temp));
            Temp = "";
        }
        else
            Temp += c;
    return ValidPins;
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

void printTable(vector<bool> BoolVec, vector<uint32_t> InPins, uint32_t OutPin)
{
    for (uint32_t pin : InPins)
        cout << pin << " ";
    cout << "\t" << OutPin << endl;
    cout << endl;
    vector<vector<bool>> Vec2D = Helper::generateTable2D(InPins.size());
    for (int i = 0; i < Vec2D.size(); i++)
    {
        for (bool b : Vec2D.at(i))
            cout << b << " ";
        cout << "\t" << BoolVec.at(i) << endl;
    }
}
