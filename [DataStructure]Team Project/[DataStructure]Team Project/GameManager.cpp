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
			spawnQueue(SPEAR, SPEAR_SPAWNTIME);
			break;
		case'4':
			spawnQueue(JAVELIN, ARCHER_SPAWNTIME);
			break;
		case'5':
			spawnQueue(HORSE, ARCHER_SPAWNTIME);
			break;
		case'6':
			spawnQueue(PALADIN, ARCHER_SPAWNTIME);
			break;

		}
	}
}