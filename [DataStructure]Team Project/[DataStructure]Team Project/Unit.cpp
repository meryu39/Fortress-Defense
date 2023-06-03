#include"Unit.h"

extern FieldData field[FIELD_HEIGHT][FIELD_WIDTH];
LinkedList_currentUnit* head;

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
		if (enemy) // 적 모양을 다르게 하기 위한 임시방편
		{
			field[spawnpoint_y][spawnpoint_x].shape.color = RED;
			field[spawnpoint_y][spawnpoint_x].shape.look = 'B';
		}
		break;

	}
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
		if (nowNode->unit->hp <= 0)
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
					goto_xy({ 0, 28 });
					printf("공격했습니다!\n");
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
			if (is_move)	continue;
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
//AI
/*
int Highmyunit();

int get_random() {
	return (rand() % 2) + 1;
}
int enemy_find(){
	int count = 0;

	for (LinkedList_currentUnit* nowNode = head->rlink; nowNode != head; nowNode = nowNode->rlink)
	{
		if (nowNode->unit->enemy)
		{
			count++;
		}
	}

	return count;
}

int UnitAI()
{
	int Tag = 1; // 초기 Tick 값 설정
	int count_enemy_unit = enemy_find(); // 필드에 존재하는 적 유닛 수
	int level_my_unit = Highmyunit(); // 필드에 존재하는 아군 유닛 최고 티어 레벨
	int random_level; // 랜덤으로 선택된 레벨 변수

	while (Tag != 0)
	{
		switch (Tag)
		{
		case 1: // 기본 생성
			if (count_enemy_unit <= 3)
			{
				random_level = get_random(); // 1 또는 2 레벨 중 랜덤 선택
				spawnEnemyUnit(random_level);
			}
			if (level_my_unit > 4)
			{
				random_level = level_my_unit - 2; // 아군 유닛 최고 티어 레벨에서 2 감소
				spawnEnemyUnit(random_level);
				Tag = 0;
			}
			break;

		case 2: // 좌표 관련 생성
			if (my_unit.x > 70) // 70% 이상 넘어왔을 때
			{
				level_my_unit = Highmyunit();
				random_level = get_random(); // 1 또는 2 레벨 중 랜덤 선택
				if (level_my_unit > 2)
				{
					random_level = level_my_unit - random_level; // 아군 유닛 최고 티어 레벨에서 -1 또는 -2
				}
				spawnEnemyUnit(random_level);
				Tag = 0;
			}
			else if (my_unit.x > 50) // 50% 이상 넘어왔을 때
			{
				random_level = get_random() // 1 또는 2 레벨 중 랜덤 선택
				spawnEnemyUnit(random_level);
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