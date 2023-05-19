#include"Unit.h"

Unit units[MAX_UNITS];
int unitCount = 0;

void addUnit(char symbol) {
    if (unitCount < MAX_UNITS) {
        units[unitCount].x = 0;
        units[unitCount].symbol = symbol;
        units[unitCount].isActive = true;
        unitCount++;
    }
}


void init() {
    unitCount = 0;
}


void draw() {
    system("cls");  // 화면 지우기

    for (int i = 0; i < unitCount; i++) {
        // 유닛 출력
        for (int j = 0; j < units[i].x; j++) {
            printf(" ");
        }
        printf("%c\n", units[i].symbol);
    }
}


void moveUnits() {
    for (int i = 0; i < unitCount; i++) {
        if (units[i].isActive) {
            units[i].x += UNIT_SPEED;
        }
    }
}


void autoMoveUnits() {
    while (1) {
        moveUnits();
        draw();
        Sleep(AUTO_MOVE_INTERVAL);
    }
}