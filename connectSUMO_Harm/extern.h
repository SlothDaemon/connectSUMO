#pragma once
#include "framework.h"
#include "pch.h"
#include "atlbase.h"
#include "atlstr.h"

#define CONNECTSUMO_API __declspec(dllexport) 

extern "C" {
	CONNECTSUMO_API int reserveAllMemory(int networkSize, int trafficSize, int boolSize);
	CONNECTSUMO_API void closeMemory();
	CONNECTSUMO_API void writeBoolA(const char* message);
	CONNECTSUMO_API int readBoolA(BSTR * result);
	CONNECTSUMO_API void writeNetworkA(const char* message);
	CONNECTSUMO_API int readNetworkA(BSTR * message);
	CONNECTSUMO_API void writeTrafficA(const char* message);
	CONNECTSUMO_API int readTrafficA(BSTR * message);
}

CONNECTSUMO_API void writeBool(std::string boolMessage);
CONNECTSUMO_API void writeNetwork(std::string networkMessage);
CONNECTSUMO_API void writeTraffic(std::string trafficMessage);
CONNECTSUMO_API std::string readBool();
CONNECTSUMO_API std::string readNetwork();
CONNECTSUMO_API std::string readTraffic();