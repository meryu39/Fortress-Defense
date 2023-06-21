#pragma once
#include"ProgramBase.h"
#include"PrintScreen.h"
#include"GameManager.h"


#define MAX_UNITQUEUE (5+1)		//원형큐는 한자리를 full 여부 구분용도로 쓰므로 최대자리+1
#define UNIT_SPEED 1
#define SPAWNPOINT_TEAM_X 3
#define SPAWNPOINT_TEAM_Y FIELD_HEIGHT - 1
#define SPAWNPOINT_ENEMY_X FIELD_WIDTH - 6
#define SPAWNPOINT_ENEMY_Y FIELD_HEIGHT - 1

// 병사에 대한 상수값
#define SOLDIER_SPAWNTIME 60
#define SOLDIER_MAXHP 100
#define SOLDIER_RANGE 1
#define SOLDIER_DAMAGE 30
#define SOLDIER_PRICE 35
#define SOLDIER_KILLBONUS 15
#define SOLDIER_DELAYMOVE 15
#define SOLDIER_DELAYATTACK 15
// 궁병에 대한 상수값
#define ARCHER_SPAWNTIME 100
#define ARCHER_MAXHP 85
#define ARCHER_RANGE 5
#define ARCHER_DAMAGE 25
#define ARCHER_PRICE 50
#define ARCHER_KILLBONUS 25
#define ARCHER_DELAYMOVE 15
#define ARCHER_DELAYATTACK 15
// 창병에 대한 상수값
#define SPEAR_SPAWNTIME 120
#define SPEAR_MAXHP 110
#define SPEAR_RANGE 2
#define SPEAR_DAMAGE 40
#define SPEAR_PRICE 75
#define SPEAR_KILLBONUS 40
#define SPEAR_DELAYMOVE 15
#define SPEAR_DELAYATTACK 15
// 투창병에 대한 상수값
#define JAVELIN_SPAWNTIME 160
#define JAVELIN_MAXHP 90
#define JAVELIN_RANGE 5
#define JAVELIN_DAMAGE 35
#define JAVELIN_PRICE 110
#define JAVELIN_KILLBONUS 65
#define JAVELIN_DELAYMOVE 15
#define JAVELIN_DELAYATTACK 15
// 기마병에 대한 상수값
#define HORSE_SPAWNTIME 180
#define HORSE_MAXHP 130
#define HORSE_RANGE 1
#define HORSE_DAMAGE 50
#define HORSE_PRICE 150
#define HORSE_KILLBONUS 90
#define HORSE_DELAYMOVE 10
#define HORSE_DELAYATTACK 15
// 투석기에 대한 상수값
// 성기사에 대한 상수값
#define PALADIN_SPAWNTIME 240
#define PALADIN_MAXHP 170
#define PALADIN_RANGE 1
#define PALADIN_DAMAGE 70
#define PALADIN_PRICE 240
#define PALADIN_KILLBONUS 110
#define PALADIN_DELAYMOVE 20
#define PALADIN_DELAYATTACK 15

// 장군에 대한 상수값
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
// 현재 필드에 있는 유닛의 정보를 담고 있는 이중연결리스트 구조이다.
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



//유닛과 관련된 데이터를 초기화하는 함수이다.
void init_unit(int currentStage);

//unitCode와 적 유무(true면 적 유닛)을 매개변수로 받아 유닛을 소환하는 함수이다. 추후에 키보드버튼이벤트와 적AI가 이 함수를 호출하면 원하는 유닛을 소환할 수 있다.
void spawnUnit(int unitCode, bool enemy);

// 매 프레임마다 유닛의 상태를 확인한 후 이동/공격을 제어하는 함수이다.
void unitControl();
// 유닛이 공격했을 때 상호작용이 담긴 함수이다. 추후 적 유닛을 잡고 나서 보너스 골드에 대한 내용을 담으면 된다.
void attackUnit(Unit* attacker, Unit* attackedUnit);

// 유닛 소환대기열을 관리하는 함수이다. 소환하고자 하는 유닛의 코드와 소환시간을 전달하면 알아서 유닛 소환대기열에 추가하여 시간이 지난 후 스폰된다.
bool spawnQueue(int unitCode = -1, int spawn_tick = -1);

// 유닛에 사용하는 큐를 연결리스트로 구현하기 위해 사용한 것이다.
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

