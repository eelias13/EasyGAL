#include "Helper.hpp"

int Helper::str2Int(string Str)
{
    if (Str.size() == 1)
        return char2Int(Str.at(0));
    else if (Str.size() == 2)
        return char2Int(Str.at(0)) * 10 + char2Int(Str.at(1));
    else
        return -1;
}

int Helper::char2Int(char C)
{
    switch (C)
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
        return -1;
    }
}
void error(string err)
{
    cout << "[Error]" << err << endl;
    exit(EXIT_FAILURE);
}

vector<vector<bool>> Helper::generateTable2D(int len)
{
    vector<vector<bool>> Result;
    Result.push_back(vector<bool>{false});
    for (int i = 1; i < len * len; i++)
        Result.push_back(Helper::int2Bool(i));
    //fill missing 0
    for (int i = 0; i < Result.size(); i++)
    {
        if (Result.at(i).size() != len)
        {
            vector<bool> Temp;
            for (int j = 0; j < len - Result.at(i).size(); j++)
                Temp.push_back(false);
            for (int j = 0; j < Result.at(i).size(); j++)
                Temp.push_back(Result.at(i).at(j));
            Result.at(i) = Temp;
        }
    }
    return Result;
}

vector<bool> Helper::int2Bool(int IntIn)
{
    vector<bool> Temp;
    while (IntIn > 0)
    {
        if (IntIn % 2 == 0)
            Temp.push_back(false);
        else
            Temp.push_back(true);
        IntIn /= 2;
    }

    // flip vec
    vector<bool> Result;
    for (int i = Temp.size() - 1; i >= 0; i--)
        Result.push_back(Temp.at(i));

    return Result;
}

int Helper::bool2Int(vector<bool> BoolVec)
{
    int number = 0;
    for (int i = BoolVec.size() - 1; i >= 0; i--)
        if (BoolVec.at(i))
            number += pow(2, (BoolVec.size() - 1 - i));
    return number;
}
