#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<iostream>
#include<stdbool.h>
#pragma warning(disable:4996)

#define FIELD_WIDTH 32//����ũ��
#define FIELD_HEIGHT 20//����ũ��

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



