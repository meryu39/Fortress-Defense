#pragma once
#include"GameManager.h"

extern FieldData field[FIELD_HEIGHT][FIELD_WIDTH];
int resource = 0;
extern int currentStage;

void init_game()
{
	init_unit(currentStage);
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

	for (int i = 1; i < FIELD_WIDTH; i++) {
		goto_xy(i, 0);
		printf("收");
		goto_xy(i, FIELD_HEIGHT );
		printf("收");
	}

	for (int i = 1; i < FIELD_HEIGHT; i++) {
		goto_xy(0, i);
		printf("早");
		goto_xy(FIELD_WIDTH, i);
		printf("早");
	}

	goto_xy(0, 0);
	printf("旨");
	goto_xy(0, FIELD_HEIGHT);
	printf("曲");
	goto_xy(FIELD_WIDTH, 0);
	printf("旬");
	goto_xy(FIELD_WIDTH, FIELD_HEIGHT);
	printf("旭");

	for (int i = 0; i < 30; i++)
	{
		if (i % 6 == 0)
		{
			goto_xy(i, FIELD_HEIGHT + 2);
			printf("旨");
			goto_xy(i, FIELD_HEIGHT + 3);
			printf("早");
			goto_xy(i, FIELD_HEIGHT + 4);
			printf("曲");
		}
		if (i % 6 == 1 || i%6 == 2 || i%6 == 3)
		{
			goto_xy(i, FIELD_HEIGHT + 2);
			printf("收");
			goto_xy(i, FIELD_HEIGHT + 2);
			goto_xy(i, FIELD_HEIGHT + 4);
			printf("收");
		}
		if (i % 6 == 4)
		{
			goto_xy(i, FIELD_HEIGHT + 2);
			printf("旬");
			goto_xy(i, FIELD_HEIGHT + 3);
			printf("早");
			goto_xy(i, FIELD_HEIGHT + 4);
			printf("旭");
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