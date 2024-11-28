#pragma once

enum ESceneType {
	E_TITLE,
	E_LOADING,
	E_INSTAGE,
	E_CLEAR
};

void InitializeGameManager();
void ClearGameManager();


void ChangeScene(const ESceneType newSceneType);

void GameLoop();