#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

#include "metrics.h"

void setWindowSize()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(h, &bufferInfo);
	SMALL_RECT& winInfo = bufferInfo.srWindow;
	COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };
	if (windowSize.X > COLS || windowSize.Y > ROWS)
	{
		SMALL_RECT info =
		{
			0,
			0,
			COLS < windowSize.X ? COLS - 1 : windowSize.X - 1,
			ROWS < windowSize.Y ? ROWS - 1 : windowSize.Y - 1
		};
		SetConsoleWindowInfo(h, TRUE, &info);
	}
	COORD size = { COLS, ROWS };
	SetConsoleScreenBufferSize(h, size);
	SMALL_RECT info = { 0, 0, COLS - 1, ROWS - 1 };
	SetConsoleWindowInfo(h, TRUE, &info);
	SetConsoleTitleA("Softporn Adventure");
}

void clearScreen()
{
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, ' ', cells, tl, &written);
	FillConsoleOutputAttribute(console, REGULARCOLOR, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

void setPos(int x, int y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { (short)x, (short)y };
	SetConsoleCursorPosition(console, coord);
}

void getPos(int *x, int *y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 };
	GetConsoleScreenBufferInfo(console, &csbi);
	if (x != NULL) *x = csbi.dwCursorPosition.X;
	if (y != NULL) *y = csbi.dwCursorPosition.Y;
}

void setColor(int color)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (short)color);
}

void writeHeader(int line, const char* leftText, const char* rightText)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	int x, y;
	CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 };
	GetConsoleScreenBufferInfo(console, &csbi);
	getPos(&x, &y);
	SetConsoleTextAttribute(console, HEADERCOLOR);
	setPos(0, line);
	for (int i = 0; i < COLS; i++)
		putchar(' ');
	if (leftText != NULL)
	{
		setPos(1, line);
		puts(leftText);
	}
	if (rightText != NULL)
	{
		setPos(COLS - 1 - strlen(rightText), 0);
		puts(rightText);
	}
	SetConsoleTextAttribute(console, REGULARCOLOR);
	setPos(x, y);
}

void delay(int ms)
{
	Sleep(ms);
}

char getKey()
{
	char answer = (char)toupper(_getche());
	puts("");
	return answer;
}

char getOneOf(char key1, char key2, char key3)
{
	key1 = (char)toupper(key1);
	key2 = (char)toupper(key2);
	key3 = (char)toupper(key3);
loop:
	char answer = (char)toupper(_getch());
	if (answer == key1 || answer == key2 || (key3 != 0 && answer == key3))
	{
		_putch(answer);
		puts("");
		return answer;
	}
	else
	{
		Beep(1000, 10);
		goto loop;
	}
}

char* getString(char* buffer, int max)
{
	int x, y;
	size_t r = 0;

	getPos(&x, &y);
	if (y >= ROWS - 1)
	{
		puts("");
		y--;
	}
	do
	{
#ifdef HAVESAFE
		setPos(x, y);
		_cgets_s(buffer, max, &r);
#if _WIN32
		char hack[4];
		size_t hr = 0;
		_cgets_s(hack, 4, &hr);
#endif
#else
	gets(buffer);
	r = strlen(buffer);
#endif
	if (r == 0)
			Beep(1000, 10);
	} while (r == 0);
	return buffer;
}
