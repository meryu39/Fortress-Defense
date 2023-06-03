#include"ProgramBase.h"
#include"PrintScreen.h"
#include"Unit.h"
#include"Resource.h"

FieldData field[FIELD_HEIGHT][FIELD_WIDTH];

void sleep_time(int milliseconds) {
    clock_t startTime = clock();
    while ((clock() - startTime) * 1000 / CLOCKS_PER_SEC < milliseconds) {
        //기다리기
    }
}

int main(void)
{
    int tick = 0;
    time_t startTime = clock();
    init_unit();
    printScreen(NULL);
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            field[y][x].code = 0;
            field[y][x].shape.look = ' ';
            field[y][x].shape.color = 7;
            field[y][x].unitData = NULL;
        }
    }
    spawnUnit(1, false);
    spawnUnit(1, true);
    while (tick <= 2000)
    {
        if (clock() - startTime >= TICK * 1000)
        {
            unitControl();
            printScreen(field);
            tick++;
            startTime = clock();
            if (tick % 200 == 0)
            {
                spawnUnit(1, false);
                spawnUnit(1, true);
            }

            goto_xy(0, 21);

        }
    }

	return 0;
}



/*
for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        fgets(test, FIELD_WIDTH + 2, testFile);
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            testData[y][x].code = 1;
            testData[y][x].shape.color = 15;
            if (test[x] == '\0' || test[x] == '\n')
            {
                testData[y][x].shape.look = ' ';
                continue;
            }
            testData[y][x].shape.look = test[x];
        }
    }
*/

//유닛 소환 및 이동 테스트 코드

/*
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
*/

// 자원 추가 테스트

/*
int main() {
    int resource = 0;
    print_field();
    resource_variation(&resource);

    return 0;
}
*/