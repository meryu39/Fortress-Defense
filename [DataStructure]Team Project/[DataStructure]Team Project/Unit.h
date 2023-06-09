#pragma once
#include"ProgramBase.h"
#include"PrintScreen.h"


#define MAX_UNITQUEUE (5+1)		//����ť�� ���ڸ��� full ���� ���п뵵�� ���Ƿ� �ִ��ڸ�+1
#define UNIT_SPEED 1
#define SPAWNPOINT_TEAM_X 3
#define SPAWNPOINT_TEAM_Y FIELD_HEIGHT - 1
#define SPAWNPOINT_ENEMY_X FIELD_WIDTH - 9
#define SPAWNPOINT_ENEMY_Y FIELD_HEIGHT - 1

// ���翡 ���� �����
#define SOLDIER_SPAWNTIME 60
#define SOLDIER_MAXHP 100
#define SOLDIER_RANGE 1
#define SOLDIER_DAMAGE 30
#define SOLDIER_PRICE 35
#define SOLDIER_KILLBONUS 35
#define SOLDIER_DELAYMOVE 15
#define SOLDIER_DELAYATTACK 15
// �ú��� ���� �����
#define ARCHER_SPAWNTIME 100
#define ARCHER_MAXHP 85
#define ARCHER_RANGE 5
#define ARCHER_DAMAGE 25
#define ARCHER_PRICE 50
#define ARCHER_KILLBONUS 50
#define ARCHER_DELAYMOVE 15
#define ARCHER_DELAYATTACK 15
// â���� ���� �����

// ��â���� ���� �����

// �⸶���� ���� �����

// �����⿡ ���� �����

// ����翡 ���� �����

// �屺�� ���� �����


enum unitcode {SOLDIER = 1, ARCHER};
// ���� �ʵ忡 �ִ� ������ ������ ��� �ִ� ���߿��Ḯ��Ʈ �����̴�.
typedef struct LinkedList_currentUnit
{
	Unit* unit;
	struct LinkedList_currentUnit* llink;
	struct LinkedList_currentUnit* rlink;
}LinkedList_currentUnit;

typedef struct SpawnQueue
{
	int unitCode;
	int spawnTime;
}SpawnQueue;

//���ְ� ���õ� �����͸� �ʱ�ȭ�ϴ� �Լ��̴�.
void init_unit();

//unitCode�� �� ����(true�� �� ����)�� �Ű������� �޾� ������ ��ȯ�ϴ� �Լ��̴�. ���Ŀ� Ű�����ư�̺�Ʈ�� ��AI�� �� �Լ��� ȣ���ϸ� ���ϴ� ������ ��ȯ�� �� �ִ�.
void spawnUnit(int unitCode, bool enemy);

// �� �����Ӹ��� ������ ���¸� Ȯ���� �� �̵�/������ �����ϴ� �Լ��̴�.
void unitControl();
// ������ �������� �� ��ȣ�ۿ��� ��� �Լ��̴�. ���� �� ������ ��� ���� ���ʽ� ��忡 ���� ������ ������ �ȴ�.
void attackUnit(Unit* attacker, Unit* attackedUnit);

// ���� ��ȯ��⿭�� �����ϴ� �Լ��̴�. ��ȯ�ϰ��� �ϴ� ������ �ڵ�� ��ȯ�ð��� �����ϸ� �˾Ƽ� ���� ��ȯ��⿭�� �߰��Ͽ� �ð��� ���� �� �����ȴ�.
bool spawnQueue(int unitCode = -1, int spawn_tick = -1);

// ���ֿ� ����ϴ� ť�� ���Ḯ��Ʈ�� �����ϱ� ���� ����� ���̴�.
void LinkedList_insert(LinkedList_currentUnit* before, Unit* newUnit);
LinkedList_currentUnit* LinkedList_delete(LinkedList_currentUnit* head, LinkedList_currentUnit* deleteNode);

int HighUnit();
int my_unitX();
int get_random();
int UnitAI();
int myunit_find();
int UnitAI();

