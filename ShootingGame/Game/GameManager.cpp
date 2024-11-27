#include "GameManager.h"
#include "Title/TitleScene.h"
#include "Loading/Loading.h"
#include "InGameStage/InGameStageScene.h"
#include "../Actor/Player/Player.h"
#include "../Actor/Enemy/Enemy.h"
#include "../DataParse/DataParse.h"
#include "../Console/Console.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

static ESceneType g_CurrentSceneType;

static FStageInformation* g_ListOfStageInformation = NULL;
static unsigned int g_iMaxStageCnt;
static unsigned int g_iCurrentStageCnt = 0;

void LoadStageList(char* const sBuffer) {
	if (sBuffer) {
		ReadInt32(sBuffer, "StageCount", (int*)&g_iMaxStageCnt);

		g_ListOfStageInformation = (FStageInformation*)malloc(sizeof(FStageInformation) * g_iMaxStageCnt);

		char* pCachedBuffer = strstr(sBuffer, "{");
		if (g_ListOfStageInformation && pCachedBuffer != NULL) {
			char* pContext = NULL;
			char* pToken = strtok_s(pCachedBuffer, "}", &pContext);
			int iCnt = 0;

			while (pToken != NULL) {
				ReadString(pToken, "FilePath", g_ListOfStageInformation[iCnt++].m_sStageFilePath, MAX_PATH);

				pToken = strtok_s(NULL, "}", &pContext);
			}
		}
		else
			ChangeMainLoopRunState(false); // error
	}
}

void LoadEnemyList(char* const sBuffer) {
	if (sBuffer) {
		unsigned short iMaxEnemyTypeCount;
		ReadInt32(sBuffer, "EnemyTypeCount", (int*)&iMaxEnemyTypeCount);

		char* pCachedBuffer = strstr(sBuffer, "{");
		if (pCachedBuffer != NULL) {
			char* pContext = NULL;
			char* pToken = strtok_s(pCachedBuffer, "}", &pContext);

			char sEnemyDataInfoFilePath[MAX_PATH];
			unsigned int iPoolCount = 0;
			while (pToken != NULL) {
				if (ReadString(pToken, "FilePath", sEnemyDataInfoFilePath, MAX_PATH) &&
					ReadInt32(pToken, "PoolCount", (int*)&iPoolCount)) {
					OpenFile(sEnemyDataInfoFilePath, nullptr);

				}

				pToken = strtok_s(NULL, "}", &pContext);
			}
		}
	}
}

void InitializeGameManager() {
	g_CurrentSceneType = ESceneType::E_TITLE;

	OpenFile("Data//Player//player.dat", LoadPlayerInformation);
	OpenFile("Data//Enemy//EnemyList.dat", LoadEnemyList);
	OpenFile("Data//Stage//StageList.dat", LoadStageList);
}

void ClearGameManager() {


	if (g_ListOfStageInformation)
		free(g_ListOfStageInformation);
}

void ChangeScene(const ESceneType newSceneType) {
	g_CurrentSceneType = newSceneType;
}

void GameLoop() {
	// 로직과 scene 함수 분리

	switch (g_CurrentSceneType) {
	case ESceneType::E_TITLE:
		TitleInput();
		TitleScene();
		break;
	case ESceneType::E_LOADING:
		InitializeStage(g_ListOfStageInformation[g_iCurrentStageCnt++].m_sStageFilePath);
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