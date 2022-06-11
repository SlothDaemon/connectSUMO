// TestMemMap.cpp : This file contains the 'main' function. Program execution begins and ends there.
// This program must run as administrator, else the mapping will fail

#include <iostream>
#include "..\ConnectSUMO_Harm\extern.h"
using namespace std;

int main()
{
    reserveAllMemory(256, 256, 10);

    cout << "writeBool" << endl;
    string value = "true";
    writeBool(value);

    cout << "writeNetwork" << endl;
    value = "Lorem Ipsum Dolor Sit Amet";
    writeNetwork(value);

    cout << "readBool" << endl;
    string result = readBool();
    cout << "\"" << result << "\"" << endl;

    cout << "readNetwork" << endl;
    result = readNetwork();
    cout << "\"" << result << "\"" << endl;

    cout << "writeBoolA" << endl;
    value = "false";
    writeBoolA(value.c_str());
    
    cout << "readBoolA" << endl;
    BSTR bResult;
    readBoolA(&bResult);
    cout << "\"" << result << "\"" << endl;

    cout << "readBool (memory was wiped)" << endl;
    result = readBool();
    cout << "\"" << result << "\"" << endl;

    cout << "writeTraffic" << endl;
    value = "traffic data";
    writeTraffic(value);
    result = readTraffic();
    cout << "\"" << result << "\"" << endl;

    cout << "writeTrafficA" << endl;
    writeTrafficA(string("traffic data A").c_str());
    cout << "readTrafficA" << endl;
    
    readTrafficA(&bResult);
    
    cout << "\"" << result << "\"" << endl;

    closeMemory();

    cout << "done\n";
}
