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
        printf("■");
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
        // 필드 출력
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

        // 현재 자원 레벨 및 자원 바 출력
        goto_xy(1, FIELD_HEIGHT + 1);
        printf("자원: %d / %d", resource, maxResource);
        print_resource_bar(resource);

        // 자원 레벨 증가
        resource += INCREASE_RESOURCE;

        // 유닛 소환을 위한 사용자 입력 프롬프트
        char unit = '\0';
        printf("\n\n유닛을 선택하세요 [A/B/C] 또는 Q를 눌러 종료:");
        if(kbhit())	unit = getch();

        // 유닛 소환을 위한 자원 차감
        if (unit == 'a' || unit == 'A') {
            if (resource >= UNIT_COST) {
                printf("\nA 유닛을 소환합니다...");
                resource -= UNIT_COST;
            }
            else {
                printf("\n자원이 부족합니다!");
                Sleep(1000);
            }
        }
        else if (unit == 'b' || unit == 'B') {
            if (resource >= UNIT_COST) {
                printf("\nB 유닛을 소환합니다...");
                resource -= UNIT_COST;
            }
            else {
                printf("\n자원이 부족합니다!");
                Sleep(1000);
            }
        }
        else if (unit == 'c' || unit == 'C') {
            if (resource >= UNIT_COST) {
                printf("\nC 유닛을 소환합니다...");
                resource -= UNIT_COST;
            }
            else {
                printf("\n자원이 부족합니다!");
                Sleep(1000);
            }
        }
        else if (unit == 'q' || unit == 'Q') {
            break;
        }
        Sleep(50);
	}
    
    return 0;
}
