#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

// Console defines
#define CONSOLE_WIDTH 36
#define CONSOLE_HEIGHT 42

#define MAX_BUFFER_SIZE 256
#define MAX_DICE_COUNT 36

// Input macros
#define GetKeyDown(keyCode) GetAsyncKeyState(keyCode) & 0x8000
#define GetKey(keyCode) GetAsyncKeyState(keyCode) & 0x8001
#define GetKeyUp(keyCode) GetAsyncKeyState(keyCode) & 0x0001

// Global variables
unsigned char screenIndex;

HANDLE screen[2];

int diceCount;
int diceValues[MAX_DICE_COUNT];

// Flags
unsigned char quitEvent;

// General functions
void Init();
void Update();
void Render();
void Quit();

void CheckQuitProcess();

void InputDice();
void RollDices();

void ScreenFlipping();
void ScreenClear();
void ScreenPrint(unsigned short x, unsigned short y, char* message);

char* NumberToChar(int number);

int main(void)
{
	Init();
	
	while (!quitEvent)
	{
		Update();
		Sleep(10);
	}
	
	Quit();
	
	return 0;
}

void Init()
{
	// Random seed
	srand((unsigned int)time(NULL));
	
	// Setup console
	system("title Number Dice");
	system("mode con cols=36 lines=42");
	
	// Screen setup
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	
	consoleCursorInfo.bVisible = 0;
	consoleCursorInfo.dwSize = 1;
	
	screen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	
	SetConsoleCursorInfo(screen[0], &consoleCursorInfo);
	SetConsoleCursorInfo(screen[1], &consoleCursorInfo);
}

void Update()
{
	CheckQuitProcess();
	ScreenClear();
	InputDice();
	RollDices();
	Render();
	ScreenFlipping();
}

void Render()
{
	// Show dice count
	ScreenPrint(1, 1, NumberToChar(diceCount));
	
	int i;
	int j;
	int sum = 0;
	
	// Show dices
	for (i = 0; i < diceCount; i++)
	{
		int x = 4;
		int y = i + 3;
		
		ScreenPrint(x, y, "в║");
		
		for (j = 0; j < 6; j++)
		{
			ScreenPrint(x + j * 2 + 2, y, diceValues[i] < j ? "бр" : "бс");
		}
		
		sum += diceValues[i];
	}
	
	// Sum of all dices
	char* sumChar = NumberToChar(sum);
	
	ScreenPrint((CONSOLE_WIDTH >> 1) - (strlen(sumChar) >> 1), CONSOLE_HEIGHT - 2, sumChar);
}

void Quit()
{
	CloseHandle(screen[0]);
	CloseHandle(screen[1]);
}

void CheckQuitProcess()
{
	if (GetKeyDown(27))
	{
		quitEvent = 1;
	}
}

// Change the count of dice
void InputDice()
{
	if (GetKeyDown(VK_UP) && diceCount < MAX_DICE_COUNT)
	{
		diceCount++;
	}
	if (GetKeyDown(VK_DOWN) && diceCount > 0)
	{
		diceCount--;
	}
}

void RollDices()
{
	if (GetKeyDown(32))
	{
		int i;
		
		for (i = 0; i < diceCount; i++)
		{
			diceValues[i] = rand() % 6 + 1;
		}
	}
}

void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(screen[screenIndex]);
	
	screenIndex = !screenIndex;
}

void ScreenClear()
{
	COORD coord = { 0, 0 };
	DWORD dw;
	
	FillConsoleOutputCharacter(screen[screenIndex], ' ', (CONSOLE_WIDTH + 2) * (CONSOLE_HEIGHT + 1), coord, &dw);
}

void ScreenPrint(unsigned short x, unsigned short y, char* message)
{
	COORD position = { x, y };
	DWORD dw;
	
	SetConsoleCursorPosition(screen[screenIndex], position);
	WriteFile(screen[screenIndex], message, strlen(message), &dw, NULL);
}

char* NumberToChar(int number)
{
	char buffer[MAX_BUFFER_SIZE];
	
	sprintf(buffer, "%d", number);
	
	return buffer;
}
