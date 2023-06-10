#include"Unit.h"


extern FieldData field[FIELD_HEIGHT][FIELD_WIDTH];
LinkedList_currentUnit* head;

Unit *mycamp;
Unit *enemycamp;


void spawnUnit(int unitCode, bool enemy)
{
	
	Unit* newUnit = (Unit*)malloc(sizeof(Unit));
	// ������ ���� ����Ʈ ����
	int spawnpoint_x = enemy ? SPAWNPOINT_ENEMY_X : SPAWNPOINT_TEAM_X;
	int spawnpoint_y = enemy ? SPAWNPOINT_ENEMY_Y : SPAWNPOINT_TEAM_Y;
	newUnit->x = spawnpoint_x;
	newUnit->y = spawnpoint_y;
	
	
	
	// ���� ������ ���ֿ� ���� ������ �Է��Ѵ�. unitCode�� ������ ������ �ǹ��Ѵ�.
	newUnit->enemy = enemy;
	newUnit->unit_code = unitCode;
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
		field[spawnpoint_y][spawnpoint_x].shape.look = 'A';

		break;
	case 2:
		newUnit->hp = ARCHER_MAXHP;
		newUnit->range = ARCHER_RANGE;
		newUnit->damage = ARCHER_DAMAGE;
		newUnit->price = ARCHER_PRICE;
		newUnit->kill_bonus = ARCHER_KILLBONUS;
		newUnit->cooltime_move = ARCHER_DELAYMOVE;
		newUnit->cooltime_attack = ARCHER_DELAYATTACK;
		newUnit->delay_move = ARCHER_DELAYMOVE;
		newUnit->delay_attack = ARCHER_DELAYATTACK;
		field[spawnpoint_y][spawnpoint_x].shape.look = 'B';

		break;
	case 3:
		newUnit->hp = SPEAR_MAXHP;
		newUnit->range = SPEAR_RANGE;
		newUnit->damage = SPEAR_DAMAGE;
		newUnit->price = SPEAR_PRICE;
		newUnit->kill_bonus = SPEAR_KILLBONUS;
		newUnit->cooltime_move = SPEAR_DELAYMOVE;
		newUnit->cooltime_attack = SPEAR_DELAYATTACK;
		newUnit->delay_move = SPEAR_DELAYMOVE;
		newUnit->delay_attack = SPEAR_DELAYATTACK;
		field[spawnpoint_y][spawnpoint_x].shape.look = 'C';
		break;
	case 4:
		newUnit->hp = JAVELIN_MAXHP;
		newUnit->range = JAVELIN_RANGE;
		newUnit->damage = JAVELIN_DAMAGE;
		newUnit->price = JAVELIN_PRICE;
		newUnit->kill_bonus = JAVELIN_KILLBONUS;
		newUnit->cooltime_move = JAVELIN_DELAYMOVE;
		newUnit->cooltime_attack = JAVELIN_DELAYATTACK;
		newUnit->delay_move = JAVELIN_DELAYMOVE;
		newUnit->delay_attack = JAVELIN_DELAYATTACK;
		field[spawnpoint_y][spawnpoint_x].shape.look = 'D';
		break;
	case 5:
		newUnit->hp = HORSE_MAXHP;
		newUnit->range = HORSE_RANGE;
		newUnit->damage = HORSE_DAMAGE;
		newUnit->price = HORSE_PRICE;
		newUnit->kill_bonus = HORSE_KILLBONUS;
		newUnit->cooltime_move = HORSE_DELAYMOVE;
		newUnit->cooltime_attack = HORSE_DELAYATTACK;
		newUnit->delay_move = HORSE_DELAYMOVE;
		newUnit->delay_attack = HORSE_DELAYATTACK;
		field[spawnpoint_y][spawnpoint_x].shape.look = 'F';
		break;
	case 6:
		newUnit->hp = PALADIN_MAXHP;
		newUnit->range = PALADIN_RANGE;
		newUnit->damage = PALADIN_DAMAGE;
		newUnit->price = PALADIN_PRICE;
		newUnit->kill_bonus = PALADIN_KILLBONUS;
		newUnit->cooltime_move = PALADIN_DELAYMOVE;
		newUnit->cooltime_attack = PALADIN_DELAYATTACK;
		newUnit->delay_move = PALADIN_DELAYMOVE;
		newUnit->delay_attack = PALADIN_DELAYATTACK;
		field[spawnpoint_y][spawnpoint_x].shape.look = 'G';
		break;
	case 7:
		newUnit->hp = GENERAL_MAXHP;
		newUnit->range = GENERAL_RANGE;
		newUnit->damage = GENERAL_DAMAGE;
		newUnit->price = GENERAL_PRICE;
		newUnit->kill_bonus = GENERAL_KILLBONUS;
		newUnit->cooltime_move = GENERAL_DELAYMOVE;
		newUnit->cooltime_attack = GENERAL_DELAYATTACK;
		newUnit->delay_move = GENERAL_DELAYMOVE;
		newUnit->delay_attack = GENERAL_DELAYATTACK;
		field[spawnpoint_y][spawnpoint_x].shape.look = 'H';
		break;
	}

	field[spawnpoint_y][spawnpoint_x].shape.color = enemy ? RED : BLUE;
	field[spawnpoint_y][spawnpoint_x].unitData = newUnit;
	field[spawnpoint_y][spawnpoint_x].code = unitCode;
	
	// ���߿��Ḯ��Ʈ�� ���ο� ���� ������ �߰��Ѵ�.
	LinkedList_insert(head, newUnit);
}

void unitControl()
{
	
	
	// ��ȣ�ۿ��� �Ͼ�� ����� ��ǥ�̴�. ���� �ÿ��� ���ݴ���� �ִ� ��ǥ, �̵� �ÿ��� �̵��� ��ǥ�̴�.
	int X;
	int Y;
	// �̵�/������ �� ��� true�� �ȴ�. �̸� ���� �̵� �� ������ ���ÿ� ���� �ʵ��� �����Ѵ�.
	bool is_attack = false;
	bool is_move = false;
	FieldData temp;

	for (LinkedList_currentUnit* nowNode = head->rlink; nowNode != head; nowNode = nowNode->rlink)
	{
		is_attack = false;
		is_move = false;
		// Ž���ϴ� ������ ü���� 0 ������ ��� ���߿��Ḯ��Ʈ���� ������ ������ �����Ѵ�.
		if (nowNode->unit->hp <= 0 || nowNode->unit->x >= FIELD_WIDTH || nowNode->unit->x <= 0)
		{
			LinkedList_currentUnit* deleteNode = nowNode;
			nowNode = nowNode->llink;
			head = LinkedList_delete(head, deleteNode);
			continue;
		}
		// Ž���ϴ� ������ ������ ������ ��� ��Ÿ� �ȿ� ���� �ִ��� Ȯ���ϰ� ������ �õ��Ѵ�.
		if (nowNode->unit->cooltime_attack <= 0)
		{
			for (int range = 1; range <= nowNode->unit->range; range++)
			{
				X = nowNode->unit->x + range * (nowNode->unit->enemy ? -1 : 1);
				Y = nowNode->unit->y;
				if (field[Y][X].unitData != NULL && field[nowNode->unit->y][nowNode->unit->x].unitData->enemy != field[Y][X].unitData->enemy)
				{
					attackUnit(nowNode->unit, field[Y][X].unitData);
					nowNode->unit->cooltime_attack = nowNode->unit->delay_attack;
					is_attack = true;
					break;
				}

			}
			if (is_attack)
			{
				continue;
			}
		}
		nowNode->unit->cooltime_attack--;
		// Ž���ϴ� ������ �̵��� ������ ��� �ٷ� �� ĭ�� �ٸ� ������ �ִ��� Ȯ���ϰ� �̵��� �õ��Ѵ�.
		if (nowNode->unit->cooltime_move <= 0)
		{
			X = nowNode->unit->x + 1 * (nowNode->unit->enemy ? -1 : 1);
			Y = nowNode->unit->y;
			if (field[Y][X].unitData == NULL)
			{
				temp = field[nowNode->unit->y][nowNode->unit->x];
				field[nowNode->unit->y][nowNode->unit->x] = field[Y][X];
				field[Y][X] = temp;
				nowNode->unit->x = X;
				nowNode->unit->y = Y;
				nowNode->unit->cooltime_move = nowNode->unit->delay_move;
				is_move = true;
			}
			//��ä ���� 
			if (is_move)
			{
				if (nowNode->unit->enemy && nowNode->unit->x < 5)
				{
					mycamp->hp -= nowNode->unit->damage;
					attackUnit(mycamp, nowNode->unit);
					LinkedList_currentUnit* deleteNode = nowNode;
					nowNode = nowNode->llink;
					head = LinkedList_delete(head, deleteNode);
					continue;
				}
				else if (!nowNode->unit->enemy && nowNode->unit->x > 86)
				{
					enemycamp->hp -= nowNode->unit->damage;
					attackUnit(mycamp, nowNode->unit);
					LinkedList_currentUnit* deleteNode = nowNode;
					nowNode = nowNode->llink;
					head = LinkedList_delete(head, deleteNode);
					continue;
				}
				goto_xy(0,12);
				printf("�Ʊ���ä: %d\n", mycamp->hp);
				goto_xy(80,12);
				printf("������ä: %d", enemycamp->hp);
				if (enemycamp->hp <= 0) {
					goto_xy(50, 5);
					printf("�Ʊ��¸�\n");
					//�������������� ���� �Լ�����
				}
				else if (mycamp->hp <= 0) {
					goto_xy(50, 5);
					printf("�����¸�\n");
					//�������� �ٽ� ���� 
				}
				continue;
			}
		}
		nowNode->unit->cooltime_move--;
	}
}

void attackUnit(Unit* attacker, Unit* attackedUnit)
{
	static int kill = 0;
	attackedUnit->hp -= attacker->damage;
	// ������ ������ ü���� 0 ������ ��� �ش� �ʵ��� ������ �ʱ�ȭ�Ѵ�.
	if (attackedUnit->hp <= 0)
	{
		field[attackedUnit->y][attackedUnit->x].code = 0;
		field[attackedUnit->y][attackedUnit->x].unitData = NULL;
		field[attackedUnit->y][attackedUnit->x].shape.color = WHITE;
		field[attackedUnit->y][attackedUnit->x].shape.look = ' ';
		
		goto_xy(0, 25);
		if (attackedUnit->enemy)
		{
			kill++;
			printf("������óġ! : %d����°\n", kill);
			// �� �ּ��� ����� ų���ʽ��� ���õ� �Լ��� ������ �ȴ�.
		}
		
	}

	return;
}

bool spawnQueue(int unitCode, int spawn_tick)
{
	static SpawnQueue spawnQueue[MAX_UNITQUEUE] = { 0 };
	static int frontIndex = 0;
	static int rearIndex = 0;

	goto_xy(0, 23);
	for (int i = 0; i < MAX_UNITQUEUE; i++)
	{
		if (rearIndex + i >= frontIndex)
		{
			printf("  ");
			continue;
		}
		printf("%d ", spawnQueue[(rearIndex+i)%MAX_UNITQUEUE].unitCode);
	}
	if (unitCode == -1 && frontIndex % MAX_UNITQUEUE != rearIndex % MAX_UNITQUEUE)
	{
		spawnQueue[rearIndex % MAX_UNITQUEUE].spawnTime--;
		if (spawnQueue[rearIndex % MAX_UNITQUEUE].spawnTime <= 0)
		{
			spawnUnit(spawnQueue[rearIndex % MAX_UNITQUEUE].unitCode, false);
			rearIndex++;
		}
	}
	if ((frontIndex + 1) % MAX_UNITQUEUE == rearIndex % MAX_UNITQUEUE)
	{
		goto_xy(0, 22);
		printf("��ȯ��⿭�� ����á���ϴ�.\n");
		return false;
	}
	else if (unitCode != -1)
	{
		spawnQueue[(frontIndex++) % MAX_UNITQUEUE] = { unitCode, spawn_tick };
		goto_xy(0, 22);
		printf("                                    ");
	}
	
	return true;
}



//AI

int HighUnit()
{
	int maxLevel = 0;

	for (LinkedList_currentUnit* nowNode = head->rlink; nowNode != head; nowNode = nowNode->rlink)
	{
		if (!nowNode->unit->enemy && nowNode->unit->unit_code > maxLevel)
		{
			maxLevel = nowNode->unit->unit_code;
		}
	}

	return maxLevel;
}

int my_unitX()
{
	int myunitX= -1;

	for (int y = 0; y < FIELD_HEIGHT; y++)
	{
		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			if (field[y][x].unitData != NULL && !field[y][x].unitData->enemy)
			{
				myunitX = x;
				break;
			}
		}
		if (myunitX != -1)
		{
			break;
		}
	}

	return myunitX;
}

int get_random() {
	return (rand() % 2) + 1;
}
int myunit_find(){
	int count = 0;

	for (LinkedList_currentUnit* nowNode = head->rlink; nowNode != head; nowNode = nowNode->rlink)
	{
		if (!nowNode->unit->enemy)
		{
			count++;
		}
	}

	return count;
}

int UnitAI()
{
	int Tag = 1; // �ʱ� Tag �� ����
	int count_my_unit = myunit_find(); // �ʵ忡 �����ϴ� �� ���� ��
	int level_my_unit = HighUnit(); // �ʵ忡 �����ϴ� �Ʊ� ���� �ְ� Ƽ�� ����
	int random_level; // �������� ���õ� ���� ����

	while (Tag != 0)
	{
		switch (Tag)
		{
		case 1: // �⺻ ����
			
			if (count_my_unit <= 10)
			{
				random_level = get_random(); // 1 �Ǵ� 2 ���� �� ���� ����
				spawnUnit(random_level, true); //���� ������ �Ű����� �߰��ؼ� ������ ���� �� �ֵ��� �ؾ��� !!!���� �Ǵ� ��� 
				Tag = 0;
			}
			else if (level_my_unit > 4)
			{
				goto_xy(0, 23);
				printf("level_my_unit : %d\n", level_my_unit);
				int unitlevel = level_my_unit - 2; // �Ʊ� ���� �ְ� Ƽ�� �������� 2 ����
				spawnUnit(unitlevel, true); //���� ������ ���� 
				Tag = 0;
			}
			break;

		case 2: // ��ǥ ���� ����
			int myunitx = my_unitX();
			if (myunitx > 70) // 70% �̻� �Ѿ���� ��
			{
				level_my_unit = HighUnit();
				random_level = get_random(); // 1 �Ǵ� 2 ���� �� ���� ����

				if (level_my_unit > 4)
				{
					random_level = level_my_unit - random_level; // �Ʊ� ���� �ְ� Ƽ�� �������� -1 �Ǵ� -2
				}
				spawnUnit(random_level, true);
				Tag = 0;
			}
			else if (myunitx > 50) // 50% �̻� �Ѿ���� ��
			{
				random_level = get_random(); // 1 �Ǵ� 2 ���� �� ���� ����
				spawnUnit(random_level, true);
				Tag = 0;
			}
			break;
		}
	}

	return 0;
}

void LinkedList_insert(LinkedList_currentUnit* before, Unit* newUnit)
{
	LinkedList_currentUnit* newList = (LinkedList_currentUnit*)malloc(sizeof(LinkedList_currentUnit));

	newList->unit = newUnit;
	newList->llink = before;
	newList->rlink = before->rlink;
	before->rlink->llink = newList;
	before->rlink = newList;

	return;
}

LinkedList_currentUnit* LinkedList_delete(LinkedList_currentUnit* head, LinkedList_currentUnit* deleteNode)
{
	deleteNode->llink->rlink = deleteNode->rlink;
	deleteNode->rlink->llink = deleteNode->llink;
	free(deleteNode);

	return head;
}

void init_unit()
{
	head = (LinkedList_currentUnit*)malloc(sizeof(LinkedList_currentUnit));
	head->rlink = head;
	head->llink = head;
}

void init_camp() {
	mycamp = (Unit*)malloc(sizeof(Unit));
	enemycamp = (Unit*)malloc(sizeof(Unit));
	mycamp->hp = 500;
	mycamp->damage = 5000;
	enemycamp->hp = 500;
	enemycamp->damage = 5000;
}