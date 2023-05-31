#pragma once
#include"ProgramBase.h"
#include"PrintScreen.h"

#define MAX_UNITS 5
#define UNIT_SPEED 1
#define SPAWNPOINT_TEAM_X 3
#define SPAWNPOINT_TEAM_Y FIELD_HEIGHT - 1
#define SPAWNPOINT_ENEMY_X FIELD_WIDTH - 9
#define SPAWNPOINT_ENEMY_Y FIELD_HEIGHT - 1

// 병사에 대한 상수값
#define SOLDIER_SPAWNTIME 60
#define SOLDIER_MAXHP 100
#define SOLDIER_RANGE 1
#define SOLDIER_DAMAGE 30
#define SOLDIER_PRICE 35
#define SOLDIER_KILLBONUS 35
#define SOLDIER_DELAYMOVE 15
#define SOLDIER_DELAYATTACK 15
// 궁병에 대한 상수값

// 창병에 대한 상수값

// 투창병에 대한 상수값

// 기마병에 대한 상수값

// 투석기에 대한 상수값

// 성기사에 대한 상수값

// 장군에 대한 상수값


void spawnUnit(int unitCode, bool enemy);
void unitControl();
void attackUnit(Unit* attacker, Unit* attackedUnit);
