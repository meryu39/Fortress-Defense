#include"Unit.h"

extern FieldData field[FIELD_HEIGHT][FIELD_WIDTH];
LinkedList_currentUnit* head;

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
		field[spawnpoint_y][spawnpoint_x].shape.color = BLUE;
		field[spawnpoint_y][spawnpoint_x].shape.look = 'A';
		if (enemy) // �� ����� �ٸ��� �ϱ� ���� �ӽù���
		{
			field[spawnpoint_y][spawnpoint_x].shape.color = RED;
			field[spawnpoint_y][spawnpoint_x].shape.look = 'B';
		}
		break;

	}
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
		if (nowNode->unit->hp <= 0)
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
					goto_xy({ 0, 28 });
					printf("�����߽��ϴ�!\n");
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
			if (is_move)	continue;
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
//AI
/*
int HighUnit()
{
	int maxprice = 0;

	for (LinkedList_currentUnit* nowNode = head->rlink; nowNode != head; nowNode = nowNode->rlink)
	{
		if (!nowNode->unit->enemy && nowNode->unit->price > maxprice)
		{
			maxprice = nowNode->unit->price;
		}
	}

	return maxprice;
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
	int Tag = 1; // �ʱ� Tick �� ����
	int count_my_unit = myunit_find(); // �ʵ忡 �����ϴ� �� ���� ��
	int level_my_unit = HighUnit(); // �ʵ忡 �����ϴ� �Ʊ� ���� �ְ� Ƽ�� ����
	int random_level; // �������� ���õ� ���� ����

	while (Tag != 0)
	{
		switch (Tag)
		{
		case 1: // �⺻ ����
			
			if (count_my_unit <= 3)
			{
				random_level = get_random(); // 1 �Ǵ� 2 ���� �� ���� ����
				spawnUnit(1, true,random_level); //���� ������ �Ű����� �߰��ؼ� ������ ���� �� �ֵ��� �ؾ��� !!!���� �Ǵ� ��� 
				Tag = 0;
			}
			if (level_my_unit > 4)
			{
				int unitlevel = level_my_unit - 2; // �Ʊ� ���� �ְ� Ƽ�� �������� 2 ����
				spawnUnit(1, true, unitlevel); //���� ������ ���� 
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
				spawnUnit(1, true, random_level);
				Tag = 0;
			}
			else if (myunitx > 50) // 50% �̻� �Ѿ���� ��
			{
				random_level = get_random(); // 1 �Ǵ� 2 ���� �� ���� ����
				spawnUnit(1, true, random_level);
				Tag = 0;
			}
			break;
		}
	}

	return 0;
}
*/
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