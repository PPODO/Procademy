#include <windows.h>
#include <stdio.h>
#include "Console.h"
#pragma comment(lib, "winmm.lib") 

// global
char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
HANDLE  hConsole;

bool g_bMainLoopRunState = true;

void cs_Initial(void) {
	CONSOLE_CURSOR_INFO stConsoleCursor;

	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hConsole, &stConsoleCursor);
}

void cs_MoveCursor(int iPosX, int iPosY) {
	COORD stCoord;
	stCoord.X = iPosX;
	stCoord.Y = iPosY;

	SetConsoleCursorPosition(hConsole, stCoord);
}

void cs_ClearScreen(void) {
	DWORD dw;

	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 100 * 100, { 0, 0 }, &dw);
}

void Buffer_Flip(void) {
	int iCnt;
	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++) {
		cs_MoveCursor(0, iCnt);
		printf(szScreenBuffer[iCnt]);
	}
}

void Buffer_Clear(void) {
	int iCnt;
	memset(szScreenBuffer, ' ', dfSCREEN_WIDTH * dfSCREEN_HEIGHT);

	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
		szScreenBuffer[iCnt][dfSCREEN_WIDTH - 1] = '\0';
}

void Sprite_DrawCharacter(int iX, int iY, char chSprite) {
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
		return;

	szScreenBuffer[iY][iX] = chSprite;
}

void Sprite_DrawString(const int iX, const int iY, const char* const strSprite, const ESpriteAligment aligment) {
	const int iSpriteLength = strlen(strSprite);
	const int iXStartOffset = (aligment == ESpriteAligment::E_Left) ? iX : (aligment == ESpriteAligment::E_Center) ? iX - (iSpriteLength / 2) : iX + iSpriteLength;

	for (int i = 0; i < iSpriteLength; i++)
		Sprite_DrawCharacter(iXStartOffset + i, iY, *(strSprite + i));
}

void ChangeMainLoopRunState(const bool bNewState) {
	g_bMainLoopRunState = bNewState;
}

bool GetMainLoopRunState() {
	return g_bMainLoopRunState;
}

bool RenderSkip() {
	static DWORD oldTime = timeGetTime();

	int t = timeGetTime() - oldTime;
	int sleepTick = 20 - t;
	if (sleepTick > 0)
		Sleep(sleepTick);

	oldTime += 20;

	if (sleepTick < 0)
		return true;

	return false;
}