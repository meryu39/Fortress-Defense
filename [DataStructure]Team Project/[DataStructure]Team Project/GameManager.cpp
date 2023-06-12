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
		printf("��");
		goto_xy(i, FIELD_HEIGHT );
		printf("��");
	}

	for (int i = 1; i < FIELD_HEIGHT; i++) {
		goto_xy(0, i);
		printf("��");
		goto_xy(FIELD_WIDTH, i);
		printf("��");
	}

	goto_xy(0, 0);
	printf("��");
	goto_xy(0, FIELD_HEIGHT);
	printf("��");
	goto_xy(FIELD_WIDTH, 0);
	printf("��");
	goto_xy(FIELD_WIDTH, FIELD_HEIGHT);
	printf("��");

	for (int i = 0; i < 30; i++)
	{
		if (i % 6 == 0)
		{
			goto_xy(i, FIELD_HEIGHT + 2);
			printf("��");
			goto_xy(i, FIELD_HEIGHT + 3);
			printf("��");
			goto_xy(i, FIELD_HEIGHT + 4);
			printf("��");
		}
		if (i % 6 == 1 || i%6 == 2 || i%6 == 3)
		{
			goto_xy(i, FIELD_HEIGHT + 2);
			printf("��");
			goto_xy(i, FIELD_HEIGHT + 2);
			goto_xy(i, FIELD_HEIGHT + 4);
			printf("��");
		}
		if (i % 6 == 4)
		{
			goto_xy(i, FIELD_HEIGHT + 2);
			printf("��");
			goto_xy(i, FIELD_HEIGHT + 3);
			printf("��");
			goto_xy(i, FIELD_HEIGHT + 4);
			printf("��");
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
			if (resource > SOLDIER_PRICE)
			{
				resource -= SOLDIER_PRICE;
				spawnQueue(SOLDIER, SOLDIER_SPAWNTIME);
			}
			break;
		case'2':
			if (resource > ARCHER_PRICE)
			{
				resource -= ARCHER_PRICE;
				spawnQueue(ARCHER, ARCHER_SPAWNTIME);
			}
			break;
		case'3':
			if (resource > SPEAR_PRICE)
			{
				resource -= SPEAR_PRICE;
				spawnQueue(SPEAR, SPEAR_SPAWNTIME);
			}
			break;
		case'4':
			if (resource > JAVELIN_PRICE)
			{
				resource -= JAVELIN_PRICE;
				spawnQueue(JAVELIN, JAVELIN_SPAWNTIME);
			}
			break;
		case'5':
			if (resource > HORSE_PRICE)
			{
				resource -= HORSE_PRICE;
				spawnQueue(HORSE, HORSE_SPAWNTIME);
			}
			break;
		case'6':
			if (resource > PALADIN_PRICE)
			{
				resource -= PALADIN_PRICE;
				spawnQueue(PALADIN, PALADIN_SPAWNTIME);
			}
			break;
		case'7':
			if (resource > GENERAL_PRICE)
			{
				resource -= GENERAL_PRICE;
				spawnQueue(GENERAL, GENERAL_SPAWNTIME);
			}
			break;
		}
	}
}

void resourceManager()
{
	resource += INCREASE_RESOURCE_BASIC;
}