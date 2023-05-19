#pragma once
#include"ProgramBase.h"

#define MAX_UNITS 10
#define UNIT_SPEED 1
#define AUTO_MOVE_INTERVAL 500 // �ڵ� �̵� ���� 

typedef struct Unit {
    int x;
    char symbol;
    bool isActive;
} Unit;



void addUnit(char symbol);
void init();
void draw();
void moveUnits();
void autoMoveUnits();
