#pragma once
#include"ProgramBase.h"
#include"PrintScreen.h"

#define INCREASE_RESOURCE 5 //단위시간당 자원 증가량
#define ENEMY_UNIT_A_COST 10 //적유닛 비용
#define ENEMY_UNIT_KILL_REWARD 0.8 //적유닛 처치 보상 비율 - 없어도 될수도?
#define UNIT_A_COST 10//유닛 A의 비용


typedef struct stage {
    int step;
    char name[20];
    struct stage* next;
} Stage;
void print_resource(int resource);
void print_field();
void resource_variation(int* resource);

