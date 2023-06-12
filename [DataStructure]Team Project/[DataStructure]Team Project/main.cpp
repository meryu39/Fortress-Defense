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


int main(void)
{
    PlaySound(TEXT("backmusic.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT); //�������
    int tick = 0;
    time_t startTime = clock();
    init_game();
    
    // �뷡 �Ҹ� ���

    while (tick <= 50000)
    {
        inputManager();
        if (clock() - startTime >= TICK * 1000)
        {
            unitControl();
            printScreen(field);
            printUI();
            spawnQueue();
            
            tick++;
            startTime = clock();

            if (tick % 10 == 0)
            {
                resourceManager();
            }

            if (tick % 200 == 0)
            {
                UnitAI();
            }
            goto_xy(0, 21);
        }
    }

	return 0;
}
