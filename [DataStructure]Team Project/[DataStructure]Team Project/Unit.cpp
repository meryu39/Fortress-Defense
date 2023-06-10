#include"Unit.h"


extern FieldData field[FIELD_HEIGHT][FIELD_WIDTH];
LinkedList_currentUnit* head;

Unit *mycamp;
Unit *enemycamp;


void spawnUnit(int unitCode, bool enemy)
{
	
	Unit* newUnit = (Unit*)malloc(sizeof(Unit));
	// 유닛의 스폰 포인트 지정
	int spawnpoint_x = enemy ? SPAWNPOINT_ENEMY_X : SPAWNPOINT_TEAM_X;
	int spawnpoint_y = enemy ? SPAWNPOINT_ENEMY_Y : SPAWNPOINT_TEAM_Y;
	newUnit->x = spawnpoint_x;
	newUnit->y = spawnpoint_y;
	
	
	
	// 새로 스폰된 유닛에 대한 정보를 입력한다. unitCode은 유닛의 종류를 의미한다.
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
	
	// 이중연결리스트에 새로운 유닛 정보를 추가한다.
	LinkedList_insert(head, newUnit);
}

void unitControl()
{
	
	
	// 상호작용이 일어나는 대상의 좌표이다. 공격 시에는 공격대상이 있는 좌표, 이동 시에는 이동할 좌표이다.
	int X;
	int Y;
	// 이동/공격을 할 경우 true가 된다. 이를 통해 이동 및 공격을 동시에 하지 않도록 방지한다.
	bool is_attack = false;
	bool is_move = false;
	FieldData temp;

	for (LinkedList_currentUnit* nowNode = head->rlink; nowNode != head; nowNode = nowNode->rlink)
	{
		is_attack = false;
		is_move = false;
		// 탐색하는 유닛의 체력이 0 이하인 경우 이중연결리스트에서 유닛의 정보를 삭제한다.
		if (nowNode->unit->hp <= 0 || nowNode->unit->x >= FIELD_WIDTH || nowNode->unit->x <= 0)
		{
			LinkedList_currentUnit* deleteNode = nowNode;
			nowNode = nowNode->llink;
			head = LinkedList_delete(head, deleteNode);
			continue;
		}
		// 탐색하는 유닛이 공격이 가능한 경우 사거리 안에 적이 있는지 확인하고 공격을 시도한다.
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
		// 탐색하는 유닛이 이동이 가능한 경우 바로 앞 칸에 다른 유닛이 있는지 확인하고 이동을 시도한다.
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
			//성채 구현 
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
				printf("아군성채: %d\n", mycamp->hp);
				goto_xy(80,12);
				printf("적군성채: %d", enemycamp->hp);
				if (enemycamp->hp <= 0) {
					goto_xy(50, 5);
					printf("아군승리\n");
					//다음스테이지로 가는 함수선언
				}
				else if (mycamp->hp <= 0) {
					goto_xy(50, 5);
					printf("적군승리\n");
					//스테이지 다시 시작 
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
	// 공격한 유닛의 체력이 0 이하인 경우 해당 필드의 정보를 초기화한다.
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
			printf("적유닛처치! : %d마리째\n", kill);
			// 이 주석을 지우고 킬보너스와 관련된 함수를 넣으면 된다.
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
		printf("소환대기열이 가득찼습니다.\n");
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
	int Tag = 1; // 초기 Tag 값 설정
	int count_my_unit = myunit_find(); // 필드에 존재하는 적 유닛 수
	int level_my_unit = HighUnit(); // 필드에 존재하는 아군 유닛 최고 티어 레벨
	int random_level; // 랜덤으로 선택된 레벨 변수

	while (Tag != 0)
	{
		switch (Tag)
		{
		case 1: // 기본 생성
			if (level_my_unit > 4)
			{
				goto_xy(0, 23);
				printf("level_my_unit : %d\n", level_my_unit);
				int unitlevel = level_my_unit - 2; // 아군 유닛 최고 티어 레벨에서 2 감소
				spawnUnit(unitlevel, true); //유닛 레벨로 설정 
				Tag = 0;
				break;
			}
			random_level = get_random(); // 1 또는 2 레벨 중 랜덤 선택
			spawnUnit(random_level, true); //유닛 생성시 매개변수 추가해서 레벨을 받을 수 있도록 해야함 !!!레벨 또는 골드 
			Tag = 0;
			break;

		case 2: // 좌표 관련 생성
			int myunitx = my_unitX();
			if (myunitx > 70) // 70% 이상 넘어왔을 때
			{
				level_my_unit = HighUnit();
				random_level = get_random(); // 1 또는 2 레벨 중 랜덤 선택

				if (level_my_unit > 4)
				{
					random_level = level_my_unit - random_level; // 아군 유닛 최고 티어 레벨에서 -1 또는 -2
				}
				spawnUnit(random_level, true);
				Tag = 0;
			}
			else if (myunitx > 50) // 50% 이상 넘어왔을 때
			{
				random_level = get_random(); // 1 또는 2 레벨 중 랜덤 선택
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