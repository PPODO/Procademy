#include "GameClear.h"
#include "../../Console/Console.h"
#include "../GameManager.h"
#include <Windows.h>

void GameClearSceneInput() {
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
		ChangeScene(ESceneType::E_TITLE);
}

void GameClearSceneRender() {
	Buffer_Clear();

	Sprite_DrawString(dfSCREEN_WIDTH / 2, dfSCREEN_HEIGHT / 2, "!GAME CLEAR!", ESpriteAligment::E_Center);
	Sprite_DrawString(dfSCREEN_WIDTH / 2, (dfSCREEN_HEIGHT / 2) + 2, "To Return To The Main Screen, Press The ESC Key.", ESpriteAligment::E_Center);

	Buffer_Flip();
}