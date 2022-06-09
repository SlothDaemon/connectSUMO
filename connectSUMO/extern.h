#pragma once
#include "framework.h"
#include "pch.h"
#define CONNECTSUMO_API __declspec(dllexport) 

extern "C" {
	class handlesAndPointers {
	public:
		std::tuple<HANDLE, LPCTSTR> content[3];
	};
	CONNECTSUMO_API int reserveAllMemory(handlesAndPointers hap, int networkSize, int trafficSize, int boolSize = 10);
	CONNECTSUMO_API void closeMemory(LPCTSTR map, HANDLE handle);
	CONNECTSUMO_API void writeBool(PVOID boolMap, TCHAR boolMessage[], int boolSize = 10);
	CONNECTSUMO_API void writeNetwork(PVOID networkMap, TCHAR networkMessage[]);
	CONNECTSUMO_API LPCTSTR readReservedMemory(TCHAR szName[], int bufferSize);
}