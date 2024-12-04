#include "TitleScene.h"
#include "../GameManager.h"
#include "../../Console/Console.h"
#include <Windows.h>

void TitleInput() {
	if (GetAsyncKeyState(0x31) & 0x8000)
		ChangeScene(ESceneType::E_LOADING);

	if (GetAsyncKeyState(0x32) & 0x8000)
		ChangeMainLoopRunState(false);
}

void TitleScene() {
	Buffer_Clear();

	Sprite_DrawString(40, 3, "-----------------", ESpriteAligment::E_Center);
	Sprite_DrawString(40, 4, "| Shooting Game |", ESpriteAligment::E_Center);
	Sprite_DrawString(40, 5, "-----------------", ESpriteAligment::E_Center);

	Sprite_DrawString(40, 17, "1. Game Start", ESpriteAligment::E_Center);
	Sprite_DrawString(40, 19, "2. Quit", ESpriteAligment::E_Center);

	Buffer_Flip();
}