#pragma once
#include "pch.h"

class MemLoc {
public:
	HANDLE handle;
	LPCWSTR pointer;
	LPCWSTR name;
};

class Locus {
public:
	int id;
	MemLoc bools;
	MemLoc network;
	MemLoc traffic;
};