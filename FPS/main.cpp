#include <stdio.h>
#include <Windows.h>
#include <time.h>
#pragma comment(lib, "winmm.lib") 

unsigned int g_logicCnt = 0;
unsigned int g_renderCnt = 0;

void Logic() {
	g_logicCnt++;

	if (GetAsyncKeyState(VK_SPACE))
		Sleep(10);
}

void FPS() {
	static int iFPSCnt = 0;
	static DWORD tick = timeGetTime();

	if (timeGetTime() - tick >= 1000) {
		printf("Logic : %d, Render : %d\n", g_logicCnt, g_renderCnt);
		iFPSCnt = 0;
		g_logicCnt = 0;
		g_renderCnt = 0;

		tick += 1000;
	}
}

void Render() {
	g_renderCnt++;

	Sleep(rand() % 15);
}

bool Skip() {
	static DWORD oldTime = timeGetTime();

	int t = timeGetTime() - oldTime;
	int sleepTick = 20 - t;
	if (sleepTick > 0)
		Sleep(sleepTick);

	oldTime += 20;

	if (sleepTick < 0) {
		return true;
	}
	return false;
}

int main() {
	srand(time(NULL));

	timeBeginPeriod(1);

	while (true) {
		Logic();

		FPS();

		if (!Skip()) {
			Render();
		}
	}

	timeEndPeriod(1);
	return 0;
}