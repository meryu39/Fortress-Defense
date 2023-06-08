#pragma once
#include"ProgramBase.h"
#include"PrintScreen.h"

#define INCREASE_RESOURCE 5 //�����ð��� �ڿ� ������
#define ENEMY_UNIT_A_COST 10 //������ ���
#define ENEMY_UNIT_KILL_REWARD 0.8 //������ óġ ���� ���� - ��� �ɼ���?
#define UNIT_A_COST 10//���� A�� ���


typedef struct stage {
    int step;
    char name[20];
    struct stage* next;
} Stage;
void print_resource(int resource);
void print_field();
void resource_variation(int* resource);

