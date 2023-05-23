#pragma once
#include"PrintScreen.h"

char defaultMap[FIELD_HEIGHT][FIELD_WIDTH];

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


void printScreen(FieldData (*inputData)[FIELD_WIDTH])
{
	static bool is_init = FALSE;
	static FieldData beforeData[FIELD_HEIGHT][FIELD_WIDTH];
	static char background[FIELD_HEIGHT][FIELD_WIDTH + 2];

	if (!is_init)
	{
		FILE* background_file = fopen("Background.txt", "r");
		bool lineEnd = FALSE;
		for (int y = 0; y < FIELD_HEIGHT; y++)
		{
			fgets(background[y], FIELD_WIDTH + 2, background_file);
			for (int x = 0; x < FIELD_WIDTH; x++)
			{
				beforeData[y][x].code = 0;
				if (background[y][x] == '\n' || background[y][x] == '\0')
				{
					lineEnd = TRUE;
				}
				if (lineEnd)
				{
					background[y][x] = ' ';
				}
				goto_xy(x * DOTSIZE_X, y * DOTSIZE_Y);
				setColor(BACKGROUND_COLOR);
				printf("%c", background[y][x]);
			}
			lineEnd = FALSE;
		}
		is_init = TRUE;
		fclose(background_file);
		return;
	}
	for (int y = 0; y < FIELD_HEIGHT; y++)
	{
		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			if (beforeData[y][x].code != inputData[y][x].code)
			{
				goto_xy(x * DOTSIZE_X, y * DOTSIZE_Y);
				beforeData[y][x] = inputData[y][x];
				if (inputData[y][x].code == 0)
				{
					setColor(BACKGROUND_COLOR);
					printf("%c", background[y][x]);

					continue;
				}
				setColor(inputData[y][x].shape.color);
				printf("%c", inputData[y][x].shape.look);
			}
		}
	}

	return;
}

void init_graph()
{
	return;
}