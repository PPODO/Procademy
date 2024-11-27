#include "InGameStageScene.h"
#include "../../Actor/Player/Player.h"
#include <Windows.h>

void InGamePlayerInput() {
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
		MoveX(-1);

	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
		MoveX(1);

	if (GetAsyncKeyState(VK_UP) & 0x8001)
		MoveY(-1);

	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
		MoveY(1);

	if (GetAsyncKeyState(VK_SPACE) & 0x8001) {

	}
}

void InGameStageLogic() {
	// collision
	// ai
	// bullet movement

}

void InGameStageScene() {
	PlayerRendering();
}