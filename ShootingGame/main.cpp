#include <stdio.h>
#include <memory.h>
#include <Windows.h>
#include "Console/Console.h"
#include "Game/GameManager.h"

void main(void) {
	cs_Initial();

	InitializeGameManager();

	while (GetMainLoopRunState()) {
		Buffer_Clear();

		GameLoop();

		Buffer_Flip();

		Sleep(50);
	}
}