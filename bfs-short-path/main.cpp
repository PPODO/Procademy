#include <iostream>
#include <vector>
#include <Windows.h>

#define W_SCREEN_SIZE 15
#define H_SCREEN_SIZE 10
#define MAX_QUEUE_SIZE 5000

struct COORDINATE {
	int X;
	int Y;

	int Num;
};

COORDINATE g_Queue[MAX_QUEUE_SIZE];
int g_QueueTopIndex = 0;
int g_QueueBottomIndex = 0;

char g_Map[H_SCREEN_SIZE][W_SCREEN_SIZE] =
{
	{ ' ', ' ', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },
	{ ' ', ' ', 'O', 'O', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', ' ', ' ', 'O' },
	{ ' ', ' ', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', ' ', ' ', ' ', 'O' },
	{ ' ', ' ', 'O', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', ' ', ' ', ' ', 'O' },
	{ ' ', ' ', 'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'O' },
	{ ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', ' ', 'O', 'O', ' ', ' ', ' ', 'O' },
	{ 'O', ' ', ' ', ' ', ' ', ' ', 'O', 'O', ' ', 'O', 'O', 'O', ' ', ' ', 'O' },
	{ 'O', ' ', 'O', 'O', 'O', ' ', 'O', 'O', ' ', 'O', 'O', 'O', ' ', ' ', 'O' },
	{ 'O', ' ', 'O', 'O', 'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },
};

int g_Tracking[H_SCREEN_SIZE][W_SCREEN_SIZE];

bool Enqueue(const COORDINATE& coord) {
	if (g_QueueTopIndex >= MAX_QUEUE_SIZE)
		return false;

	g_Queue[g_QueueTopIndex++] = coord;

	return true;
}

bool Dequeue(COORDINATE& coord) {
	if (g_QueueBottomIndex >= g_QueueTopIndex)
		return false;

	coord = g_Queue[g_QueueBottomIndex++];

	return true;
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

void BFS(const COORDINATE& goal) {
	if (goal.Y >= H_SCREEN_SIZE && goal.X >= W_SCREEN_SIZE)
		return;

	Enqueue({ 0, 0, 0 });

	COORDINATE outData;
	while (Dequeue(outData)) {
		if (outData.X < 0 || outData.Y < 0 || outData.X >= W_SCREEN_SIZE || outData.Y >= H_SCREEN_SIZE || g_Map[outData.Y][outData.X] != ' ')
			continue;

		g_Tracking[outData.Y][outData.X] = outData.Num;
		g_Map[outData.Y][outData.X] = '*';

		ScreenPrint();

		if (goal.X == outData.X && goal.Y == outData.Y)
			break;

		Enqueue({ outData.X + 1, outData.Y, outData.Num + 1 });
		Enqueue({ outData.X - 1, outData.Y, outData.Num + 1 });
		Enqueue({ outData.X, outData.Y + 1, outData.Num + 1 });
		Enqueue({ outData.X, outData.Y - 1, outData.Num + 1 });
	}

	int dy[4] = { 1,-1,0,0 };
	int dx[4] = { 0,0,1,-1 };
	const int path_length = g_Tracking[goal.Y][goal.X];
	std::vector<COORDINATE> short_path;

	short_path.push_back({ goal.X, goal.Y });
	for (int i = 1; i < path_length; i++) {
		for (int j = 0; j < 4; j++) {
			int ty = short_path[i - 1].Y + dy[j];
			int tx = short_path[i - 1].X + dx[j];

			if (g_Map[ty][tx] == '*' && g_Tracking[ty][tx] == path_length - i) {
				short_path.push_back({ tx, ty });
				break;
			}
		}
	}
	short_path.push_back({ 0, 0 });

	for (auto& it : short_path)
		g_Map[it.Y][it.X] = 'X';

	ScreenPrint();
}

int main() {

	ScreenPrint();

	BFS({ 14, 8 });

	return 0;
}