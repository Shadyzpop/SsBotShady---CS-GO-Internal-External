#include "C_Triggerbot.h"
#include "C_Memory.h"

C_Triggerbot* G_Triggerbot = new C_Triggerbot();

void C_Triggerbot::Think()
{
	while (true)
	{
		if (GetAsyncKeyState(0xA4) && G::Main::Local->CanHitEnemy())
		{
			Sleep(1);
			G::Main::Local->shoot();
		}
		Sleep(1);
	}
}
void C_Triggerbot::weapon() {
}
int C_Triggerbot::weaponammo()
{
	return 0;
}