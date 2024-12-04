#include "InGameStageScene.h"
#include "../../Console/Console.h"
#include "../../Actor/Player/Player.h"
#include "../../Actor/Enemy/Enemy.h"
#include "../../Actor/Bullet/Bullet.h"
#include "../GameManager.h"
#include <Windows.h>

void InGameInput() {
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
		MoveX(-1);

	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
		MoveX(1);

	if (GetAsyncKeyState(VK_UP) & 0x8001)
		MoveY(-1);

	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
		MoveY(1);

	if (GetAsyncKeyState(VK_SPACE) & 0x8001)
		PlayerFire();
}

void InGameStageLogic() {
	if (!IsEnemiesAlive())
		ChangeScene(ESceneType::E_LOADING);

	BulletLogic();

	EnemyLogic();
}

void InGameStageScene() {
	Buffer_Clear();

	PlayerRendering();
	EnemyRendering();
	BulletRendering();

	Buffer_Flip();
}