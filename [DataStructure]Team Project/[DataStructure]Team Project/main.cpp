#include"ProgramBase.h"
#include"PrintScreen.h"
#include"Unit.h"
#include"Resource.h"


void sleep_time(int milliseconds) {
    clock_t startTime = clock();
    while ((clock() - startTime) * 1000 / CLOCKS_PER_SEC < milliseconds) {
        //기다리기
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
            // 정반대편 x 좌표에서도 유닛 생성
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
    int testX1 = 5; // 아군 유닛의 testX 값
    int testX2 = 5; // 적 유닛의 testX 값
    int inputKey = 0;  // 입력된 키를 저장할 변수



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
            my_unit(testData, testX1); // 아군 유닛 생성
            testX1 += 1; // 아군 유닛 x좌표 증가
        }
        else if (inputKey == 'w') {
            enemy_unit(testData, testX2); // 적 유닛 생성
            testX2 += 1; // 적 유닛 x좌표 증가
        }


        goto_xy(FIELD_WIDTH, FIELD_HEIGHT);
        sleep_time(50);
        printScreen(testData);
        if (testX1 > FIELD_WIDTH && testX2 > FIELD_WIDTH) break;
        
    }
    
	

	return 0;
}

/*
//AI 알고리즘
Tick =1  아군 유닛생성시 선언
Tick =2  아군 유닛 위치 추적
int Tick         //  AI 실행하는 틱 변수, 아군 유닛생성시 틱을 1로 선언시켜 AI알고리즘을 실행시킴
int count_enemy_unit   //  필드에 있는 적 유닛 수


while(Tick !=0){
    swtich(Tick){
         //Tick == 1일때 기본 생성
        case 1:
            if(count_enemy_unit <= 3):   //    필드에 적 유닛이 3개 이하일 때,
                random(1,2레벨 유닛한정) 적 유닛소환 
            if(level_my_unit > 4):
                i = level_my.unit   //필드에 존재하는 아군유닛 최고 티어레벨을 받는다.
                i-2 레벨 적 유닛 생성
                
                TIck = 0
                break;


            

          //TIck == 2일 경우 좌표 관련 생성
          case 2:

            if(my.unit.x > 70) //70퍼이상 넘어왔을때
              i = level_my.unit   //필드에 존재하는 아군유닛 최고 티어레벨을 받는다.
              int reandom = radn() % 2 + 1 //1~2중에 랜덤선택
              if(i >2)
                enemy.unit(i-random) //i기준 -1 ~ -2 티어레벨 적 유닛을 소환함
              else
                enemy.unit(1) || enemy.unit(2) // 1~2레벨 랜덤 적 유닛 하나 생성
              Tick = 0
              break;
            else if(my.unit.x > 50) //50퍼이상 넘어왔을 때
              1~2레벨 한정 유닛 랜덤 소환 (1마리)
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