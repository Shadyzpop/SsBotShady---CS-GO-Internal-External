#include "SDK.h"
#include "C_Memory.h"
#include "C_ConsoleManager.h"

//Include the functions to loop them here...
#include "C_Triggerbot.h"
#include "varupdate.h"
#include "mmc.h"

HWND csgo = NULL;
void INIT( HMODULE hModule )
{
	G_ConsoleFunctions->Init( false );
	G_ConsoleFunctions->SetConsoleColor( concol::red, concol::black );
	G_ConsoleFunctions->GotoXY( 25, 0);
	std::cout << XorString("Waiting..\n\n") << std::endl;
	while ( csgo == NULL )
	{
		csgo = FindWindow(NULL, XorString( "Counter-Strike: Global Offensive" ) );
		std::this_thread::sleep_for(std::chrono::seconds( 2 ) );
	}
	G_ConsoleFunctions->Init( true );
	G_ConsoleFunctions->SetConsoleColor( concol::green, concol::black );
	G_ConsoleFunctions->GotoXY( 25, 0);
	std::cout << XorString( "Running.." ) << std::endl;
	G_ConsoleFunctions->SetConsoleColor(concol::yellow, concol::black);
	//Get the process
	pMemory->GetProcess( XorString( "csgo.exe" ) );
	//Get client.dll
	G::DLL::Client::DLL = pMemory->GetModule( XorString( "client.dll" ) );
	G::DLL::Client::DLL_SIZE = pMemory->GetModuleSize( XorString( "client.dll" ) );
	//Get engine.dll
	G::DLL::Engine::DLL = pMemory->GetModule( XorString( "engine.dll") );
	G::DLL::Engine::DLL_SIZE = pMemory->GetModuleSize( XorString( "engine.dll" ) );

	//Offset Update functions =>>>
	G_ConsoleFunctions->SetConsoleColor(concol::white, concol::black);
	G_ConsoleFunctions->GotoXY(25, 2);
	std::cout << XorString("Modules: ") << std::endl;
	G_ConsoleFunctions->SetConsoleColor(concol::green, concol::black);
	update->lplayer();
	update->entity();
	//update->console();


	//threads
	std::thread triggerThread(&C_Triggerbot::Think, C_Triggerbot());


	//Infinite loop
	do {
		G::Main::Local->GetLocal();
		Sleep(1000);
	} while (true);
	system( XorString( "pause" ) );
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) 
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: 
		HANDLE leggokek = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(INIT), hModule, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		CloseHandle(leggokek);
		break;
	}
	return TRUE;
}