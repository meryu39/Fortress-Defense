#pragma once
#include"ProgramBase.h"

#define DOTSIZE_X 2
#define DOTSIZE_Y 1

//COORD�� window.h ������Ͽ��� x, y��ǥ�� ����ִ� ����ü
//������� : short X / short Y
typedef COORD Position;

//0 : ������ / 1 : �Ķ��� / 2 : ��� / 3 : û�ϻ� / 4 : ������ / 5 : ���ֻ� / 6 : ����� / 7 : ��� / 8~ : 0~7�� ������ 
void setColor(unsigned short color);
//��� ���� �κ��� x, y�κ����� �ű�, ��������� (0, 0)�̴�. ����� �����ϸ� ���ϴ�.
void goto_xy(short x, short y);
//Position�� ���ڷ� �����ϴ� ������ goto_xy�Լ� �����ε�
void goto_xy(Position pos);
//ȭ�� ��� �Լ�, �̹� �����Ӱ� ���� �������� �ʵ� ���¸� ���ؼ� �ʿ��� ���� ����Ѵ�.
void printScreen(FieldData (*inputData)[WIDTHSIZE]);

