#include "Loading.h"
#include "../../Actor/Player/Player.h"
#include "../GameManager.h"

void LoadingActorData();
void LoadingStageData();

void InitializeStage() {
	LoadingActorData();
	LoadingStageData();

	ChangeScene(ESceneType::E_INSTAGE);
}

void LoadingActorData() {
	InitializePlayerInformation();
}

void LoadingStageData() {
}
