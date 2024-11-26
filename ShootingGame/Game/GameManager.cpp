#include "GameManager.h"
#include "Title/TitleScene.h"
#include "Loading/Loading.h"
#include "InGameStage/InGameStageScene.h"

static ESceneType g_CurrentSceneType;

void InitializeGameManager() {
	g_CurrentSceneType = ESceneType::E_TITLE;

	// load player info

	// load all enemy info
}

void ChangeScene(const ESceneType newSceneType) {
	g_CurrentSceneType = newSceneType;
}

void GameLoop() {
	switch (g_CurrentSceneType) {
	case ESceneType::E_TITLE:
		TitleInput();
		TitleScene();
		break;
	case ESceneType::E_LOADING:
		InitializeStage();
		break;
	case ESceneType::E_INSTAGE:
		InGamePlayerInput();
		InGameStageLogic();
		InGameStageScene();
		break;
	case ESceneType::E_CLEAR:

		break;
	}
}