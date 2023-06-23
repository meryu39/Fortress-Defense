#pragma once
#include"ProgramBase.h"

#define DOTSIZE_X 1
#define DOTSIZE_Y 1
#define BACKGROUND_COLOR 7
#define DAMAGEPRINTQUEUE_MAXINDEX 15
#define DAMAGE_PRINT_TICK 20

//COORD는 window.h 헤더파일에서 x, y좌표를 담고있는 구조체
//구성멤버 : short X / short Y
typedef COORD Position;
//색 코드를 문자화시킨 것
enum color { BLACK = 0, BLUE, GREEN, BLUE_GREEN, RED, PURPLE, YELLOW, WHITE, GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_BULE_GREEN, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLO, LIGHT_WHITE};

//0 : 검은색 / 1 : 파란색 / 2 : 녹색 / 3 : 청록색 / 4 : 빨간색 / 5 : 자주색 / 6 : 노란색 / 7 : 흰색 / 8~ : 0~7의 옅은색 
void setColor(unsigned short color);
//출력 시작 부분을 x, y부분으로 옮김, 좌측상단이 (0, 0)이다. 행렬을 생각하면 편하다.
void goto_xy(SHORT x, SHORT y);
//Position를 인자로 전달하는 형태의 goto_xy함수 오버로딩
void goto_xy(Position pos);
//화면 출력 함수, 이번 프레임과 이전 프레임의 필드 상태를 비교해서 필요한 곳만 출력한다.
void printScreen(FieldData (*inputData)[FIELD_WIDTH]);
//상시로 출력하는 UI를 출력
void printUI();
//
void printDamage(Position pos = {-1, -1}, int damage = -1, int color = BACKGROUND_COLOR);

void init_UI();
