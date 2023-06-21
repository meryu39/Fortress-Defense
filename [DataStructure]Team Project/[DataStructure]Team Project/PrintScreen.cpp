#pragma once
#include"PrintScreen.h"

char defaultMap[FIELD_HEIGHT][FIELD_WIDTH];
extern int resource;
extern Unit* mycamp;
extern Unit* enemycamp;

void setColor(unsigned short color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	return;
}

void goto_xy(SHORT x, SHORT y)
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
				switch (inputData[y][x].unitData->unit_code)
				{
				case 1:
					printf("■");
					break;
				case 2:
					printf("▲");
					break;
				case 3:
					printf("♠");
					break;
				case 4:
					printf("Ψ");
					break;
				case 5:
					printf("♣");
					break;
				case 6:
					printf("θ");
					break;
				case 7:
					printf("★");
					break;
				}
				//printf("%c", inputData[y][x].shape.look);
			}
		}
	}

	return;
}

void printUI()
{
	goto_xy(0, 11);
	setColor(WHITE);
	printf("GOLD%5d      ", resource);

	//체력 출력
	goto_xy(2, 2);
	printf("%d\n", mycamp->hp);
	goto_xy(93, 2);
	printf("%d", enemycamp->hp);
}

void printDamage(int x, int damage)
{
	


}