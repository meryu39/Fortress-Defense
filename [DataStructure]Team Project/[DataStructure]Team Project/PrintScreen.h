#pragma once
#include"ProgramBase.h"

#define DOTSIZE_X 1
#define DOTSIZE_Y 1
#define BACKGROUND_COLOR 7
#define DAMAGEPRINTQUEUE_MAXINDEX 15
#define DAMAGE_PRINT_TICK 20

//COORD�� window.h ������Ͽ��� x, y��ǥ�� ����ִ� ����ü
//������� : short X / short Y
typedef COORD Position;
//�� �ڵ带 ����ȭ��Ų ��
enum color { BLACK = 0, BLUE, GREEN, BLUE_GREEN, RED, PURPLE, YELLOW, WHITE, GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_BULE_GREEN, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLO, LIGHT_WHITE};

//0 : ������ / 1 : �Ķ��� / 2 : ��� / 3 : û�ϻ� / 4 : ������ / 5 : ���ֻ� / 6 : ����� / 7 : ��� / 8~ : 0~7�� ������ 
void setColor(unsigned short color);
//��� ���� �κ��� x, y�κ����� �ű�, ��������� (0, 0)�̴�. ����� �����ϸ� ���ϴ�.
void goto_xy(SHORT x, SHORT y);
//Position�� ���ڷ� �����ϴ� ������ goto_xy�Լ� �����ε�
void goto_xy(Position pos);
//ȭ�� ��� �Լ�, �̹� �����Ӱ� ���� �������� �ʵ� ���¸� ���ؼ� �ʿ��� ���� ����Ѵ�.
void printScreen(FieldData (*inputData)[FIELD_WIDTH]);
//��÷� ����ϴ� UI�� ���
void printUI();
//
void printDamage(Position pos = {-1, -1}, int damage = -1, int color = BACKGROUND_COLOR);
