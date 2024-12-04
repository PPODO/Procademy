#pragma once
#include <Windows.h>

struct FStageInformation {
	char m_sStageFilePath[MAX_PATH];

};

// input
void InGameInput();

// logic
void InGameStageLogic();

// render
void InGameStageScene();