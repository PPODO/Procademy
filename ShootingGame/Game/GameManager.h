#pragma once

enum ESceneType {
	E_TITLE,
	E_LOADING,
	E_INSTAGE,
	E_STAGECLEAR,
	E_GAMECLEAR,
	E_GAMEOVER
};

void InitializeGameManager();
void ClearGameManager();


void ChangeScene(const ESceneType newSceneType);

void GameLoop();