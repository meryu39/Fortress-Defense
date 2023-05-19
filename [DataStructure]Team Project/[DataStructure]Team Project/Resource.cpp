#include"Resource.h"

void print_resource(int resource) {
    goto_xy(FIELD_WIDTH + 3, 3);
    printf("�ڿ� : %3d", resource);
}

void print_field() {
    for (int i = 1; i < FIELD_WIDTH; i++) {
        goto_xy(i, 0);
        printf("��");
        goto_xy(i, FIELD_HEIGHT - 1);
        printf("��");
    }

    for (int i = 1; i < FIELD_HEIGHT; i++) {
        goto_xy(0, i);
        printf("��");
        goto_xy((FIELD_WIDTH - 1), i);
        printf("��");
    }

    goto_xy(0, 0);
    printf("��");
    goto_xy(0, FIELD_HEIGHT - 1);
    printf("��");
    goto_xy(FIELD_WIDTH - 1, 0);
    printf("��");
    goto_xy(FIELD_WIDTH - 1, FIELD_HEIGHT - 1);
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
        if (/*  ���� A�� óġ */TRUE) {
            (*resource) += (int)(ENEMY_UNIT_A_COST * ENEMY_UNIT_KILL_REWARD);
            print_resource(*resource);
        }

        // ��ȯ�Ϸ��� ���� ����� ���� ���� �ڿ����� ���� ��� ��� ���
        if (UNIT_A_COST > *resource) {
            goto_xy(FIELD_WIDTH + 3, 2);
            printf("�ڿ��� �����մϴ�!");
        }
        else {
            (*resource) -= UNIT_A_COST; // ��ȯ�Ϸ��� ���� ��븸ŭ �ڿ� ����
            print_resource(*resource);
        }

        Sleep(1000);
    }
}