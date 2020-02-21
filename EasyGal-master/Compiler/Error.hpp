#pragma once
#include <iostream>

using namespace std;
void ERROR(string err)
{
    cout << "[Error]" << err << endl;
    throw;
}
