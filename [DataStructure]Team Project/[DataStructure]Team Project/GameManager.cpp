#pragma once
#include"GameManager.h"

extern FieldData field[FIELD_HEIGHT][FIELD_WIDTH];
int resource = 0;
extern int currentStage;

void init_game()
{
	init_unit(currentStage);
	srand(time(NULL));
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
	init_UI();


}

void inputManager()
{
	if (kbhit())
	{
		switch (getch())
		{
		case'1':
			if (resource > SOLDIER_PRICE && spawnQueue(SOLDIER, SOLDIER_SPAWNTIME))
			{
				resource -= SOLDIER_PRICE;
			}
			break;
		case'2':
			if (resource > ARCHER_PRICE && spawnQueue(ARCHER, ARCHER_SPAWNTIME))
			{
				resource -= ARCHER_PRICE;
				
			}
			break;
		case'3':
			if (resource > SPEAR_PRICE && spawnQueue(SPEAR, SPEAR_SPAWNTIME))
			{
				resource -= SPEAR_PRICE;
				
			}
			break;
		case'4':
			if (resource > JAVELIN_PRICE && spawnQueue(JAVELIN, JAVELIN_SPAWNTIME))
			{
				resource -= JAVELIN_PRICE;
			}
			break;
		case'5':
			if (resource > HORSE_PRICE && spawnQueue(HORSE, HORSE_SPAWNTIME))
			{
				resource -= HORSE_PRICE;
			}
			break;
		case'6':
			if (resource > PALADIN_PRICE && spawnQueue(PALADIN, PALADIN_SPAWNTIME))
			{
				resource -= PALADIN_PRICE;
			}
			break;
		case'7':
			if (resource > GENERAL_PRICE && spawnQueue(GENERAL, GENERAL_SPAWNTIME))
			{
				resource -= GENERAL_PRICE;
			}
			break;
		}
	}
}

void resourceManager()
{
	resource += INCREASE_RESOURCE_BASIC;
}

void clearGame()
{
	return;
}