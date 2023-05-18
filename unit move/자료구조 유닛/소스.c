#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>

#define MAX_UNITS 10
#define UNIT_SPEED 1
#define AUTO_MOVE_INTERVAL 500 // 자동 이동 간격 

typedef struct Unit {
    int x;
    char symbol;
    bool isActive;
} Unit;

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

// 메인 함수
int main() {
    init(); 


    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)autoMoveUnits, NULL, 0, NULL);

    while (1) {
 
        if (kbhit()) {
            int key = getch();

            switch (key) {
            case '1':
                addUnit('ㄱ');
                break;
            case '2':
                addUnit('ㄴ');
                break;
            case '3':
                addUnit('ㄷ');
                break;
            }
        }
    }

    CloseHandle(hThread); 

    return 0;
}
