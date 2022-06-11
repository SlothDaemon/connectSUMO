#include <iostream>
#include <stdlib.h>
#include <string>

#include "framework.h"
#include "pch.h"
#include "extern.h"
#include "locus.h"
#include "atlbase.h"
#include "atlstr.h"
#include "comutil.h"

using namespace std;
// using namespace System;


// These are the names with which to address the locations in the pagefile for 
// their respective contents.They are set in stone, and if any other application
// just so happens to need to access these locations, too bad?? But I highly, 
// highly doubt that would ever be the case. Surely, nobody is going to take
// a name as strange as 'boolMappingObject'. Surely.
TCHAR boolName[] = TEXT("Global\\boolMappingObject");
TCHAR networkName[] = TEXT("Global\\networkMappingObject");
TCHAR trafficName[] = TEXT("Global\\trafficMappingObject");

// In these memory locations their respective contents need to be stored which
// is almost self-explanatory. I assume that network data is going to be 
// stringified XML. However, I found that these files can get ginormous. Just be 
// conservative with the network you send through. Or test the limits of the size
// that shared memory can take. Your choice.
const TCHAR networkMessage[] = TEXT("Network message.");
const TCHAR trafficMessage[] = TEXT("Traffic message.");
const TCHAR boolMessage[] = TEXT("false");

Locus pointers;

MemLoc reserveMemory(LPCWSTR memName, int bufferSize) {
	HANDLE hMapFile;
	LPCTSTR pBuf;

	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		bufferSize,              // maximum object size (low-order DWORD)
		memName);                // name of mapping object

	cout << "reserve memory for [" << bufferSize << "] ";
	cout << CW2A(memName) << endl;

	if (hMapFile == NULL)
	{
		cout << "Could not create file mapping object (" << GetLastError() << ")" << endl;
		exit(1);
	}

	pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		bufferSize);

	if (pBuf == NULL)
	{
		cout << "Could not map view of file (" << GetLastError() << ")" << endl;

		CloseHandle(hMapFile);
		exit(1);
	}

	MemLoc location;
	location.handle = hMapFile;
	location.pointer = pBuf;
	location.name = memName;
	return location;
}

extern "C"
{
	void closeMemory() {
		UnmapViewOfFile(pointers.bools.pointer);
		CloseHandle(pointers.bools.handle);

		UnmapViewOfFile(pointers.network.pointer);
		CloseHandle(pointers.network.handle);

		UnmapViewOfFile(pointers.traffic.pointer);
		CloseHandle(pointers.traffic.handle);
	}

	int reserveAllMemory(int networkSize, int trafficSize, int boolSize) {
		pointers.bools = reserveMemory(boolName, boolSize);
		pointers.network = reserveMemory(networkName, networkSize);
		pointers.traffic = reserveMemory(trafficName, trafficSize);

		// success
		return 0;
	}

	void writeBoolA(const char* message)
	{
		// cout << "writeBoolA " << string(message) << endl;
		writeBool(string(message));
	}

	string tempBool;

	int readBoolA(BSTR* result)
	{
		tempBool = readBool();
		// cout << "result readBool(): \"" << tempBool << "\"" << endl;
		CString s(tempBool.c_str());
		*result = s.AllocSysString();
		return 0;
	}

	void writeNetworkA(const char* message)
	{
		// cout << "writeNetworkA " << string(message) << endl;
		writeNetwork(string(message));
	}

	string tempNetwork;

	int readNetworkA(BSTR* result)
	{
		tempNetwork = readNetwork();
		CString s(tempNetwork.c_str());
		*result = s.AllocSysString();
		return 0;
	}

	void writeTrafficA(const char* message)
	{
		writeTraffic(string(message));
	}

	string tempTraffic;

	int readTrafficA(BSTR* result)
	{
		tempTraffic = readTraffic();
		CString s(tempTraffic.c_str());
		*result = s.AllocSysString();
		return 0;
	}
}

void writeBool(string message) {
	// cout << "writeBool \"" << message << "\"" << endl;
	CopyMemory((VOID*)pointers.bools.pointer, (VOID*)message.c_str(), message.length());
}

void writeNetwork(string message) {
	CopyMemory((VOID*)pointers.network.pointer, (VOID*)message.c_str(), message.length());
}

void writeTraffic(string message) {
	CopyMemory((VOID*)pointers.traffic.pointer, (VOID*)message.c_str(), message.length());
}

std::string readData(MemLoc location)
{
	char* data = (char*)location.pointer;
    string result = string(data);
	*data = '\0';
	// cout << "readData \"" << result << "\"" << endl;
	return result;
}

std::string readBool()
{
	return readData(pointers.bools);
}

std::string readNetwork()
{
	return readData(pointers.network);
}

std::string readTraffic()
{
	return readData(pointers.traffic);
}
