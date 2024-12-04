#include "Loading.h"
#include "../../Actor/Player/Player.h"
#include "../../Actor/Enemy/Enemy.h"
#include "../../Actor/Bullet/Bullet.h"
#include "../../DataParse/DataParse.h"
#include "../GameManager.h"
#include <string.h>
#include <random>

void LoadingStageData(char* sBuffer);

void InitializeStage(const char* const sStageFilePath) {
	srand((unsigned int)time(NULL));

	ClearEnemyPoolList();
	ClearBulletPoolList();

	OpenFile(sStageFilePath, LoadingStageData);

	ChangeScene(ESceneType::E_INSTAGE);
}

void LoadingStageData(char* sBuffer) {
	if (sBuffer) {
		char* pCachedBuffer = strstr(sBuffer, "{");
		if (pCachedBuffer != NULL) {
			char* pContext = NULL;
			char* pToken = strtok_s(pCachedBuffer, "}", &pContext);

			while (pToken != NULL) {
				short iActorType = -1;
				short iX = -1;
				short iY = -1;

				ReadInt16(pToken, "ActorType", &iActorType);
				ReadInt16(pToken, "X", &iX);
				ReadInt16(pToken, "Y", &iY);

				if (iActorType == 0)
					InitializePlayerInformation(iX, iY);
				else
					AllocEnemyToPool(iActorType, iX, iY);

				pToken = strtok_s(NULL, "}", &pContext);
			}
		}
	}
}