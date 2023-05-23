#include"ProgramBase.h"
#include"PrintScreen.h"
#include"Unit.h"
#include"Resource.h"


void sleep_time(int milliseconds) {
    clock_t startTime = clock();
    while ((clock() - startTime) * 1000 / CLOCKS_PER_SEC < milliseconds) {
        //��ٸ���
    }
}

void my_unit(FieldData testData[FIELD_HEIGHT][FIELD_WIDTH], int testX)
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
            testData[y][x].shape.look = 'M';
            testData[y][x].shape.color = 7;
        }
    }
}

void enemy_unit(FieldData testData[FIELD_HEIGHT][FIELD_WIDTH], int testX)
{
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            testData[y][x].code = 0;
            // ���ݴ��� x ��ǥ������ ���� ����
            if (x == FIELD_WIDTH - testX && y == FIELD_HEIGHT - 1)
            {
                testData[y][x].code = 1;

            }
            testData[y][x].shape.look = 'E';
            testData[y][x].shape.color = 7;

        }
    }
}

int main(void)
{
	FieldData testData[FIELD_HEIGHT][FIELD_WIDTH];
    char test[FIELD_WIDTH + 2];
	int temp = 0;
    bool sign = FALSE;
    int testX1 = 5; // �Ʊ� ������ testX ��
    int testX2 = 5; // �� ������ testX ��
    int inputKey = 0;  // �Էµ� Ű�� ������ ����



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
        if (kbhit()) {
            inputKey = getch();
        }

        if (inputKey == 'q') {
            my_unit(testData, testX1); // �Ʊ� ���� ����
            testX1 += 1; // �Ʊ� ���� x��ǥ ����
        }
        else if (inputKey == 'w') {
            enemy_unit(testData, testX2); // �� ���� ����
            testX2 += 1; // �� ���� x��ǥ ����
        }


        goto_xy(FIELD_WIDTH, FIELD_HEIGHT);
        sleep_time(50);
        printScreen(testData);
        if (testX1 > FIELD_WIDTH && testX2 > FIELD_WIDTH) break;
        
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