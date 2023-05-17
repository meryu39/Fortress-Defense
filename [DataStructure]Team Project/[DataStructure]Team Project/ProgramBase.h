#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<iostream>
#pragma warning(disable:4996)

#define WIDTHSIZE 50
#define HEIGHTSIZE 10
//유닛의 그래픽 정보를 담고 있는 구조체
typedef struct
{
	unsigned short color;
	char look;
}SHAPE;
//게임 필드의 정보를 담고 있는 구조체
typedef struct
{
	int code;
	SHAPE shape;
}FieldData;



