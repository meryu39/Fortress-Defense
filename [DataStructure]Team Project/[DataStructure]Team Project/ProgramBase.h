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
//������ �׷��� ������ ��� �ִ� ����ü
typedef struct
{
	unsigned short color;
	char look;
}SHAPE;
//���� �ʵ��� ������ ��� �ִ� ����ü
typedef struct
{
	int code;
	SHAPE shape;
}FieldData;



