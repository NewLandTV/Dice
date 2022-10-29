#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define CONSOLE_WIDTH 34
#define CONSOLE_HEIGHT 17

void Init();
void Update();
void DrawDiceSprite(int number);
void Gotoxy(int x, int y);

int main(void)
{
	Init();
	
	while (1)
	{
		Update();
	}
	
	return 0;
}

void Init()
{
	srand((unsigned int)time(NULL));
	
	system("title Dice");
	system("mode con cols=34 lines=17");
	
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	
	consoleCursorInfo.bVisible = 0;
	consoleCursorInfo.dwSize = 1;
	
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
}

void Update()
{
	_getch();
	
	DrawDiceSprite(rand() % 6);
}

void DrawDiceSprite(int number)
{
	int x;
	int y;
	
	system("cls");
	
	for (y = 0; y < CONSOLE_HEIGHT; y++)
	{
		for (x = 0; x < CONSOLE_WIDTH - 1; x += 2)
		{
			Gotoxy(x, y);
			
			if (x == 0 || y == 0 || x == CONSOLE_WIDTH - 2 || y == CONSOLE_HEIGHT - 1)
			{
				printf("¡á");
			}
		}
	}
	
	switch (number)
	{
		// 1
		case 0:
			Gotoxy((CONSOLE_WIDTH >> 1) - 1, CONSOLE_HEIGHT >> 1);
			printf("¡Û");
			
			break;
			
		// 2
		case 1:
			Gotoxy((CONSOLE_WIDTH >> 2) - 1, CONSOLE_HEIGHT >> 2);
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) + (CONSOLE_WIDTH >> 1) - 1, (CONSOLE_HEIGHT >> 2) + (CONSOLE_HEIGHT >> 1));
			printf("¡Û");
			
			break;
			
		// 3
		case 2:
			Gotoxy((CONSOLE_WIDTH >> 2) - 1, CONSOLE_HEIGHT >> 2);
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 1) - 1, CONSOLE_HEIGHT >> 1);
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) + (CONSOLE_WIDTH >> 1) - 1, (CONSOLE_HEIGHT >> 2) + (CONSOLE_HEIGHT >> 1));
			printf("¡Û");
			
			break;
			
		// 4
		case 3:
			Gotoxy((CONSOLE_WIDTH >> 2) - 1, CONSOLE_HEIGHT >> 2);
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) + (CONSOLE_WIDTH >> 1) - 1, CONSOLE_HEIGHT >> 2);
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) - 1, (CONSOLE_HEIGHT >> 2) + (CONSOLE_HEIGHT >> 1));
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) + (CONSOLE_WIDTH >> 1) - 1, (CONSOLE_HEIGHT >> 2) + (CONSOLE_HEIGHT >> 1));
			printf("¡Û");
			
			break;
		// 5
		case 4:
			Gotoxy((CONSOLE_WIDTH >> 1) - 1, CONSOLE_HEIGHT >> 1);
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) - 1, CONSOLE_HEIGHT >> 2);
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) + (CONSOLE_WIDTH >> 1) - 1, CONSOLE_HEIGHT >> 2);
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) - 1, (CONSOLE_HEIGHT >> 2) + (CONSOLE_HEIGHT >> 1));
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) + (CONSOLE_WIDTH >> 1) - 1, (CONSOLE_HEIGHT >> 2) + (CONSOLE_HEIGHT >> 1));
			printf("¡Û");
			
			break;
			
		// 6
		case 5:
			Gotoxy((CONSOLE_WIDTH >> 2) - 1, CONSOLE_HEIGHT >> 2);
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) + (CONSOLE_WIDTH >> 1) - 1, CONSOLE_HEIGHT >> 2);
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) - 1, CONSOLE_HEIGHT >> 1);
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) + (CONSOLE_WIDTH >> 1) - 1, CONSOLE_HEIGHT >> 1);
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) - 1, (CONSOLE_HEIGHT >> 2) + (CONSOLE_HEIGHT >> 1));
			printf("¡Û");
			Gotoxy((CONSOLE_WIDTH >> 2) + (CONSOLE_WIDTH >> 1) - 1, (CONSOLE_HEIGHT >> 2) + (CONSOLE_HEIGHT >> 1));
			printf("¡Û");
			
			break;
	}
}

void Gotoxy(int x, int y)
{
	COORD position = { x, y };
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
