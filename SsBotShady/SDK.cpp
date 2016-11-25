#include "SDK.h"
#include "C_Memory.h"

C_Entity* entit = new C_Entity();
C_Local* loco = new C_Local();
//=============================
void C_Entity::GetEntity(int i)
{
	this->Entity = pMemory->ReadMemory<DWORD>(G::DLL::Client::DLL + G::Offsets::m_dwEntityList + (i * 0x10));
}
int C_Entity::GetHealth()
{
	return pMemory->ReadMemory<int>(this->Entity + G::Offsets::m_iHealth);
}
int C_Entity::GetTeam()
{
	return pMemory->ReadMemory<int>(this->Entity + G::Offsets::m_iTeamNum);
}
bool C_Entity::GetDormant() {
	return pMemory->ReadMemory<bool>(this->Entity + G::Offsets::m_bDormant);
}
int C_Entity::GetGlowIndex() {
	return pMemory->ReadMemory<int>(this->Entity + G::Offsets::m_iGlowIndex);
}
DWORD C_Entity::GlowPointer() {
	return pMemory->ReadMemory<DWORD>(G::DLL::Client::DLL + G::Offsets::m_dwGlowObject);
}
//=============================
void C_Local::GetLocal()
{
	this->Local = pMemory->ReadMemory<uintptr_t>(G::DLL::Client::DLL + G::Offsets::m_dwLocalPlayer);
}
int C_Local::GetCrosshairID()
{
	return pMemory->ReadMemory<int>(this->Local + G::Offsets::m_iCrosshairID);
}
bool C_Local::CanHitEnemy()
{
	int CrosshairID = this->GetCrosshairID();
	int Player = CrosshairID - 1;
	entit->GetEntity(Player);
	return (CrosshairID >= 0 && CrosshairID <= 64 && entit->GetTeam() != this->GetTeam() && entit->GetHealth() >= 1);
}
int C_Local::GetTeam()
{
	return pMemory->ReadMemory<int>(this->Local + G::Offsets::m_iTeamNum);
}
bool C_Local::Isteam() {
	if (G::Main::Entity->GetTeam() == this->GetTeam())
		return true;
	else
		return false;
}
void C_Local::shoot() {
	pMemory->WriteMemory<int>(G::DLL::Client::DLL + G::Offsets::forceattack, 5);
	Sleep(15);
	pMemory->WriteMemory<int>(G::DLL::Client::DLL + G::Offsets::forceattack, 4);
	Sleep(280);
}
//=============================
bool C_Engine::isenemy() {
	return (entit->GetTeam() == loco->GetTeam() || entit->GetTeam() == 0) ? false : true;
}
//=============================
namespace G
{
	namespace Main
	{
		C_Local* Local = new C_Local();
		C_Entity* Entity = new C_Entity();
		C_Engine* Engine = new C_Engine();
	}
	namespace DLL
	{
		namespace Client
		{
			DWORD DLL;
			DWORD DLL_SIZE;
		}
		namespace Engine
		{
			DWORD DLL;
			DWORD DLL_SIZE;
		}
	}
	namespace Offsets
	{
		DWORD m_dwLocalPlayer = 0xA9053C;
		DWORD m_dwLocalPlayerindex = 0x178;
		DWORD m_dwEntityList = 0x4AB1F54;
		DWORD m_iCrosshairID = 0xAA64;
		DWORD m_fFlags = 0x100;
		DWORD m_iTeamNum = 0xF0;
		//=====vec
		DWORD m_VecOrigin = 0x134;
		DWORD m_VecViewOffset = 0x104;
		DWORD m_VecVelocity = 0x110;
		DWORD m_dwBoneMatrix = 0x2698;
		DWORD m_dwClientState = 0x5C22C4;
		DWORD m_dwViewAngles = 0x4D0C;
		DWORD m_VecPunch = 0x301C;
		DWORD m_dwViewMatrix = 0x0;
		//=====other
		DWORD m_bDormant = 0xE9;
		DWORD m_iHealth = 0xFC;
		DWORD m_iItemDefinitionIndex = 0x2F88;
		DWORD forceattack = 0x2EF1F40;
		DWORD console = 0x0;
		DWORD m_dwGlowObject = 0x4FC9D74;
		DWORD m_iGlowIndex = 0xA320;
		DWORD m_dwGlobalVars = 0x4DB258;
		DWORD m_hActiveWeapon = 0x2EE8;
		DWORD m_iWeaponID = 0x32EC;
		DWORD m_iClip1 = 0x3204;
	}
}
//=============================