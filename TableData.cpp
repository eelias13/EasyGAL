#include "TableData.hpp"

bool TableData::verify(uint32_t pinMin, uint32_t pinMax, vector<uint32_t> disallowedPins)
{
    if(m_outputPin < pinMin || m_outputPin > pinMax)
        return false;

    for(uint32_t pin : disallowedPins)
        if(m_outputPin == pin)
            return false;

    // TODO: Add checks.

    return true;
}

uint32_t TableData::getNumInputBits()
{
    return pow(2, m_inputPins.size());
}
