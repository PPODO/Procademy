#include <iostream>
#include <Windows.h>

#define W_SCREEN_SIZE 15
#define H_SCREEN_SIZE 10

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

void Paint(const int x, const int y, const int iDepth) {
	if (x < 0 || x >= W_SCREEN_SIZE || y < 0 || y >= H_SCREEN_SIZE || g_Map[y][x] != 'O')
		return;

	g_Map[y][x] = 'X';

	Paint(x + 1, y, iDepth + 1);
	Paint(x - 1, y, iDepth + 1);
	Paint(x, y + 1, iDepth + 1);
	Paint(x, y - 1, iDepth + 1);
}

int main() {
	Init();

	ScreenPrint();

	clock_t totalTime = 0;
	for (int i = 0; i < 10000; i++) {
		clock_t startTime = clock();
		Paint(7, 5, 0);
		totalTime += clock() - startTime;

		Init();
	}

	ScreenPrint();

	std::cout << totalTime << std::endl;


	return 0;
}