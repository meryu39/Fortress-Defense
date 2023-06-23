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
bool exitgame = false;
void mainscreen();
void mainex();


int main(void)
{
    

    while (!exitgame)
    {
        mainscreen();
        int menuChoice = _getch();
        switch (menuChoice)
        {
        case '1':
            exitgame = true;
            system("cls");
            break;

        case '2':
            mainex();
            break;

        case '3':
            exit(0);
            break;


        }
    }

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


void mainscreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD originalAttributes = consoleInfo.wAttributes;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    printf("######  #####  ######   ####### ######  #####  #####\n");
    printf("#      #     # #     #     #    #      #      # \n");
    printf("#      #     # #     #     #    #      #      # \n");
    printf("#####  #     # ######      #    #####   ####   ####\n");
    printf("#      #     # #   #       #    #           #      #\n");
    printf("#      #     # #    #      #    #           #      #\n");
    printf("#       #####  #     #     #    ###### #####  #####\n\n\n");

    printf("#######  ###### ###### ###### #       #  #####  ##### \n");
    printf(" #     # #      #      #      # #     # #      # \n");
    printf(" #     # #      #      #      #  #    # #      # \n");
    printf(" #     # #####  ###### #####  #   #   #  ####   ####\n");
    printf(" #     # #      #      #      #    #  #      #      #\n");
    printf(" #     # #      #      #      #     # #      #      #\n");
    printf("#######  ###### #      ###### #       # #####  #####\n\n\n");

    SetConsoleTextAttribute(hConsole, originalAttributes);
    printf("Team : 복학했죠\n\n\n\n");

    printf("1. 게임 시작\n");
    printf("2. 게임 설명\n");
    printf("3. 게임 종료\n\n");
    printf("메뉴를 선택하세요: ");
}

void mainex()
{
    system("cls");
    printf("기획 의도\n");
    printf("==================================================================\n");
    printf("1. 생성해야 하는 유닛의 대기열을 큐를 활용하여 구현\n");
    printf("2. 이중연결리스트를 활용하여 유닛의 소환과 삭제 구현\n");
    printf("3. 스테이지 연결리스트로 구현하여 다음스테이지로 유기적으로 이어질 수 있도록 구현\n");
    printf("==================================================================\n\n\n");
    printf("게임 설명\n");
    printf("====================================================================\n");
    printf("장르 : 횡스크롤 기반 전략 디펜스 게임\n");
    printf("주제 : 가상의 전쟁 시나리오에서 지휘관의 입장에서 플레이하는 플레이어\n");
    printf("플레이 요소 : 상황에 맞는 자원관리 및 유닛 소환\n");
    printf("플레이 방식 : 숫자를 입력해 상황에 맞는 유닛 소환\n");
    printf("====================================================================\n\n\n");
    printf("게임 규칙\n");
    printf("=========================================================\n");
    printf("목표 : 적 성채의 HP를 0으로 만드는 것\n");
    printf("유닛을 소환하면 적 성채 방향으로 적 유닛과 싸우면서 돌격\n");
    printf("성채에 도착하면 도착한 유닛의 공격력만큼 성채 HP가 감소\n\n");
    printf("스테이지 별 기본 재화인 골드 지급\n");
    printf("초당 10골드씩 획득\n");
    printf("적유닛을 제거시 그 유닛의 생성 비용의 40%를 획득\n");
    printf("=========================================================\n\n\n");
    printf("메인화면으로 돌아가려면 1번을 눌러주세요");

    int input;
    do {
        input = _getch();
    } while (input != '1');
    system("cls");
}
