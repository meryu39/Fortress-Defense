#include"ProgramBase.h"
#include"PrintScreen.h"
#include"Unit.h"
#include"Resource.h"


int main(void)
{
	FieldData testData[FIELD_HEIGHT][FIELD_WIDTH];
	int temp = 0;
	for (int y = 0; y < FIELD_HEIGHT; y++)
	{
		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			testData[y][x].code = 0;
			testData[y][x].shape.look = 'E';
			testData[y][x].shape.color = 1;
		}
	}
	printScreen(testData);
	scanf("%d", &temp);
	for (int y = 0; y < FIELD_HEIGHT; y+=2)
	{
		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			testData[y][x].code = 1;
			testData[y][x].shape.look = 'N';
			testData[y][x].shape.color = 6;
		}
	}
	printScreen(testData);
	scanf("%d", &temp);
	for (int y = 0; y < FIELD_HEIGHT; y += 1)
	{
		for (int x = 0; x < FIELD_WIDTH; x+=3)
		{
			testData[y][x].code = 2;
			testData[y][x].shape.look = 'A';
			testData[y][x].shape.color = 4;
		}
	}
	printScreen(testData);
	scanf("%d", &temp);
	for (int y = 0; y < FIELD_HEIGHT; y += 2)
	{
		for (int x = 0; x < FIELD_WIDTH; x += 2)
		{
			testData[y][x].code = 3;
			testData[y][x].shape.look = 'O';
			testData[y][x].shape.color = 2;
		}
	}
	printScreen(testData);
	scanf("%d", &temp);

	return 0;
}



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