#include"ProgramBase.h"
#include"PrintScreen.h"
#include"Unit.h"
#include"Resource.h"
#include"GameManager.h"

//����
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

FieldData field[FIELD_HEIGHT][FIELD_WIDTH];

void sleep_time(int milliseconds) {
    clock_t startTime = clock();
    while ((clock() - startTime) * 1000 / CLOCKS_PER_SEC < milliseconds) {
        //��ٸ���
    }
}

int main(void)
{
    PlaySound(TEXT("backmusic.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT); //�������
    int tick = 0;
    time_t startTime = clock();
    init_game();
    init_camp();
    
    // �뷡 �Ҹ� ���

    while (tick <= 50000)
    {
        inputManager();
        if (clock() - startTime >= TICK * 1000)
        {
            unitControl();
            printScreen(field);
            spawnQueue();
            tick++;
            startTime = clock();

            if (tick % 200 == 0)
            {
                UnitAI();
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

//���� ��ȯ �� �̵� �׽�Ʈ �ڵ�

/*
// ���� �Լ�
int main() {
    init();


    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)autoMoveUnits, NULL, 0, NULL);

    while (1) {

        if (kbhit()) {
            int key = getch();

            switch (key) {
            case '1':
                addUnit('��');
                break;
            case '2':
                addUnit('��');   
                break;
            case '3':
                addUnit('��');
                break;
            }
        }
    }

    CloseHandle(hThread);

    return 0;
}
*/

// �ڿ� �߰� �׽�Ʈ

/*
int main() {
    int resource = 0;
    print_field();
    resource_variation(&resource);

    return 0;
}
*/