#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define INCREASE_RESOURCE 5 //�����ð��� �ڿ� ������
#define ENEMY_UNIT_A_COST 10 //������ ���
#define ENEMY_UNIT_KILL_REWARD 0.8 //������ óġ ���� ���� - ��� �ɼ���?
#define UNIT_A_COST 10//���� A�� ���
#define FIELD_WIDTH 32//����ũ��
#define FIELD_HEIGHT 20//����ũ��

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
    printf("�ڿ� : %d", resource);
}

void print_field() {
    for (int i = 1; i < FIELD_WIDTH; i++) {
        gotoxy(i, 0);
        printf("��");
        gotoxy(i, FIELD_HEIGHT - 1);
        printf("��");
    }

    for (int i = 1; i < FIELD_HEIGHT; i++) {
        gotoxy(0, i);
        printf("��");
        gotoxy((FIELD_WIDTH - 1), i);
        printf("��");
    }

    gotoxy(0, 0);
    printf("��");
    gotoxy(0, FIELD_HEIGHT - 1);
    printf("��");
    gotoxy(FIELD_WIDTH - 1, 0);
    printf("��");
    gotoxy(FIELD_WIDTH - 1, FIELD_HEIGHT - 1);
    printf("��");
}

void resource_variation(int* resource) {
    while (1) {
        (*resource) += INCREASE_RESOURCE; // ���� �ð��� �ڿ� ������ ��ŭ �ʴ� �ڿ� ����

        if (*resource > INCREASE_RESOURCE * 200) { // �ڿ��� �ʹ� �������� �ڿ� ���� ����
            Sleep(1000);
            while (*resource > INCREASE_RESOURCE * 200) {
                Sleep(1000);
            }
        }

        print_resource(*resource);

        // ���� A�� óġ�ϴ� �̺�Ʈ�� �߻��� ������ �ڿ� ����
        if (/*  ���� A�� óġ */) {
            (*resource) += (int)(ENEMY_UNIT_A_COST * ENEMY_UNIT_KILL_REWARD);
            print_resource(*resource);
        }

        // ��ȯ�Ϸ��� ���� ����� ���� ���� �ڿ����� ���� ��� ��� ���
        if (UNIT_A_COST > *resource) {
            gotoxy(FIELD_WIDTH + 3, -2);
            printf("�ڿ��� �����մϴ�!");
        }
        else {
            (*resource) -= UNIT_A_COST; // ��ȯ�Ϸ��� ���� ��븸ŭ �ڿ� ����
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
