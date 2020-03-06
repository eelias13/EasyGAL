#include "Linker.hpp"

Linker::Linker() {}

Linker::Linker(vector<int> ValidInPins, vector<int> ValidOutPins)
{
    m_ValidInPins = ValidInPins;
    m_ValidOutPins = ValidOutPins;
}

vector<TableData> Linker::link(TablesAndNames Input)
{
    vector<TableName> TNVec = split(Input);
    return matchPins(TNVec, Input);
}

int Linker::findePin(string Str, vector<pair<string, int>> Alias)
{
    for (pair<string, int> p : Alias)
        if (p.first == Str)
            return p.second;

    error("Linking Error", "Pin " + Str + "is not definde", -1);
    return {};
}

vector<Linker::TableName> Linker::split(TablesAndNames Input)
{
    vector<TableName> TNVec;
    for (Table t : Input.Tables)
    {
        for (int i = 0; i < t.getInNames().size(); i++)
        {
            TableName Temp;
            Temp.OutName = t.getOutNames().at(i);
            Temp.InNames = t.getInNames();
            Temp.BoolTable = t.getDate(Temp.OutName);
            TNVec.push_back(Temp);
        }
    }

    return TNVec;
}

vector<TableData> Linker::matchPins(vector<TableName> TNVec, TablesAndNames Input)
{
    vector<TableData> TDVec;

    for (TableName TN : TNVec)
    {
        TableData Temp;
        int Pin = findePin(TN.OutName, Input.Alias);
        checkPin(Pin, false);
        Temp.m_OutputPin = (uint32_t)Pin;

        for (string Str : TN.InNames)
        {
            Pin = findePin(Str, Input.Alias);
            checkPin(Pin, true);
            Temp.m_InputPins.push_back((uint32_t)Pin);
        }

        Temp.m_Table = TN.BoolTable;
        Temp.m_EnableFlipFlop = false;
        TDVec.push_back(Temp);
    }

    for (string dff : Input.IsD)
    {
        int Pin = findePin(dff, Input.Alias);
        for (int i = 0; i < TDVec.size(); i++)
            if (TDVec.at(i).m_OutputPin == Pin)
            {
                TDVec.at(i).m_EnableFlipFlop = true;
                break;
            }
    }

    return TDVec;
}

void Linker::checkPin(int Pin, bool IsInput)
{
    if (!isValidPin(Pin, IsInput))
        if (IsInput)
            error("Linking Error", "Pin " + to_string(Pin) + " is not a valid inputpin", -1);
        else
            error("Linking Error", "Pin " + to_string(Pin) + " is not a valid outputpin", -1);
}

bool Linker::isValidPin(int Pin, bool IsInput)
{
    if (IsInput)
    {
        for (int i : m_ValidInPins)
            if (i == Pin)
                return true;
    }
    else
        for (int i : m_ValidOutPins)
            if (i == Pin)
                return true;
    return false;
}