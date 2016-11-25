#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <TlHelp32.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <random>
#include <conio.h>
#include <stdint.h>
#include <thread>
#include <stdlib.h>
#include <process.h>
#include <unordered_map>

#include <stdint.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")

#include <windowsx.h>
#include <psapi.h>
#include <time.h>
#include <d3d9.h>
#include <Dwmapi.h> 
#include <TlHelp32.h>  
#include <stack>
#include <vector>
#include <future>

#include "XorString.h"

#define M_RADPI 57.295779513082f
#define M_PI 3.14159265358979323846f
#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)
extern float(*pfSqrt)(float x);
#define FastSqrt(x)			(*pfSqrt)(x)
#define PI 3.14159265358979323846f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
#define square( x ) ( x * x )
#define DEG2RAD_F( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define FLOAT32_NAN_BITS     (unsigned long)0x7FC00000
#define FLOAT32_NAN          BitsToFloat( FLOAT32_NAN_BITS )
#define VEC_T_NAN FLOAT32_NAN

#define MAX_WEAPONS 64
#define MAX_PLAYERS 128



#pragma warning(disable:4996)
#pragma warning(disable:4018)
#pragma warning(disable:4244)
#pragma warning(disable:4172)
#pragma warning(disable:4800)

class C_Local
{
public:
	DWORD Local;

	void GetLocal();
	int  GetCrosshairID();
	int  GetTeam();
	bool Isteam();
	bool CanHitEnemy();
	void shoot();
};

class C_Entity
{
public:
	DWORD Entity;

	void GetEntity(int i);
	int  GetTeam();
	int  GetHealth();
	bool GetDormant();
	int GetGlowIndex();
	DWORD GlowPointer();
};

class C_Engine {
public:
	DWORD Engine;

	bool isenemy();
};


namespace G
{
	namespace Main
	{
		extern C_Local* Local;
		extern C_Entity* Entity;
		extern C_Engine* Engine;
	}
	namespace DLL
	{
		namespace Client
		{
			extern DWORD DLL;
			extern DWORD DLL_SIZE;
		}
		namespace Engine
		{
			extern DWORD DLL;
			extern DWORD DLL_SIZE;
		}
	}
	namespace Offsets
	{
		extern DWORD m_dwLocalPlayer;
		extern DWORD m_dwLocalPlayerindex;
		extern DWORD m_dwEntityList;
		extern DWORD m_iCrosshairID;
		extern DWORD m_fFlags;
		extern DWORD m_iTeamNum;
		extern DWORD m_VecOrigin;
		extern DWORD m_VecViewOffset;
		extern DWORD m_VecVelocity;
		extern DWORD m_dwBoneMatrix;
		extern DWORD forceattack;
		extern DWORD m_dwClientState;
		extern DWORD m_dwViewAngles;
		extern DWORD m_bDormant;
		extern DWORD m_iHealth;
		extern DWORD m_iItemDefinitionIndex;
		extern DWORD m_VecPunch;
		extern DWORD m_dwViewMatrix;
		extern DWORD console;
		extern DWORD m_dwGlowObject;
		extern DWORD m_iGlowIndex;
		extern DWORD m_dwGlobalVars;
		extern DWORD m_hActiveWeapon;
		extern DWORD m_iWeaponID;
		extern DWORD m_iClip1;
	}
}