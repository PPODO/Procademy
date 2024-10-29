#include <iostream>
#include <Windows.h>

#define W_SCREEN_SIZE 15
#define H_SCREEN_SIZE 10

char g_Map[H_SCREEN_SIZE][W_SCREEN_SIZE] =
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

void Paint(int x, int y) {
	if (x < 0 || x >= W_SCREEN_SIZE || y < 0 || y >= H_SCREEN_SIZE)
		return;

	if (g_Map[y][x] == 'O') {
		g_Map[y][x] = 'X';
		ScreenPrint();
	}
	else
		return;

	Paint(x + 1, y);
	Paint(x - 1, y);
	Paint(x, y + 1);
	Paint(x, y - 1);
}

int main() {
	ScreenPrint();

	Paint(7, 5);

	return 0;
}