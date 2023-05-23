#include <stdio.h>
#include <conio.h> // getch() 함수 사용을 위한 헤더 파일
#include <windows.h>

#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 25

typedef struct {
    int x;
    int y;
    int hp;
    int attack;
} Unit;

enum {
    black, blue,
    green, cyan, red, purple, brown, lightgray, darkgray, lightblue, lightgreen, lightcyan, lightred, lightpurple,
    yellow, white
};

int checkCollision(Unit unit1, Unit unit2) {
    if (unit1.x == unit2.x && unit1.y == unit2.y) {
        return 1;  // 충돌 발생
    }
    return 0;  // 충돌 없음
}

void setColor(int foreground, int background) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int code = foreground + background * 16;
    SetConsoleTextAttribute(consoleHandle, code);
}

void printMap(char map[CONSOLE_HEIGHT][CONSOLE_WIDTH]) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    // 커서 숨기기
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursorInfo);

    // 맵 출력
    for (int i = 0; i < CONSOLE_HEIGHT; i++) {
        COORD cursorPos = { 0, i };
        SetConsoleCursorPosition(console, cursorPos);
        printf("%s", map[i]);
    }
}

int main() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD consoleSize = { CONSOLE_WIDTH, CONSOLE_HEIGHT };
    SMALL_RECT windowSize = { 0, 0, CONSOLE_WIDTH - 1, CONSOLE_HEIGHT - 1 };
    SetConsoleScreenBufferSize(console, consoleSize);
    SetConsoleWindowInfo(console, TRUE, &windowSize);

    // 콘솔 창 속성 변경
    SetConsoleMode(console, ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    char map[CONSOLE_HEIGHT][CONSOLE_WIDTH] = {
        "############################################################",
        "#                                                          #",
        "#                                                          #",
        "#  11111111                                       11111111 #",
        "#  1      1                                       1      1 #",
        "#  1      1                                       1      1 #",
        "#  1 성채 1                                       1적성채1 #",
        "#  1      1                                       1      1 #",
        "#          ---------------------------------------         #",
        "#                                                          #",
        "############################################################"
    };

    Unit unit1 = { 10, 8, 100, 40 };
    Unit unit2 = { 60, 8, 80, 30};

    int pausetime = 0; // 경과 시간
    int collisionTime = 0; // 충돌 시간

    while (1) {
        // 맵 출력
        printMap(map);

        // 유닛1 출력
        COORD cursorPos1 = { unit1.x, unit1.y };
        SetConsoleCursorPosition(console, cursorPos1);
        printf("@");
        setColor(red, black);

        // 유닛2 출력
        
        COORD cursorPos2 = { unit2.x, unit2.y };
        SetConsoleCursorPosition(console, cursorPos2);
        printf("@");
        setColor(white, black);

        if (checkCollision(unit1, unit2)) {
            // 충돌 시간 증가
            collisionTime++;

            // 충돌 시간이 1초 이상일 때에만 공격 및 HP 감소 처리
            if (collisionTime >= 20) {
                unit2.hp -= unit1.attack;
                unit1.hp -= unit2.attack;

                // HP가 0 이하인 경우 유닛 제거 처리 등 추가 작업 수행 가능
                if (unit2.hp <= 0) {
                    // 유닛 2를 제거하는 로직
                    unit2.x = -1;
                    unit2.y = -1;
                    // 맵 배열에서 해당 위치를 공백으로 변경
                    map[unit2.y][unit2.x] = ' ';
                }

                if (unit1.hp <= 0) {
                    // 유닛 1을 제거하는 로직
                    unit1.x = -1;
                    unit1.y = -1;
                    // 맵 배열에서 해당 위치를 공백으로 변경
                    map[unit1.y][unit1.x] = ' ';
                }

                if (unit1.hp <= 0 || unit2.hp <= 0) {
                    // 유닛 충돌 후 처리 작업
                    break;
                }

                collisionTime = 0; // 충돌 시간 초기화
            }
            else {
                // 충돌 시간이 1초 미만일 때 이동 멈춤 처리
                // 이전 좌표로 되돌리기
                unit1.x--;
                unit2.x++;
            }
        }
        else {
            // 충돌이 없을 경우 충돌 시간 초기화
            collisionTime = 0;
        }

        if (_kbhit()) { // 키보드 입력 체크
            char key = _getch(); // 키 입력 받기
            switch (key) {
            case '1': {
                // 유닛 1 생성
                unit1.x = 20;
                unit1.y = 8;
                unit1.hp = 100;
                unit1.attack = 10;
                break;
            }
            case '2': {
                // 유닛 2 생성
                unit2.x = 60;
                unit2.y = 8;
                unit2.hp = 80;
                unit2.attack = 8;
                break;
            }

            }
        }

        unit1.x++;
        unit2.x--;

        Sleep(50);
        pausetime += 50;

        // 1초경과시
        if (pausetime >= 1000) {
    

            pausetime = 0; // 경과 시간 초기화
        }
    }

    // 커서 복원
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(console, &cursorInfo);

    return 0;
}