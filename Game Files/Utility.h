#pragma once
#include<Windows.h>
enum Color{BLACK,WHITE=15};

#define BROWN 6
#define GREEN 2
#define RED 4
#define LBLUE 9
#define YELLOW 14
#define GRAY 8
#define PINK 13
#define ORANGE 12
#define GREEN 10
#define BLUE 9
#define PURPLE 5


//void SetClr(int tcl, int bcl)
//{
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
//}
//
//
//void getRowColbyLeftClick(int& rpos, int& cpos)
//{
//	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
//	DWORD Events;
//	INPUT_RECORD InputRecord;
//	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
//	do
//	{
//		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
//		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
//		{
//			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
//			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
//			break;
//		}
//	} while (true);
//}
//
//
//void gotoRowCol(int rpos, int cpos)
//{
//	COORD scrn;
//	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
//	scrn.X = cpos;
//	scrn.Y = rpos;
//	SetConsoleCursorPosition(hOuput, scrn);
//}

