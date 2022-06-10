#pragma once
#include "framework.h"
#include "pch.h"
#define CONNECTSUMO_API __declspec(dllexport) 

extern "C" {
	class MemLoc {
	public:
		HANDLE handle;
		LPCTSTR pointer;
	};
	class Locus {
	public:
		MemLoc bools;
		MemLoc network;
		MemLoc traffic;
	};
	CONNECTSUMO_API int reserveAllMemory(Locus pointers, int networkSize, int trafficSize, int boolSize);
	CONNECTSUMO_API void closeMemory(LPCTSTR map, HANDLE handle);
	CONNECTSUMO_API void writeBool(PVOID boolMap, TCHAR boolMessage[], int boolSize = 10);
	CONNECTSUMO_API void writeNetwork(PVOID networkMap, TCHAR networkMessage[]);
	CONNECTSUMO_API char* readReservedMemory(TCHAR szName[], int bufferSize);
	CONNECTSUMO_API void deleteCharPointer(char* memoryLeak);
}