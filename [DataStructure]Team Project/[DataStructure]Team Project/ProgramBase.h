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

#define FIELD_WIDTH 100		//가로크기
#define FIELD_HEIGHT 10		//세로크기
#define TICK 0.02			//틱(프레임) 한 번당 시간

//유닛의 그래픽 정보를 담고 있는 구조체
typedef struct
{
	unsigned short color;
	char look;
}SHAPE;

typedef struct
{
	int x;							// 유닛의 x좌표
	int y;
	int hp;							// 유닛의 남은 체력
	int range;						// 유닛의 사거리
	int damage;						// 유닛의 데미지
	int price;						// 유닛의 생산 가격
	bool enemy;						// 아군과 적을 구분하는 변수, TRUE이면 적
	int kill_bonus;					// 죽으면 상대에게 주는 킬보너스
	int cooltime_move;				// 이동까지 남은 tick
	int cooltime_attack;			// 공격까지 남은 tick
	int delay_move;					// 이동속도(이동에 필요한 tick)
	int delay_attack;				// 공격속도(공격에 필요한 tick)
	int unit_code;
}Unit;

//게임 필드의 정보를 담고 있는 구조체
typedef struct
{
	int code;
	SHAPE shape;
	Unit* unitData;
}FieldData;




