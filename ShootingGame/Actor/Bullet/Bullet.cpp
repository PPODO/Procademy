#include "Bullet.h"
#include <stdlib.h>
#include <memory.h>
#include <Windows.h>
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../../Console/Console.h"
#include "../../DataParse/DataParse.h"

#define dfBULLET_MAX_COUNT 100

static FBullet** g_pBulletActorPoolList = NULL;

static unsigned short g_iMaxBulletTypeCount = 0;

void AllocBulletDatas(const unsigned short iMaxBulletTypeCount) {
	g_iMaxBulletTypeCount = iMaxBulletTypeCount;
	g_pBulletActorPoolList = (FBullet**)malloc(sizeof(FBullet*) * iMaxBulletTypeCount);
}

void DeallocBulletDatas() {
	for (unsigned short i = 0; i < g_iMaxBulletTypeCount; i++)
		free(g_pBulletActorPoolList[i]);

	free(g_pBulletActorPoolList);
}

void ClearBulletPoolList() {
	for (unsigned short i = 0; i < g_iMaxBulletTypeCount; i++) {
		for (int j = 0; j < dfBULLET_MAX_COUNT; j++) {
			if (g_pBulletActorPoolList[i])
				g_pBulletActorPoolList[i][j].m_bIsVisible = false;
		}
	}
}

void LoadBulletInformation(char* const sBuffer) {
	static unsigned short iLoadedCnt = 0;

	if (g_pBulletActorPoolList && sBuffer) {
		short iBulletType = -1;
		ReadInt16(sBuffer, "Type", &iBulletType);

		if (iBulletType > g_iMaxBulletTypeCount && iLoadedCnt >= g_iMaxBulletTypeCount)
			return;

		g_pBulletActorPoolList[iBulletType] = (FBullet*)malloc(sizeof(FBullet) * dfBULLET_MAX_COUNT);

		if (g_pBulletActorPoolList[iBulletType]) {
			short iXPosMoveSpeed = -1;
			short iYPosMoveSpeed = -1;
			short iDamage = -1;
			int iMovementDelayTime = 0;
			char cSprite = 0;

			ReadInt16(sBuffer, "XPosMoveSpeed", &iXPosMoveSpeed);
			ReadInt16(sBuffer, "YPosMoveSpeed", &iYPosMoveSpeed);

			ReadInt16(sBuffer, "Damage", &iDamage);

			ReadInt32(sBuffer, "MovementDelayTime", &iMovementDelayTime);

			ReadInt8(sBuffer, "Sprite", &cSprite);

			for (int i = 0; i < dfBULLET_MAX_COUNT; i++) {
				g_pBulletActorPoolList[iBulletType][i].m_iType = iBulletType;

				g_pBulletActorPoolList[iBulletType][i].m_iXPosSpeed = iXPosMoveSpeed;
				g_pBulletActorPoolList[iBulletType][i].m_iYPosSpeed = iYPosMoveSpeed;

				g_pBulletActorPoolList[iBulletType][i].m_iDamage = iDamage;

				g_pBulletActorPoolList[iBulletType][i].m_bIsVisible = false;
				g_pBulletActorPoolList[iBulletType][i].m_bIsPlayerOwned = false;

				g_pBulletActorPoolList[iBulletType][i].m_cSprite = cSprite;

				g_pBulletActorPoolList[iBulletType][i].m_iLastMovementTime = 0;
				g_pBulletActorPoolList[iBulletType][i].m_iMovementDelayTime = iMovementDelayTime;
			}
		}

		iLoadedCnt++;
	}
	else
		ChangeMainLoopRunState(false); // error
}

void Fire(const unsigned short iBulletType, const unsigned short iX, const unsigned short iY, const bool bIsPlayerRequest) {
	if (iBulletType < g_iMaxBulletTypeCount && g_pBulletActorPoolList[iBulletType]) {
		for (int i = 0; i < dfBULLET_MAX_COUNT; i++) {
			if (!g_pBulletActorPoolList[iBulletType][i].m_bIsVisible) {
				g_pBulletActorPoolList[iBulletType][i].m_iX = iX;
				g_pBulletActorPoolList[iBulletType][i].m_iY = iY;

				g_pBulletActorPoolList[iBulletType][i].m_bIsPlayerOwned = bIsPlayerRequest;
				g_pBulletActorPoolList[iBulletType][i].m_bIsVisible = true;	

				break;
			}
		}
	}
}

_inline void BulletMovementLogic(const unsigned short iBulletType, const unsigned short iBulletIndex) {
	DWORD iCurrentTime = timeGetTime();

	if (iCurrentTime - g_pBulletActorPoolList[iBulletType][iBulletIndex].m_iLastMovementTime >= g_pBulletActorPoolList[iBulletType][iBulletIndex].m_iMovementDelayTime) {
		g_pBulletActorPoolList[iBulletType][iBulletIndex].m_iY += g_pBulletActorPoolList[iBulletType][iBulletIndex].m_iYPosSpeed * (g_pBulletActorPoolList[iBulletType][iBulletIndex].m_bIsPlayerOwned ? -1 : 1);
		g_pBulletActorPoolList[iBulletType][iBulletIndex].m_iX += g_pBulletActorPoolList[iBulletType][iBulletIndex].m_iXPosSpeed;

		g_pBulletActorPoolList[iBulletType][iBulletIndex].m_iLastMovementTime = iCurrentTime;
	}
}

_inline void BulletCollisionLogic(const unsigned short iBulletType, const unsigned short iBulletIndex) {
	const unsigned short iCachedX = g_pBulletActorPoolList[iBulletType][iBulletIndex].m_iX;
	const unsigned short iCachedY = g_pBulletActorPoolList[iBulletType][iBulletIndex].m_iY;
	const unsigned short iCachedDamage = g_pBulletActorPoolList[iBulletType][iBulletIndex].m_iDamage;

	g_pBulletActorPoolList[iBulletType][iBulletIndex].m_bIsVisible = !((g_pBulletActorPoolList[iBulletType][iBulletIndex].m_bIsPlayerOwned) ? EnemyCollisionLogic(iCachedX, iCachedY, iCachedDamage) : PlayerCollisionLogic(iCachedX, iCachedY, iCachedDamage));
}

void BulletLogic() {
	for (unsigned short i = 0; i < g_iMaxBulletTypeCount; i++) {
		for (unsigned short j = 0; j < dfBULLET_MAX_COUNT; j++) {
			if (g_pBulletActorPoolList[i] && g_pBulletActorPoolList[i][j].m_bIsVisible) {
				if ((g_pBulletActorPoolList[i][j].m_iY < 0 || g_pBulletActorPoolList[i][j].m_iY > dfSCREEN_HEIGHT) ||
					(g_pBulletActorPoolList[i][j].m_iX < 0 || g_pBulletActorPoolList[i][j].m_iX > dfSCREEN_WIDTH)) {
					g_pBulletActorPoolList[i][j].m_bIsVisible = false;
					continue;
				}

				BulletCollisionLogic(i, j);
				BulletMovementLogic(i, j);
			}
		}
	}
}

void BulletRendering() {
	for (unsigned short i = 0; i < g_iMaxBulletTypeCount; i++) {
		for (int j = 0; j < dfBULLET_MAX_COUNT; j++) {
			if (g_pBulletActorPoolList[i] && g_pBulletActorPoolList[i][j].m_bIsVisible)
				Sprite_DrawCharacter(g_pBulletActorPoolList[i][j].m_iX, g_pBulletActorPoolList[i][j].m_iY, g_pBulletActorPoolList[i][j].m_cSprite);
		}
	}
}
