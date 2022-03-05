#include "io_utils.h"
#include "Color.h"

using namespace std;

#ifndef WINDOWS
void gotoxy(int x, int y) {}
int _getch(void) { return 0; }
int _kbhit(void) { return 0; }
void Sleep(unsigned long) {}
void setTextColor(Color color) {}
void hideCursor() {}
void clear_screen() {}
#else
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;

	// Sets cursor position
	cout << flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
	// Hides cursor
	CONSOLE_CURSOR_INFO info = { 100, false };
	SetConsoleCursorInfo(hConsoleOutput, &info);
}
void setTextColor(Color colorToSet) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}
void hideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}


#endif