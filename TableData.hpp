#pragma once

#include <vector>

using namespace std;

class TableData
{

public:

    bool verify(uint32_t pinMin, uint32_t pinMax, vector<uint32_t> disallowedPins);
    uint32_t getNumInputBits();

    bool m_enableDFF;
    uint32_t m_outputPin;
    vector<bool> m_table;
    vector<uint32_t> m_inputPins;
};

