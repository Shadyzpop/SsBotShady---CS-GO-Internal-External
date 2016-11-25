#include "C_ConsoleManager.h"

C_ConsoleFunctions* G_ConsoleFunctions = new C_ConsoleFunctions();

void C_ConsoleFunctions::Init(bool GameFound)
{
	if (GameFound)
	{
		SetConsoleTitle(XorString("SsBot : Made by shady"));
	}
	else
	{
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen(XorString("CONIN$"), XorString("r"), stdin);
		freopen(XorString("CONOUT$"), XorString("w"), stdout);
		freopen(XorString("CONOUT$"), XorString("w"), stderr);
		SetConsoleTitle(XorString("SsBot : waiting.."));
	}
}

void C_ConsoleFunctions::SetConsoleCursor(bool cursor)
{
	CONSOLE_CURSOR_INFO curCursorInfo;
	curCursorInfo.bVisible = cursor;
	curCursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curCursorInfo);
}

void C_ConsoleFunctions::GotoXY(int x, int y)
{
	COORD CursorPosition = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void C_ConsoleFunctions::SetConsoleColor(concol textColor, concol bgColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}

void C_ConsoleFunctions::ClearScreen()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hStdOut;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count))
		return;

	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
		return;
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

int C_ConsoleFunctions::Getch()
{
	HANDLE hConsole;
	INPUT_RECORD inrec;
	DWORD count, mode;

	hConsole = GetStdHandle(STD_INPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE || !GetConsoleMode(hConsole, &mode) || !SetConsoleMode(hConsole, 0))
		return 0;

	FlushConsoleInputBuffer(hConsole);

	do
	{
		ReadConsoleInput(hConsole, &inrec, 1, &count);
	} while ((inrec.EventType != KEY_EVENT) || inrec.Event.KeyEvent.bKeyDown);

	SetConsoleMode(hConsole, mode);

	return inrec.Event.KeyEvent.wVirtualKeyCode;
}

void C_ConsoleFunctions::SetConsoleSize(int w, int h)
{
	HWND hConsole = GetConsoleWindow();	RECT r;

	GetWindowRect(hConsole, &r);

	MoveWindow(hConsole, r.left, r.top, w, h, TRUE);
}