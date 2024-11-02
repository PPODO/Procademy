#include <iostream>
#include <Windows.h>

#define W_SCREEN_SIZE 15
#define H_SCREEN_SIZE 10
#define MAX_STACK_SIZE 5000
#define MAX_DIRECTION 4

struct COORDINATE {
	int X;
	int Y;
};

COORDINATE g_Stack[MAX_STACK_SIZE];
int g_StackTopIndex = 0;

bool Push(const COORDINATE& COORDINATE) {
	if (g_StackTopIndex >= MAX_STACK_SIZE)
		return false;

	g_Stack[g_StackTopIndex++] = COORDINATE;

	return true;
}

bool Pop(COORDINATE& outData) {
	if (g_StackTopIndex - 1 < 0)
		return false;

	outData = g_Stack[--g_StackTopIndex];

	return true;
}

char g_OriginalMap[H_SCREEN_SIZE][W_SCREEN_SIZE] =
{
	{ '*', '*', 'O', 'O', '*', '*', 'O', '*', '*', '*', '*', '*', '*', '*', '*' },
	{ '*', 'O', 'O', 'O', '*', 'O', 'O', 'O', 'O', 'O', 'O', '*', '*', '*', '*' },
	{ '*', 'O', 'O', 'O', 'O', 'O', '*', '*', 'O', 'O', 'O', 'O', '*', 'O', '*' },
	{ 'O', 'O', 'O', '*', '*', '*', 'O', 'O', 'O', '*', 'O', 'O', 'O', 'O', '*' },
	{ '*', 'O', 'O', 'O', '*', 'O', 'O', 'O', '*', '*', 'O', 'O', 'O', 'O', '*' },
	{ '*', 'O', 'O', 'O', '*', '*', 'O', 'O', 'O', '*', 'O', 'O', 'O', 'O', 'O' },
	{ '*', '*', 'O', 'O', 'O', '*', '*', 'O', 'O', '*', '*', 'O', 'O', 'O', '*' },
	{ '*', '*', 'O', 'O', 'O', '*', 'O', 'O', 'O', 'O', '*', 'O', 'O', 'O', 'O' },
	{ '*', '*', '*', '*', '*', '*', '*', 'O', 'O', '*', '*', '*', 'O', 'O', '*' },
	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
};

char g_Map[H_SCREEN_SIZE][W_SCREEN_SIZE];

void Init() {
	memcpy(g_Map, g_OriginalMap, H_SCREEN_SIZE * W_SCREEN_SIZE);
	g_StackTopIndex = 0;

	Push(COORDINATE{ 7, 5 });
}

void ScreenPrint() {
	Sleep(50);
	system("cls");

	for (int i = 0; i < H_SCREEN_SIZE; i++) {
		for (int j = 0; j < W_SCREEN_SIZE; j++) {
			printf("%c", g_Map[i][j]);
		}
		printf("\n");
	}
}

void Paint() {
	COORDINATE outData;
	
	while (g_StackTopIndex >= 1) {
		--g_StackTopIndex;
		outData.X = g_Stack[g_StackTopIndex].X;
		outData.Y = g_Stack[g_StackTopIndex].Y;

		if (outData.X >= W_SCREEN_SIZE || outData.Y >= H_SCREEN_SIZE || g_Map[outData.Y][outData.X] != 'O')
			continue;

		g_Map[outData.Y][outData.X] = 'X';

		if (g_StackTopIndex < MAX_STACK_SIZE) {
			g_Stack[g_StackTopIndex].X = outData.X - 1;
			g_Stack[g_StackTopIndex].Y = outData.Y;
			++g_StackTopIndex;
		}

		if (g_StackTopIndex < MAX_STACK_SIZE) {
			g_Stack[g_StackTopIndex].X = outData.X + 1;
			g_Stack[g_StackTopIndex].Y = outData.Y;
			++g_StackTopIndex;
		}

		if (g_StackTopIndex < MAX_STACK_SIZE) {
			g_Stack[g_StackTopIndex].X = outData.X;
			g_Stack[g_StackTopIndex].Y = outData.Y - 1;
			++g_StackTopIndex;
		}

		if (g_StackTopIndex < MAX_STACK_SIZE) {
			g_Stack[g_StackTopIndex].X = outData.X;
			g_Stack[g_StackTopIndex].Y = outData.Y + 1;
			++g_StackTopIndex;
		}
	}
}

int main() {
	Init();

	ScreenPrint();

	clock_t totalTime = 0;
	for (int i = 0; i < 10000; i++) {
		clock_t startTime = clock();
		Paint();
		totalTime += clock() - startTime;

		Init();
	}

	ScreenPrint();

	std::cout << totalTime << std::endl;

	return 0;
}