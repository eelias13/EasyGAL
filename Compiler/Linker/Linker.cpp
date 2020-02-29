#include "Linker.hpp"

Linker::Linker()
{
}

vector<TableData> Linker::link(TablesAndNames Input)
{
    vector<TableName> TNVec = split(Input);
    return matchPins(TNVec, Input);
}

uint32_t Linker::findePin(string Str, vector<pair<string, int>> Alias)
{
    for (pair<string, int> p : Alias)
        if (p.first == Str)
            return (uint32_t)p.second;

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
        Temp.m_OutputPin = findePin(TN.OutName, Input.Alias);
        for (string Str : TN.InNames)
            Temp.m_InputPins.push_back(findePin(Str, Input.Alias));
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