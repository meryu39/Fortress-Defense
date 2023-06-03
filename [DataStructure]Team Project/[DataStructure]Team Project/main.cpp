#include"ProgramBase.h"
#include"PrintScreen.h"
#include"Unit.h"
#include"Resource.h"

FieldData field[FIELD_HEIGHT][FIELD_WIDTH];

void sleep_time(int milliseconds) {
    clock_t startTime = clock();
    while ((clock() - startTime) * 1000 / CLOCKS_PER_SEC < milliseconds) {
        //��ٸ���
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
//AI �˰���
Tick =1  �Ʊ� ���ֻ����� ����
Tick =2  �Ʊ� ���� ��ġ ����
int Tick         //  AI �����ϴ� ƽ ����, �Ʊ� ���ֻ����� ƽ�� 1�� ������� AI�˰����� �����Ŵ
int count_enemy_unit   //  �ʵ忡 �ִ� �� ���� ��


while(Tick !=0){
    swtich(Tick){
         //Tick == 1�϶� �⺻ ����
        case 1:
            if(count_enemy_unit <= 3):   //    �ʵ忡 �� ������ 3�� ������ ��,
                random(1,2���� ��������) �� ���ּ�ȯ 
            if(level_my_unit > 4):
                i = level_my.unit   //�ʵ忡 �����ϴ� �Ʊ����� �ְ� Ƽ����� �޴´�.
                i-2 ���� �� ���� ����
                
                TIck = 0
                break;


            

          //TIck == 2�� ��� ��ǥ ���� ����
          case 2:

            if(my.unit.x > 70) //70���̻� �Ѿ������
              i = level_my.unit   //�ʵ忡 �����ϴ� �Ʊ����� �ְ� Ƽ����� �޴´�.
              int reandom = radn() % 2 + 1 //1~2�߿� ��������
              if(i >2)
                enemy.unit(i-random) //i���� -1 ~ -2 Ƽ��� �� ������ ��ȯ��
              else
                enemy.unit(1) || enemy.unit(2) // 1~2���� ���� �� ���� �ϳ� ����
              Tick = 0
              break;
            else if(my.unit.x > 50) //50���̻� �Ѿ���� ��
              1~2���� ���� ���� ���� ��ȯ (1����)
              Tick = 0
              break;
        
        

*/

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