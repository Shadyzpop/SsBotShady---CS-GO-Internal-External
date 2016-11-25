#include "varupdate.h"
#include "C_Memory.h"

varupdate* update = new varupdate();
void varupdate::lplayer() 
{
	DWORD start;
	start = pMemory->FindSignature(G::DLL::Client::DLL, G::DLL::Client::DLL_SIZE, (PBYTE)"\x8D\x34\x85\x00\x00\x00\x00\x89\x15\x00\x00\x00\x00\x8B\x41\x08\x8B\x48\x00", XorString("xxx????xx????xxxxx?"));
	DWORD p1 = pMemory->ReadMemory<DWORD>(start + 3);
	BYTE p2 = pMemory->ReadMemory<BYTE>(start + 18);
	G::Offsets::m_dwLocalPlayer = (p1 + p2) - G::DLL::Client::DLL;
	std::cout << XorString("               Updated LocalPlayer: 0x") << G::Offsets::m_dwLocalPlayer << std::endl;
}
void varupdate::entity()
{
	DWORD start;
	start = pMemory->FindSignature(G::DLL::Client::DLL, G::DLL::Client::DLL_SIZE, (PBYTE)"\x05\x00\x00\x00\x00\xC1\xE9\x00\x39\x48\x04", XorString("x????xx?xxx"));
	DWORD p1 = pMemory->ReadMemory<DWORD>(start + 1);
	BYTE p2 = pMemory->ReadMemory<BYTE>(start + 7);
	G::Offsets::m_dwEntityList = (p1 + p2) - G::DLL::Client::DLL;
	std::cout << XorString("               Updated Entitylist: 0x") << G::Offsets::m_dwEntityList << std::endl;
}
void varupdate::console()
{
	DWORD start;
	start = pMemory->FindSignature(G::DLL::Engine::DLL, G::DLL::Engine::DLL_SIZE, (PBYTE)"\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x81\xF9\x00\x00\x00\x00\x75\x0C\xA1\x00\x00\x00\x00\x35\x00\x00\x00\x00\xEB\x0B", XorString("xxxxx????xx????xxx????x????xx"));
	cond = start;
	std::cout << XorString("Updated Console: 0x") << start << std::endl;
}

