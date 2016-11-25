#include "C_Memory.h"

CMemory* pMemory = new CMemory();

CMemory::CMemory()
{
}

CMemory::~CMemory()
{
	CloseHandle(hProcess);
}

bool CMemory::read_memory(const uint32_t& address, void* buffer, const size_t& size)
{
	SIZE_T bytes_readed = 0;
	return !!ReadProcessMemory(hProcess, reinterpret_cast< const void* >(address), buffer, size, &bytes_readed);
}

DWORD CMemory::GetModuleSize(char* ModuleName)
{
	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);

	do
		if (!strcmp(mEntry.szModule, ModuleName))
		{
			CloseHandle(hModule);
			return (DWORD)mEntry.modBaseSize;
		}
	while (Module32Next(hModule, &mEntry));

	return 0;
}

void CMemory::GetProcess(char* ProcessName)
{
	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 ProcEntry;
	ProcEntry.dwSize = sizeof(ProcEntry);

	do
		if (!strcmp(ProcEntry.szExeFile, ProcessName))
		{
			PID = ProcEntry.th32ProcessID;
			CloseHandle(hPID);

			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
			return;
		}
	while (Process32Next(hPID, &ProcEntry));

	system(XorString("pause"));
	exit(0);
}

DWORD CMemory::GetModule(char* ModuleName)
{
	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);

	do
		if (!strcmp(mEntry.szModule, ModuleName))
		{
			CloseHandle(hModule);
			return (DWORD)mEntry.modBaseAddr;
		}
	while (Module32Next(hModule, &mEntry));

	return 0;
}

DWORD CMemory::FindSignature(DWORD base, DWORD size, BYTE* sign, char* mask)
{
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	DWORD offset = 0;
	while (offset < size)
	{
		VirtualQueryEx(hProcess, (LPCVOID)(base + offset), &mbi, sizeof(MEMORY_BASIC_INFORMATION));
		if (mbi.State != MEM_FREE)
		{
			BYTE* buffer = new BYTE[mbi.RegionSize];
			ReadProcessMemory(hProcess, mbi.BaseAddress, buffer, mbi.RegionSize, NULL);
			for (int i = 0; i < mbi.RegionSize; i++)
			{
				if (DataCompare(buffer + i, sign, mask))
				{
					delete[] buffer;
					return (DWORD)mbi.BaseAddress + i;
				}
			}

			delete[] buffer;
		}
		offset += mbi.RegionSize;
	}
	return 0;
}

bool CMemory::DataCompare(BYTE* data, BYTE* sign, char* mask)
{
	for (; *mask; mask++, sign++, data++)
	{
		if (*mask == 'x' && *data != *sign)
		{
			return false;
		}
	}
	return true;
}