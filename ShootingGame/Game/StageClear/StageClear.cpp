#include "StageClear.h"
#include "../../Console/Console.h"
#include "../GameManager.h"

void StageClearLogic(const DWORD iCurrentTime) {
	static DWORD iCachedTime = 0;
	if (iCachedTime == 0)
		iCachedTime = iCurrentTime;

	if (iCurrentTime - iCachedTime >= 1000) {
		iCachedTime = 0;
		ChangeScene(ESceneType::E_LOADING);
	}
}

void StageClearSceneRender() {
	Buffer_Clear();

	Sprite_DrawString(dfSCREEN_WIDTH / 2, dfSCREEN_HEIGHT / 2, "! STAGE CLEAR !", ESpriteAligment::E_Center);
	Sprite_DrawString(dfSCREEN_WIDTH / 2, (dfSCREEN_HEIGHT / 2) + 2, "Next Stage Loading...", ESpriteAligment::E_Center);

	Buffer_Flip();
}