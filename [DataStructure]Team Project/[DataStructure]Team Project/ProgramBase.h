#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<iostream>
#include<stdbool.h>
#include<windows.h>
#pragma warning(disable:4996)

#define FIELD_WIDTH 100		//����ũ��
#define FIELD_HEIGHT 10		//����ũ��
#define TICK 0.02			//ƽ(������) �� ���� �ð�

//������ �׷��� ������ ��� �ִ� ����ü
typedef struct
{
	unsigned short color;
	char look;
}SHAPE;

typedef struct
{
	int x;							// ������ x��ǥ
	int y;
	int hp;							// ������ ���� ü��
	int range;						// ������ ��Ÿ�
	int damage;						// ������ ������
	int price;						// ������ ���� ����
	bool enemy;						// �Ʊ��� ���� �����ϴ� ����, TRUE�̸� ��
	int kill_bonus;					// ������ ��뿡�� �ִ� ų���ʽ�
	int cooltime_move;				// �̵����� ���� tick
	int cooltime_attack;			// ���ݱ��� ���� tick
	int delay_move;					// �̵��ӵ�(�̵��� �ʿ��� tick)
	int delay_attack;				// ���ݼӵ�(���ݿ� �ʿ��� tick)
	int unit_code;
}Unit;

//���� �ʵ��� ������ ��� �ִ� ����ü
typedef struct
{
	int code;
	SHAPE shape;
	Unit* unitData;
}FieldData;




