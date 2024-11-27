#include "Loading.h"
#include "../../Actor/Player/Player.h"
#include "../../DataParse/DataParse.h"
#include "../GameManager.h"
#include <string.h>

void LoadingStageData(char* sBuffer);

void InitializeStage(const char* const sStageFilePath) {
	OpenFile(sStageFilePath, LoadingStageData);

	ChangeScene(ESceneType::E_INSTAGE);
}

void LoadingActorData() {
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

				pToken = strtok_s(NULL, "}", &pContext);
			}
		}
	}
}