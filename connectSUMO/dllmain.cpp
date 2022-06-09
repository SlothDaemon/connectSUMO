#include "framework.h"
#include "pch.h"
#include "extern.h"

extern "C"
{
	// These are the names with which to address the locations in the pagefile for 
	// their respective contents.They are set in stone, and if any other application
	// just so happens to need to access these locations, too bad?? But I highly, 
	// highly doubt that would ever be the case. Surely, nobody is going to take
	// a name as strange as 'boolMappingObject'. Surely.
	TCHAR boolName[] = TEXT("Global\boolMappingObject");
	TCHAR networkName[] = TEXT("Global\networkMappingObject");
	TCHAR trafficName[] = TEXT("Global\trafficMappingObject");

	// In these memory locations their respective contents need to be stored which
	// is almost self-explanatory. I assume that network data is going to be 
	// stringified XML. However, I found that these files can get ginormous. Just be 
	// conservative with the network you send through. Or test the limits of the size
	// that shared memory can take. Your choice.
	TCHAR networkMessage[] = TEXT("Network message.");
	TCHAR trafficMessage[] = TEXT("Traffic message.");
	TCHAR boolMessage[] = TEXT("false");

	MemLoc reserveMemory(TCHAR memName[], int bufferSize) {
		HANDLE hMapFile;
		LPCTSTR pBuf;

		hMapFile = CreateFileMapping(
			INVALID_HANDLE_VALUE,    // use paging file
			NULL,                    // default security
			PAGE_READWRITE,          // read/write access
			0,                       // maximum object size (high-order DWORD)
			bufferSize,              // maximum object size (low-order DWORD)
			memName);                // name of mapping object

		if (hMapFile == NULL)
		{
			_tprintf(TEXT("Could not create file mapping object (%d).\n"),
				GetLastError());
			exit(1);
		}

		pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
			FILE_MAP_ALL_ACCESS, // read/write permission
			0,
			0,
			bufferSize);

		if (pBuf == NULL)
		{
			_tprintf(TEXT("Could not map view of file (%d).\n"),
				GetLastError());

			CloseHandle(hMapFile);
			exit(1);
		}

		MemLoc location;
		location.handle = hMapFile;
		location.pointer = pBuf;

		return location;
	}

	void closeMemory(LPCTSTR map, HANDLE handle) {
		UnmapViewOfFile(map);
		CloseHandle(handle);
	}

	int reserveAllMemory(Locus pointers, int networkSize, int trafficSize, int boolSize) {
		std::cout << "Reserving Memory!\n";
		MemLoc bools = reserveMemory(boolName, networkSize);
		MemLoc network = reserveMemory(networkName, trafficSize);
		MemLoc traffic = reserveMemory(trafficName, boolSize);

		pointers.bools = bools;
		pointers.network = network;
		pointers.traffic = traffic;

		return 0;
	}

	void writeBool(PVOID boolMap, TCHAR boolMessage[], int boolSize) {
		CopyMemory(boolMap, boolMessage, boolSize);
	}

	void writeNetwork(PVOID networkMap, TCHAR networkMessage[]) {
		CopyMemory(networkMap, networkMessage, (_tcslen(networkMessage) * sizeof(TCHAR)));
	}

	LPCTSTR readReservedMemory(TCHAR szName[], int bufferSize)
	{
		HANDLE hMapFile;
		LPCTSTR pBuf;

		hMapFile = OpenFileMapping(
			FILE_MAP_ALL_ACCESS,   // read/write access
			FALSE,                 // do not inherit the name
			szName);               // name of mapping object

		if (hMapFile == NULL)
		{
			_tprintf(TEXT("Could not open file mapping object (%d).\n"),
				GetLastError());
			exit(1);
		}

		pBuf = (LPTSTR)MapViewOfFile(hMapFile, // handle to map object
			FILE_MAP_ALL_ACCESS,  // read/write permission
			0,
			0,
			bufferSize);

		if (pBuf == NULL)
		{
			_tprintf(TEXT("Could not map view of file (%d).\n"),
				GetLastError());

			CloseHandle(hMapFile);
			exit(1);
		}

		#if DEBUG 
			MessageBox(NULL, pBuf, TEXT("Reading shared memory"), MB_OK);
		#endif

		UnmapViewOfFile(pBuf);
		CloseHandle(hMapFile);

		return pBuf;
	}
}


