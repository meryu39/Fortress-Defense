#pragma once
#include"PrintScreen.h"

void setColor(unsigned short color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	return;
}

void goto_xy(short x, short y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	Position pos = { x, y };
	SetConsoleCursorPosition(handle, pos);
}

void goto_xy(Position pos)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
}


void printScreen(FieldData (*inputData)[WIDTHSIZE])
{
	static bool is_init = FALSE;
	static FieldData beforeData[HEIGHTSIZE][WIDTHSIZE];

	if (!is_init)
	{
		for (int y = 0; y < HEIGHTSIZE; y++)
		{
			for (int x = 0; x < WIDTHSIZE; x++)
			{
				goto_xy(x * DOTSIZE_X, y * DOTSIZE_Y);
				setColor(inputData[y][x].shape.color);
				printf("%c", inputData[y][x].shape.look);
				beforeData[y][x] = inputData[y][x];
			}
		}
		is_init = TRUE;
		return;
	}
	for (int y = 0; y < HEIGHTSIZE; y++)
	{
		for (int x = 0; x < WIDTHSIZE; x++)
		{
			if (beforeData[y][x].code != inputData[y][x].code)
			{
				goto_xy(x * DOTSIZE_X, y * DOTSIZE_Y);
				setColor(inputData[y][x].shape.color);
				printf("%c", inputData[y][x].shape.look);
				beforeData[y][x] = inputData[y][x];
			}
		}
	}

	return;
}