#include"ProgramBase.h"
#include"PrintScreen.h"
#include"Unit.h"
#include"Resource.h"


int main(void)
{
	FieldData testData[FIELD_HEIGHT][FIELD_WIDTH];
    char test[FIELD_WIDTH + 2];
	int temp = 0;
    bool sign = FALSE;
    int testX = 5;

    printScreen(NULL);
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            testData[y][x].code = 0;
            testData[y][x].shape.look = 'A';
            testData[y][x].shape.color = 7;
        }
    }
    while (temp != -1)
    {
        for (int y = 0; y < FIELD_HEIGHT; y++)
        {
            for (int x = 0; x < FIELD_WIDTH; x++)
            {
                testData[y][x].code = 0;
                if (x == testX && y == FIELD_HEIGHT - 1)
                {
                    testData[y][x].code = 1;
                }
                testData[y][x].shape.look = 'A';
                testData[y][x].shape.color = 7;
            }
            
        }
        testX += 1;
        goto_xy(FIELD_WIDTH, FIELD_HEIGHT);
        _sleep(100);
        printScreen(testData);
        if (testX > FIELD_WIDTH)  break;
        
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