#include <stdio.h>
#include <memory.h>
#include <Windows.h>
#include "Console/Console.h"
#include "Game/GameManager.h"

int main(void) {
	timeBeginPeriod(1);

	cs_Initial();

	InitializeGameManager();

	while (GetMainLoopRunState())
		GameLoop();

	ClearGameManager();

	timeEndPeriod(1);
	return 0;
}