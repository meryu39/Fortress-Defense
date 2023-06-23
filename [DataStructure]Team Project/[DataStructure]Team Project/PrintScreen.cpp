#pragma once
#include"PrintScreen.h"

char defaultMap[FIELD_HEIGHT][FIELD_WIDTH];
extern int resource;
extern Unit* mycamp;
extern Unit* enemycamp;
extern FieldData field[FIELD_HEIGHT][FIELD_WIDTH];

void setColor(unsigned short color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	return;
}

void goto_xy(SHORT x, SHORT y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	Position pos = { x, y };
	SetConsoleCursorPosition(handle, pos);
}

void goto_xy(Position pos)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
}


void printScreen(FieldData (*inputData)[FIELD_WIDTH])
{
	static bool is_init = FALSE;
	static FieldData beforeData[FIELD_HEIGHT][FIELD_WIDTH];
	static char background[FIELD_HEIGHT][FIELD_WIDTH + 2];

	if (!is_init)
	{
		FILE* background_file = fopen("Background.txt", "r");
		bool lineEnd = FALSE;
		for (int y = 0; y < FIELD_HEIGHT; y++)
		{
			fgets(background[y], FIELD_WIDTH + 2, background_file);
			for (int x = 0; x < FIELD_WIDTH; x++)
			{
				beforeData[y][x].code = 0;
				if (background[y][x] == '\n' || background[y][x] == '\0')
				{
					lineEnd = TRUE;
				}
				if (lineEnd)
				{
					background[y][x] = ' ';
				}
				goto_xy(x * DOTSIZE_X, y * DOTSIZE_Y);
				setColor(BACKGROUND_COLOR);
				printf("%c", background[y][x]);
			}
			lineEnd = FALSE;
		}
		is_init = TRUE;
		fclose(background_file);
		return;
	}
	for (int y = 0; y < FIELD_HEIGHT; y++)
	{
		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			if (beforeData[y][x].code != inputData[y][x].code)
			{
				goto_xy(x * DOTSIZE_X, y * DOTSIZE_Y);
				beforeData[y][x] = inputData[y][x];
				if (inputData[y][x].code == 0)
				{
					setColor(BACKGROUND_COLOR);
					printf("%c", background[y][x]);

					continue;
				}
				setColor(inputData[y][x].shape.color);
				if (inputData[y][x].unitData != NULL)
				{
					switch (inputData[y][x].unitData->unit_code)
					{
					case 1:
						printf("■");
						break;
					case 2:
						printf("▲");
						break;
					case 3:
						printf("♠");
						break;
					case 4:
						printf("Ψ");
						break;
					case 5:
						printf("♣");
						break;
					case 6:
						printf("θ");
						break;
					case 7:
						printf("★");
						break;
					}
				}
				//printf("%c", inputData[y][x].shape.look);
			}
		}
	}

	return;
}

void printUI()
{
	goto_xy(0, 11);
	setColor(WHITE);
	printf("GOLD%5d      ", resource);

	//체력 출력
	goto_xy(2, 2);
	printf("%4d", mycamp->hp);
	goto_xy(92, 2);
	printf("%4d", enemycamp->hp);
	printDamage();
}

void printDamage(Position pos, int damage, int color)
{
	static Position damage_print_pos[DAMAGEPRINTQUEUE_MAXINDEX];
	static int damage_print_tick[DAMAGEPRINTQUEUE_MAXINDEX];
	static int frontIndex = 0;
	static int rearIndex = 0;

	for (int i = frontIndex; i < rearIndex; i++)
	{
		damage_print_tick[i % DAMAGEPRINTQUEUE_MAXINDEX]--;
		field[damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].X].code = -1;
		field[damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].X + 1].code = -1;
		field[damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].X + 2].code = -1;
		if (damage_print_tick[i % DAMAGEPRINTQUEUE_MAXINDEX] <= 0)
		{
			field[damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].X].code = 0;
			field[damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].X].shape.color = BACKGROUND_COLOR;
			field[damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].X + 1].code = 0;
			field[damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].X + 1].shape.color = BACKGROUND_COLOR;
			field[damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].X + 2].code = 0;
			field[damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[i % DAMAGEPRINTQUEUE_MAXINDEX].X + 2].shape.color = BACKGROUND_COLOR;

			frontIndex++;
		}
	}

	if (damage != -1)
	{
		if ((rearIndex + 1) % DAMAGEPRINTQUEUE_MAXINDEX == frontIndex % DAMAGEPRINTQUEUE_MAXINDEX)
		{
			goto_xy(20, 0);
			printf("error : 데미지 출력 큐 초과");
			return;
		}
		damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX] = pos;
		damage_print_tick[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX] = DAMAGE_PRINT_TICK;
		field[damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].X].code = -1;
		field[damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].X].shape.color = color;
		field[damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].X + 1].code = -1;
		field[damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].X + 1].shape.color = color;
		field[damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].X + 2].code = -1;
		field[damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].Y][damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].X + 2].shape.color = color;
		goto_xy(damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].X, damage_print_pos[rearIndex % DAMAGEPRINTQUEUE_MAXINDEX].Y);
		setColor(color);
		printf("-%d", damage);
		rearIndex++;
	}

}

void init_UI()
{
	for (int i = 1; i < FIELD_WIDTH; i++) {
		goto_xy(i, 0);
		printf("━");
		goto_xy(i, FIELD_HEIGHT);
		printf("━");
	}

	for (int i = 1; i < FIELD_HEIGHT; i++) {
		goto_xy(0, i);
		printf("┃");
		goto_xy(FIELD_WIDTH, i);
		printf("┃");
	}

	goto_xy(0, 0);
	printf("┏");
	goto_xy(0, FIELD_HEIGHT);
	printf("┗");
	goto_xy(FIELD_WIDTH, 0);
	printf("┓");
	goto_xy(FIELD_WIDTH, FIELD_HEIGHT);
	printf("┛");

	for (int i = 0; i < 30; i++)
	{
		if (i % 6 == 0)
		{
			goto_xy(i, FIELD_HEIGHT + 2);
			printf("┏");
			goto_xy(i, FIELD_HEIGHT + 3);
			printf("┃");
			goto_xy(i, FIELD_HEIGHT + 4);
			printf("┗");
		}
		if (i % 6 == 1 || i % 6 == 2 || i % 6 == 3)
		{
			goto_xy(i, FIELD_HEIGHT + 2);
			printf("━");
			goto_xy(i, FIELD_HEIGHT + 2);
			goto_xy(i, FIELD_HEIGHT + 4);
			printf("━");
		}
		if (i % 6 == 4)
		{
			goto_xy(i, FIELD_HEIGHT + 2);
			printf("┓");
			goto_xy(i, FIELD_HEIGHT + 3);
			printf("┃");
			goto_xy(i, FIELD_HEIGHT + 4);
			printf("┛");
		}

	}

	setColor(WHITE);
	goto_xy(35, FIELD_HEIGHT + 2);
	printf("■ %3s : %3d골드, 가장 기본적인 근접 유닛이다. ", "병사", 35);
	goto_xy(37, FIELD_HEIGHT + 3);
	printf("낮은 공격력과 적당한 체력을 가지고 있다.");
	goto_xy(35, FIELD_HEIGHT + 4);
	printf("▲ %3s : %3d골드, 가장 기본적인 원거리 유닛이다. ", "궁병", 50);
	goto_xy(37, FIELD_HEIGHT + 5);
	printf("병사보다 낮은 공격력과 체력을 가지고 있지만, 4칸 너머 유닛을 공격할 수 있다.");
	goto_xy(35, FIELD_HEIGHT + 6);
	printf("♠ %3s : %3d골드, 평균적인 전투력을 가진 근접 유닛이다. ", "창병", 75);
	goto_xy(37, FIELD_HEIGHT + 7);
	printf("병사보다 높은 공격력과 체력을 가지고 있으며 2칸 너머 유닛을 공격할 수 있다.");
	goto_xy(35, FIELD_HEIGHT + 8);
	printf("Ψ %3s : %3d골드, 평균적인 전투력을 가진 원거리 유닛이다. ", "투창병", 110);
	goto_xy(37, FIELD_HEIGHT + 9);
	printf("병사보다 높은 공격력을 가지고 있으며 4칸 너머 유닛을 공격할 수 있다.");
	goto_xy(35, FIELD_HEIGHT + 10);
	printf("♣ %3s : %3d골드, 평균적인 전투력을 가진 빠른 근접 유닛이다. ", "기마병", 150);
	goto_xy(37, FIELD_HEIGHT + 11);
	printf("창병보다 높은 공격력과 체력을 가지고 있으며 빠른 이동 속도를 가지고 있다.");
	goto_xy(35, FIELD_HEIGHT + 12);
	printf("θ %3s : % 3d골드, 강력한 전투력을 가진 근접 유닛이다. ", "성기사", 240);
	goto_xy(37, FIELD_HEIGHT + 13);
	printf("높은 공격력과 체력을 가지고 있다.");
	goto_xy(35, FIELD_HEIGHT + 14);
	printf("★ %3s : %3d골드, 매우 강력한 전투력을 가진 근접 유닛이다. ", "장군", 280);
	goto_xy(37, FIELD_HEIGHT + 15);
	printf("매우 강력한 공격력과 체력을 가지고 있지만 이동 속도가 살짝 느리다.");

	return;
}