#pragma once
#include "framework.h"
#include "pch.h"
#define CONNECTSUMO_API __declspec(dllexport) 

extern "C" {
	class memLoc {
	public:
		HANDLE handle;
		LPCTSTR pointer;
	};
	class locus {
	public:
		memLoc bools;
		memLoc network;
		memLoc traffic;
	};
	CONNECTSUMO_API int reserveAllMemory(locus pointers, int networkSize, int trafficSize, int boolSize);
	CONNECTSUMO_API void closeMemory(LPCTSTR map, HANDLE handle);
	CONNECTSUMO_API void writeBool(PVOID boolMap, TCHAR boolMessage[], int boolSize = 10);
	CONNECTSUMO_API void writeNetwork(PVOID networkMap, TCHAR networkMessage[]);
	CONNECTSUMO_API LPCTSTR readReservedMemory(TCHAR szName[], int bufferSize);
}