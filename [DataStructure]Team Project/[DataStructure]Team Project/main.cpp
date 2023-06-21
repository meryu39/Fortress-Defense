#include"ProgramBase.h"
#include"PrintScreen.h"
#include"Unit.h"
#include"Resource.h"
#include"GameManager.h"

//음악
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

FieldData field[FIELD_HEIGHT][FIELD_WIDTH];

int currentStage = 0;

int main(void)
{
    PlaySound(TEXT("backmusic.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT); //음악출력
    int tick = 0;
    time_t startTime = clock();
    init_game();
    
    // 노래 소리 출력

    while (1)
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
