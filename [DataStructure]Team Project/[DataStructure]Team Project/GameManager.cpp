#pragma once
#include"GameManager.h"

extern FieldData field[FIELD_HEIGHT][FIELD_WIDTH];

void init_game()
{
	init_unit();
	printScreen(NULL);
	for (int y = 0; y < FIELD_HEIGHT; y++)
	{
		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			field[y][x].code = 0;
			field[y][x].shape.look = ' ';
			field[y][x].shape.color = 7;
			field[y][x].unitData = NULL;
		}
	}
}

void inputManager()
{
	if (kbhit())
	{
		switch (getch())
		{
		case'1':
			spawnQueue(SOLDIER, SOLDIER_SPAWNTIME);
			break;
		case'2':
			spawnQueue(ARCHER, ARCHER_SPAWNTIME);
			break;
		case'3':
			break;
		case'4':
			break;
		case'5':

			break;
		case'6':

			break;
		case'7':

			break;
		case'8':

			break;
		case'9':

			break;
		}



	}
}