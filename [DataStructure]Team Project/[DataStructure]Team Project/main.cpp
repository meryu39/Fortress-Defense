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

    PlaySound(TEXT("backmusic.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT); //�������
    int tick = 0;
    time_t startTime = clock();
    init_game();
    
    // �뷡 �Ҹ� ���
    
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
    printf("Team : ��������\n\n\n\n");

    printf("1. ���� ����\n");
    printf("2. ���� ����\n");
    printf("3. ���� ����\n\n");
    printf("�޴��� �����ϼ���: ");
}

void mainex()
{
    system("cls");
    printf("��ȹ �ǵ�\n");
    printf("==================================================================\n");
    printf("1. �����ؾ� �ϴ� ������ ��⿭�� ť�� Ȱ���Ͽ� ����\n");
    printf("2. ���߿��Ḯ��Ʈ�� Ȱ���Ͽ� ������ ��ȯ�� ���� ����\n");
    printf("3. �������� ���Ḯ��Ʈ�� �����Ͽ� �������������� ���������� �̾��� �� �ֵ��� ����\n");
    printf("==================================================================\n\n\n");
    printf("���� ����\n");
    printf("====================================================================\n");
    printf("�帣 : Ⱦ��ũ�� ��� ���� ���潺 ����\n");
    printf("���� : ������ ���� �ó��������� ���ְ��� ���忡�� �÷����ϴ� �÷��̾�\n");
    printf("�÷��� ��� : ��Ȳ�� �´� �ڿ����� �� ���� ��ȯ\n");
    printf("�÷��� ��� : ���ڸ� �Է��� ��Ȳ�� �´� ���� ��ȯ\n");
    printf("====================================================================\n\n\n");
    printf("���� ��Ģ\n");
    printf("=========================================================\n");
    printf("��ǥ : �� ��ä�� HP�� 0���� ����� ��\n");
    printf("������ ��ȯ�ϸ� �� ��ä �������� �� ���ְ� �ο�鼭 ����\n");
    printf("��ä�� �����ϸ� ������ ������ ���ݷ¸�ŭ ��ä HP�� ����\n\n");
    printf("�������� �� �⺻ ��ȭ�� ��� ����\n");
    printf("�ʴ� 10��徿 ȹ��\n");
    printf("�������� ���Ž� �� ������ ���� ����� 40%�� ȹ��\n");
    printf("=========================================================\n\n\n");
    printf("����ȭ������ ���ư����� 1���� �����ּ���");

    int input;
    do {
        input = _getch();
    } while (input != '1');
    system("cls");
}
