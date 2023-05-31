#include"Unit.h"

extern FieldData field[FIELD_HEIGHT][FIELD_WIDTH];
Unit* unitQueue[5];
int index = 0;

void spawnUnit(int unitCode, bool enemy)
{
	Unit* newUnit = (Unit*)malloc(sizeof(Unit));

	int spawnpoint_x = enemy ? SPAWNPOINT_ENEMY_X : SPAWNPOINT_TEAM_X;
	int spawnpoint_y = enemy ? SPAWNPOINT_ENEMY_Y : SPAWNPOINT_TEAM_Y;

	newUnit->x = spawnpoint_x;
	newUnit->y = spawnpoint_y;
	newUnit->enemy = enemy;
	
	switch (unitCode)
	{
	case 1:
		newUnit->hp = SOLDIER_MAXHP;
		newUnit->range = SOLDIER_RANGE;
		newUnit->damage = SOLDIER_DAMAGE;
		newUnit->price = SOLDIER_PRICE;
		newUnit->kill_bonus = SOLDIER_KILLBONUS;
		newUnit->cooltime_move = SOLDIER_DELAYMOVE;
		newUnit->cooltime_attack = SOLDIER_DELAYATTACK;
		newUnit->delay_move = SOLDIER_DELAYMOVE;
		newUnit->delay_attack = SOLDIER_DELAYATTACK;

		break;

	}

	field[spawnpoint_y][spawnpoint_x].unitData = newUnit;
	field[spawnpoint_y][spawnpoint_x].code = unitCode;
	field[spawnpoint_y][spawnpoint_x].shape.color = BLUE;
	field[spawnpoint_y][spawnpoint_x].shape.look = 'A';
	unitQueue[index++] = newUnit;
}

void unitControl()
{
	int X;
	int Y;
	bool attack = false;
	bool move = false;
	FieldData temp;
	static int check1 = 0;
	static int check2 = 0;
	static int check3 = 0;
	static int check4 = 0;
	for (int i = 0; i < MAX_UNITS; i++)
	{
		if (unitQueue[i] == NULL)
		{
			break;
		}
		//goto_xy(0, 25);
		//printf("check1(%d)\n", ++check1);
		if (unitQueue[i]->cooltime_attack <= 0)
		{
			for (int range = 1; range <= unitQueue[i]->range; range++)
			{
				X = unitQueue[i]->x + range * (unitQueue[i]->enemy ? -1 : 1);
				Y = unitQueue[i]->y;
				if (field[Y][X].unitData != NULL && field[unitQueue[i]->y][unitQueue[i]->x].unitData->enemy != field[Y][X].unitData->enemy)
				{
					attackUnit(unitQueue[i], field[Y][X].unitData);
					unitQueue[i]->cooltime_attack = unitQueue[i]->delay_attack;
					goto_xy({ 0, 28 });
					printf("공격했습니다!\n");
					attack = true;
					break;
				}
			}
			if (attack)	continue;
		}
		//goto_xy(0, 26);
		//printf("check2(%d)\n", ++check2);
		unitQueue[i]->cooltime_attack--;
		if (unitQueue[i]->cooltime_move <= 0)
		{
			X = unitQueue[i]->x + 1 * (unitQueue[i]->enemy ? -1 : 1);
			Y = unitQueue[i]->y;
			if (field[Y][X].unitData == NULL)
			{
				//goto_xy(0, 27);
				//printf("check3(%d)\n", ++check3);
				temp = field[unitQueue[i]->y][unitQueue[i]->x];
				field[unitQueue[i]->y][unitQueue[i]->x] = field[Y][X];
				field[Y][X] = temp;
				unitQueue[i]->x = X;
				unitQueue[i]->y = Y;
				move = true;
				unitQueue[i]->cooltime_move = unitQueue[i]->delay_move;
				//printf("check4(%d)\n", ++check4);
			}
			if (move)	continue;
		}
		unitQueue[i]->cooltime_move--;
	}
}
void attackUnit(Unit* attacker, Unit* attackedUnit)
{

	return;
}