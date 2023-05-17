#include"ProgramBase.h"
#include"PrintScreen.h"


int main(void)
{
	FieldData testData[HEIGHTSIZE][WIDTHSIZE];
	int temp = 0;
	for (int y = 0; y < HEIGHTSIZE; y++)
	{
		for (int x = 0; x < WIDTHSIZE; x++)
		{
			testData[y][x].code = 0;
			testData[y][x].shape.look = 'E';
			testData[y][x].shape.color = 1;
		}
	}
	printScreen(testData);
	scanf("%d", &temp);
	for (int y = 0; y < HEIGHTSIZE; y+=2)
	{
		for (int x = 0; x < WIDTHSIZE; x++)
		{
			testData[y][x].code = 1;
			testData[y][x].shape.look = 'N';
			testData[y][x].shape.color = 6;
		}
	}
	printScreen(testData);
	scanf("%d", &temp);
	for (int y = 0; y < HEIGHTSIZE; y += 1)
	{
		for (int x = 0; x < WIDTHSIZE; x+=3)
		{
			testData[y][x].code = 2;
			testData[y][x].shape.look = 'A';
			testData[y][x].shape.color = 4;
		}
	}
	printScreen(testData);
	scanf("%d", &temp);
	for (int y = 0; y < HEIGHTSIZE; y += 2)
	{
		for (int x = 0; x < WIDTHSIZE; x += 2)
		{
			testData[y][x].code = 3;
			testData[y][x].shape.look = 'O';
			testData[y][x].shape.color = 2;
		}
	}
	printScreen(testData);
	scanf("%d", &temp);

	return 0;
}

