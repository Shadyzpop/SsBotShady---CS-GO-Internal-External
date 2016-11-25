#include "SDK.h"


class CMemory
{
public:
	CMemory();
	~CMemory();

	DWORD PID;
	HANDLE hProcess;

	template <class cData>
	cData ReadMemory(DWORD AddressToRead)
	{
		cData cRead;
		ReadProcessMemory(hProcess, (LPVOID)AddressToRead, &cRead, sizeof(cData), NULL);
		return cRead;
	}
	template <class cData>
	cData WriteMemory(DWORD AddressToWrite, cData WhatToWrite)
	{
		WriteProcessMemory(hProcess, (LPVOID)AddressToWrite, &WhatToWrite, sizeof(cData), NULL);
		return 0;
	}
	template <class cData>
	bool WriteArray(DWORD dwAddress, const cData* ArrayToWrite, const size_t& dwArraySize)
	{
		return WriteProcessMemory(hProcess, (LPVOID)dwAddress, ArrayToWrite, sizeof(cData) * dwArraySize, NULL) == TRUE;
	}

	bool read_memory(const uint32_t& address, void* buffer, const size_t& size);
	virtual void  GetProcess(char* ProcessName);
	virtual DWORD GetModule(char* ModuleName);
	virtual DWORD FindSignature(DWORD base, DWORD size, BYTE* sign, char* mask);
	virtual DWORD GetModuleSize(char* ModuleName);
	virtual bool  DataCompare(BYTE* data, BYTE* sign, char* mask);
};

extern CMemory* pMemory;