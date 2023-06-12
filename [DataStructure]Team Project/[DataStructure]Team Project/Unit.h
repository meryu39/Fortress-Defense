#pragma once
#include"ProgramBase.h"
#include"PrintScreen.h"


#define MAX_UNITQUEUE (5+1)		//����ť�� ���ڸ��� full ���� ���п뵵�� ���Ƿ� �ִ��ڸ�+1
#define UNIT_SPEED 1
#define SPAWNPOINT_TEAM_X 3
#define SPAWNPOINT_TEAM_Y FIELD_HEIGHT - 1
#define SPAWNPOINT_ENEMY_X FIELD_WIDTH - 6
#define SPAWNPOINT_ENEMY_Y FIELD_HEIGHT - 1

// ���翡 ���� �����
#define SOLDIER_SPAWNTIME 60
#define SOLDIER_MAXHP 100
#define SOLDIER_RANGE 1
#define SOLDIER_DAMAGE 30
#define SOLDIER_PRICE 35
#define SOLDIER_KILLBONUS 15
#define SOLDIER_DELAYMOVE 15
#define SOLDIER_DELAYATTACK 15
// �ú��� ���� �����
#define ARCHER_SPAWNTIME 100
#define ARCHER_MAXHP 85
#define ARCHER_RANGE 5
#define ARCHER_DAMAGE 25
#define ARCHER_PRICE 50
#define ARCHER_KILLBONUS 25
#define ARCHER_DELAYMOVE 15
#define ARCHER_DELAYATTACK 15
// â���� ���� �����
#define SPEAR_SPAWNTIME 120
#define SPEAR_MAXHP 110
#define SPEAR_RANGE 2
#define SPEAR_DAMAGE 40
#define SPEAR_PRICE 75
#define SPEAR_KILLBONUS 40
#define SPEAR_DELAYMOVE 15
#define SPEAR_DELAYATTACK 15
// ��â���� ���� �����
#define JAVELIN_SPAWNTIME 160
#define JAVELIN_MAXHP 90
#define JAVELIN_RANGE 5
#define JAVELIN_DAMAGE 35
#define JAVELIN_PRICE 110
#define JAVELIN_KILLBONUS 65
#define JAVELIN_DELAYMOVE 15
#define JAVELIN_DELAYATTACK 15
// �⸶���� ���� �����
#define HORSE_SPAWNTIME 180
#define HORSE_MAXHP 130
#define HORSE_RANGE 1
#define HORSE_DAMAGE 50
#define HORSE_PRICE 150
#define HORSE_KILLBONUS 90
#define HORSE_DELAYMOVE 10
#define HORSE_DELAYATTACK 15
// �����⿡ ���� �����
// ����翡 ���� �����
#define PALADIN_SPAWNTIME 240
#define PALADIN_MAXHP 170
#define PALADIN_RANGE 1
#define PALADIN_DAMAGE 70
#define PALADIN_PRICE 240
#define PALADIN_KILLBONUS 110
#define PALADIN_DELAYMOVE 20
#define PALADIN_DELAYATTACK 15

// �屺�� ���� �����
#define GENERAL_SPAWNTIME 300
#define GENERAL_MAXHP 250
#define GENERAL_RANGE 1
#define GENERAL_DAMAGE 80
#define GENERAL_PRICE 280
#define GENERAL_KILLBONUS 130
#define GENERAL_DELAYMOVE 25
#define GENERAL_DELAYATTACK 15


enum unitcode {SOLDIER = 1, ARCHER,SPEAR,JAVELIN, HORSE, PALADIN,GENERAL
};
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
void init_unit(int currentStage);

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

void nextStage();
void replay();


int HighUnit();
int my_unitX();
int get_random();
int UnitAI();
int myunit_find();
int UnitAI();

