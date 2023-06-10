#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define FIELD_WIDTH 40
#define FIELD_HEIGHT 20
#define INCREASE_RESOURCE 5
#define UNIT_COST 20

void goto_xy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void print_resource_bar(int resource) {
    int barLength = (int)(((double)resource / (INCREASE_RESOURCE * 200)) * (FIELD_WIDTH - 2));
    goto_xy(1, FIELD_HEIGHT);
    printf("[");
    for (int i = 0; i < barLength; i++) {
        printf("��");
    }
    for (int i = barLength; i < (int)(((double)INCREASE_RESOURCE * 200) / (INCREASE_RESOURCE * 200)) * (FIELD_WIDTH - 2); i++) {
        printf(" ");
    }
    printf("]");
}

int main() {
    int resource = 0;
    int maxResource = INCREASE_RESOURCE * 200;

    while (1) {
        // �ʵ� ���
        system("cls");
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            for (int x = 0; x < FIELD_WIDTH; x++) {
                if (x == 0 || x == FIELD_WIDTH - 1 || y == FIELD_HEIGHT - 1) {
                    printf("#");
                }
                else {
                    printf(" ");
                }
            }
            printf("\n");
        }

        // ���� �ڿ� ���� �� �ڿ� �� ���
        goto_xy(1, FIELD_HEIGHT + 1);
        printf("�ڿ�: %d / %d", resource, maxResource);
        print_resource_bar(resource);

        // �ڿ� ���� ����
        resource += INCREASE_RESOURCE;

        // ���� ��ȯ�� ���� ����� �Է� ������Ʈ
        char unit;
        printf("\n\n������ �����ϼ��� [A/B/C] �Ǵ� Q�� ���� ����:");
        unit = getch();

        // ���� ��ȯ�� ���� �ڿ� ����
        if (unit == 'a' || unit == 'A') {
            if (resource >= UNIT_COST) {
                printf("\nA ������ ��ȯ�մϴ�...");
                resource -= UNIT_COST;
            }
            else {
                printf("\n�ڿ��� �����մϴ�!");
                Sleep(1000);
            }
        }
        else if (unit == 'b' || unit == 'B') {
            if (resource >= UNIT_COST) {
                printf("\nB ������ ��ȯ�մϴ�...");
                resource -= UNIT_COST;
            }
            else {
                printf("\n�ڿ��� �����մϴ�!");
                Sleep(1000);
            }
        }
        else if (unit == 'c' || unit == 'C') {
            if (resource >= UNIT_COST) {
                printf("\nC ������ ��ȯ�մϴ�...");
                resource -= UNIT_COST;
            }
            else {
                printf("\n�ڿ��� �����մϴ�!");
                Sleep(1000);
            }
        }
        else if (unit == 'q' || unit == 'Q') {
            break;
        }
    }
    
    return 0;
}