#include "GameManager.h"
#include "Title/TitleScene.h"
#include "Loading/Loading.h"
#include "InGameStage/InGameStageScene.h"
#include "StageClear/StageClear.h"
#include "GameOver/GameOver.h"
#include "GameClear/GameClear.h"
#include "../Actor/Player/Player.h"
#include "../Actor/Enemy/Enemy.h"
#include "../Actor/Bullet/Bullet.h"
#include "../DataParse/DataParse.h"
#include "../Console/Console.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

static ESceneType g_CurrentSceneType;

static FStageInformation* g_ListOfStageInformation = NULL;
static unsigned int g_iMaxStageCnt;


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
		ReadInt16(sBuffer, "EnemyTypeCount", (short*)&iMaxEnemyTypeCount);

		AllocEnemyDatas(iMaxEnemyTypeCount);

		char* pCachedBuffer = strstr(sBuffer, "{");
		if (pCachedBuffer != NULL) {
			char* pContext = NULL;
			char* pToken = strtok_s(pCachedBuffer, "}", &pContext);

			char sEnemyDataInfoFilePath[MAX_PATH];

			while (pToken != NULL) {
				if (ReadString(pToken, "FilePath", sEnemyDataInfoFilePath, MAX_PATH))
					OpenFile(sEnemyDataInfoFilePath, LoadEnemyInformation);

				pToken = strtok_s(NULL, "}", &pContext);
			}
		}
		else
			ChangeMainLoopRunState(false); // error
	}
}

void LoadBulletList(char* const sBuffer) {
	if (sBuffer) {
		unsigned short iMaxBulletTypeCount;
		ReadInt16(sBuffer, "BulletTypeCount", (short*)&iMaxBulletTypeCount);

		AllocBulletDatas(iMaxBulletTypeCount);

		char* pCachedBuffer = strstr(sBuffer, "{");
		if (pCachedBuffer != NULL) {
			char* pContext = NULL;
			char* pToken = strtok_s(pCachedBuffer, "}", &pContext);

			char sEnemyDataInfoFilePath[MAX_PATH];

			while (pToken != NULL) {
				if (ReadString(pToken, "FilePath", sEnemyDataInfoFilePath, MAX_PATH))
					OpenFile(sEnemyDataInfoFilePath, LoadBulletInformation);

				pToken = strtok_s(NULL, "}", &pContext);
			}
		}
		else
			ChangeMainLoopRunState(false); // error
	}
}

void InitializeGameManager() {
	g_CurrentSceneType = ESceneType::E_TITLE;

	OpenFile("Data//Player//player.dat", LoadPlayerInformation);
	OpenFile("Data//Enemy//EnemyList.dat", LoadEnemyList);
	OpenFile("Data//Bullet//BulletList.dat", LoadBulletList);

	OpenFile("Data//Stage//StageList.dat", LoadStageList);
}

void ClearGameManager() {
	DeallocBulletDatas();
	DeallocEnemyDatas();

	free(g_ListOfStageInformation);
}

void ChangeScene(const ESceneType newSceneType) {
	g_CurrentSceneType = newSceneType;
}

unsigned int g_logicCnt = 0;
unsigned int g_renderCnt = 0;

void FPS() {
	static DWORD tick = timeGetTime();

	if (timeGetTime() - tick >= 1000) {
		printf("Logic : %d, Render : %d\n", g_logicCnt, g_renderCnt);
		g_logicCnt = 0;
		g_renderCnt = 0;

		tick += 1000;
	}
}

void GameLoop() {
	static unsigned int g_iCurrentStageCnt = 0;

	switch (g_CurrentSceneType) {
	case ESceneType::E_TITLE:
		g_iCurrentStageCnt = 0;

		TitleInput();

		if (!RenderSkip())
			TitleScene();
		break;
	case ESceneType::E_LOADING:
		InitializeStage(g_ListOfStageInformation[g_iCurrentStageCnt++].m_sStageFilePath);
		break;
	case ESceneType::E_INSTAGE:
		InGameInput();
		InGameStageLogic();
		g_logicCnt++;

		FPS();

		if (!RenderSkip()) {
			InGameStageScene();
			g_renderCnt++;
		}
		break;
	case ESceneType::E_STAGECLEAR:
		if (g_iCurrentStageCnt >= g_iMaxStageCnt)
			ChangeScene(ESceneType::E_GAMECLEAR);
		else {
			StageClearLogic(timeGetTime());

			if (!RenderSkip())
				StageClearSceneRender();
		}
		break;
	case ESceneType::E_GAMECLEAR:
		GameClearSceneInput();

		if (!RenderSkip())
			GameClearSceneRender();
		break;
	case ESceneType::E_GAMEOVER:
		GameOverSceneInput();

		if (!RenderSkip())
			GameOverSceneRender();
		break;
	}
}