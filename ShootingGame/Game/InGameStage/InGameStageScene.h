#pragma once
#include <Windows.h>

struct FStageInformation {
	char m_sStageFilePath[MAX_PATH];

};

// input
void InGamePlayerInput();

// logic
void InGameStageLogic();

// render
void InGameStageScene();