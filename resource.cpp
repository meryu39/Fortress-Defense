#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define INCREASE_RESOURCE 5 //단위시간당 자원 증가량
#define ENEMY_UNIT_A_COST 10 //적유닛 비용
#define ENEMY_UNIT_KILL_REWARD 0.8 //적유닛 처치 보상 비율 - 없어도 될수도?
#define UNIT_A_COST 10//유닛 A의 비용
#define FIELD_WIDTH 32//가로크기
#define FIELD_HEIGHT 20//세로크기

typedef struct stage {
    int step;
    char name[20];
    struct stage* next;
} Stage;

void gotoxy(int x, int y) {
    COORD pos = { x , y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void print_resource(int resource) {
    gotoxy(FIELD_WIDTH + 3, -3);
    printf("자원 : %d", resource);
}

void print_field() {
    for (int i = 1; i < FIELD_WIDTH; i++) {
        gotoxy(i, 0);
        printf("━");
        gotoxy(i, FIELD_HEIGHT - 1);
        printf("━");
    }

    for (int i = 1; i < FIELD_HEIGHT; i++) {
        gotoxy(0, i);
        printf("┃");
        gotoxy((FIELD_WIDTH - 1), i);
        printf("┃");
    }

    gotoxy(0, 0);
    printf("┏");
    gotoxy(0, FIELD_HEIGHT - 1);
    printf("┗");
    gotoxy(FIELD_WIDTH - 1, 0);
    printf("┓");
    gotoxy(FIELD_WIDTH - 1, FIELD_HEIGHT - 1);
    printf("┛");
}

void resource_variation(int* resource) {
    while (1) {
        (*resource) += INCREASE_RESOURCE; // 단위 시간당 자원 증가량 만큼 초당 자원 증가

        if (*resource > INCREASE_RESOURCE * 200) { // 자원이 너무 많아지면 자원 증가 멈춤
            Sleep(1000);
            while (*resource > INCREASE_RESOURCE * 200) {
                Sleep(1000);
            }
        }

        print_resource(*resource);

        // 유닛 A를 처치하는 이벤트가 발생할 때마다 자원 증가
        if (/*  유닛 A가 처치 */) {
            (*resource) += (int)(ENEMY_UNIT_A_COST * ENEMY_UNIT_KILL_REWARD);
            print_resource(*resource);
        }

        // 소환하려는 유닛 비용이 내가 가진 자원보다 많은 경우 경고문 출력
        if (UNIT_A_COST > *resource) {
            gotoxy(FIELD_WIDTH + 3, -2);
            printf("자원이 부족합니다!");
        }
        else {
            (*resource) -= UNIT_A_COST; // 소환하려는 유닛 비용만큼 자원 감소
            print_resource(*resource);
        }

        Sleep(1000);
    }
}


int main() {
    int resource = 0;
    print_field();
    resource_variation(&resource);

    return 0;
}
