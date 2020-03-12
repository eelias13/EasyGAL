#include "Table.hpp"

Table::Table(vector<string> InNames, vector<string> OutNames, vector<bool> BoolVec, bool Fill)
{
    m_InNames = InNames;
    m_OutNames = OutNames;
    vector<vector<bool>> Vec2D = Table::splitRows(BoolVec, OutNames.size() + InNames.size());
    m_BoolVec = Table::match(Vec2D, OutNames.size(), Fill);
    m_InitSuccess = true;
}

Table::Table(vector<string> InNames, vector<string> OutNames, vector<bool> BoolVec, Type type)
{
    m_InNames = InNames;
    m_OutNames = OutNames;

    if (type == Table::Type::Count)
    {
        if (BoolVec.size() != pow(2, InNames.size()) * OutNames.size())
            m_InitSuccess = false;
#ifdef COUNT_VERTICAL
        else
        {
            for (int i = 0; i < OutNames.size(); i++)
            {
                vector<bool> Temp;
                for (int j = 0; j < pow(2, InNames.size()); j++)
                    Temp.push_back(BoolVec.at(i * pow(2, InNames.size()) + j));
                m_BoolVec.push_back(Temp);
            }
            m_InitSuccess = true;
        }
#else
        else
        {
            for (int i = 0; i < OutNames.size(); i++)
                m_BoolVec.push_back({});

            for (int i = 0; i < BoolVec.size(); i++)
            {
                m_BoolVec.at(i % OutNames.size()).push_back(BoolVec.at(i));
            }
            m_InitSuccess = true;
        }

#endif
    }
    else
    {
        if (BoolVec.size() != pow(2, InNames.size()) * (OutNames.size() + InNames.size()))
            m_InitSuccess = false;
        else
        {
            vector<vector<bool>> Vec2D = Table::splitRows(BoolVec, OutNames.size() + InNames.size());
            m_BoolVec = Table::match(Vec2D, OutNames.size(), false);
            m_InitSuccess = true;
        }
    }
}

vector<vector<bool>> Table::splitRows(vector<bool> BoolVec, int len)
{
    vector<vector<bool>> Rows;
    int index = 0;
    while (BoolVec.size() != index * len)
    {
        for (int i = 0; i < len; i++)
            if (i == 0)
                Rows.push_back(vector<bool>{BoolVec.at(i + len * index)});
            else
                Rows.at(index).push_back(BoolVec.at(i + len * index));
        index++;
    }
    return Rows;
}

pair<int, vector<bool>> Table::matchLine(vector<bool> BoolVec, int OutLen)
{
    vector<bool> Temp;

    for (int i = 0; i < BoolVec.size() - OutLen; i++)
        Temp.push_back(BoolVec.at(i));

    int Index = Helper::bool2Int(Temp);
    Temp = {};

    for (int i = 0; i < OutLen; i++)
        Temp.push_back(BoolVec.at(BoolVec.size() - OutLen + i));

    return pair<int, vector<bool>>(Index, Temp);
}

vector<vector<bool>> Table::match(vector<vector<bool>> Vec2D, int OutLen, bool Init)
{
    vector<vector<bool>> Result;
    // init result;
    for (int i = 0; i < OutLen; i++)
    {
        Result.push_back(vector<bool>{Init});
        for (int j = 1; j < pow(2, Vec2D.at(0).size() - OutLen); j++)
            Result.at(i).push_back(Init);
    }

    for (vector<bool> B : Vec2D)
    {
        pair<int, vector<bool>> P = matchLine(B, OutLen);
        for (int i = 0; i < P.second.size(); i++)
            Result.at(i).at(P.first) = P.second.at(i);
    }

    return Result;
}

vector<bool> Table::getDate(string OutNames)
{
    int Index = -1;
    for (int i = 0; i < m_OutNames.size(); i++)
        if (OutNames == m_OutNames.at(i))
        {
            Index = i;
            break;
        }

    if (Index == -1)
    {
        cout << "error" << endl;
        return {};
    }
    return m_BoolVec.at(Index);
}

vector<string> Table::getInNames()
{
    return m_InNames;
}

vector<string> Table::getOutNames()
{
    return m_OutNames;
}