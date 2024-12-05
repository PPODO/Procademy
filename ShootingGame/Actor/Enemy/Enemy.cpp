#include "Enemy.h"
#include <stdlib.h>
#include <memory.h>
#include <Windows.h>
#include <random>
#include "../Bullet/Bullet.h"
#include "../../Console/Console.h"
#include "../../DataParse/DataParse.h"

#define dfENEMY_POOL_SIZE 100

static FEnemy* g_pEnemyDatas = NULL;

static FEnemy g_EnemyActorPoolList[dfENEMY_POOL_SIZE];
static unsigned int g_iUsedEnemyPoolCnt = 0;

static unsigned int g_iAliveEnemyCnt = 0;

static unsigned short g_iMaxEnemyTypeCount = 0;

void MoveToLocation(FEnemy* const pEnemy);
void SetTargetLocation(FEnemy* const pEnemy);

void AllocEnemyDatas(const unsigned short iMaxEnemyTypeCount) {
	g_iMaxEnemyTypeCount = iMaxEnemyTypeCount;

	g_pEnemyDatas = (FEnemy*)malloc(sizeof(FEnemy) * g_iMaxEnemyTypeCount);
}

void DeallocEnemyDatas() {
	free(g_pEnemyDatas);
}

void LoadEnemyInformation(char* const sBuffer) {
	static unsigned short iLoadedCnt = 0;

	if (sBuffer) {
		if (iLoadedCnt >= g_iMaxEnemyTypeCount)
			return;

		ReadInt16(sBuffer, "Type", (short*)&g_pEnemyDatas[iLoadedCnt].m_iType);
		ReadInt16(sBuffer, "HP", (short*)&g_pEnemyDatas[iLoadedCnt].m_iHP);
		ReadInt16(sBuffer, "XPosMoveSpeed", (short*)&g_pEnemyDatas[iLoadedCnt].m_iXPosMoveSpeed);

		ReadInt32(sBuffer, "MovementDelayTime", (int*)&g_pEnemyDatas[iLoadedCnt].m_iMovementDelayTime);
		ReadInt32(sBuffer, "FireDelayTime", (int*)&g_pEnemyDatas[iLoadedCnt].m_iFireDelayTime);

		ReadString(sBuffer, "Sprite", g_pEnemyDatas[iLoadedCnt].m_sSprite, ENEMY_SPRITE_WIDTH);

		iLoadedCnt++;
	}
}

void ClearEnemyPoolList() {
	g_iAliveEnemyCnt = 0;
	g_iUsedEnemyPoolCnt = 0;
	memset(g_EnemyActorPoolList, 0, sizeof(FEnemy) * dfENEMY_POOL_SIZE);
}

void AllocEnemyToPool(const unsigned short iActorType, const unsigned short iX, const unsigned short iY) {
	if (g_pEnemyDatas) {
		for (unsigned short i = 0; i < g_iMaxEnemyTypeCount; i++) {
			if (g_pEnemyDatas[i].m_iType == iActorType) {
				g_EnemyActorPoolList[g_iUsedEnemyPoolCnt].m_iX = iX;
				g_EnemyActorPoolList[g_iUsedEnemyPoolCnt].m_iY = iY;

				g_EnemyActorPoolList[g_iUsedEnemyPoolCnt].m_iHP = g_pEnemyDatas[i].m_iHP;
				g_EnemyActorPoolList[g_iUsedEnemyPoolCnt].m_iType = g_pEnemyDatas[i].m_iType;
				g_EnemyActorPoolList[g_iUsedEnemyPoolCnt].m_iXPosMoveSpeed = g_pEnemyDatas[i].m_iXPosMoveSpeed;

				g_EnemyActorPoolList[g_iUsedEnemyPoolCnt].m_iLastMovementTime = 0;
				g_EnemyActorPoolList[g_iUsedEnemyPoolCnt].m_iLastFireTime = 0;

				g_EnemyActorPoolList[g_iUsedEnemyPoolCnt].m_iMovementDelayTime = g_pEnemyDatas[i].m_iMovementDelayTime;
				g_EnemyActorPoolList[g_iUsedEnemyPoolCnt].m_iFireDelayTime= g_pEnemyDatas[i].m_iFireDelayTime;

				SetTargetLocation(&g_EnemyActorPoolList[g_iUsedEnemyPoolCnt]);

				memcpy(g_EnemyActorPoolList[g_iUsedEnemyPoolCnt].m_sSprite, g_pEnemyDatas[i].m_sSprite, ENEMY_SPRITE_WIDTH);
				g_EnemyActorPoolList[g_iUsedEnemyPoolCnt].m_iSpriteWidth = (unsigned short)strlen(g_EnemyActorPoolList[g_iUsedEnemyPoolCnt].m_sSprite);

				g_EnemyActorPoolList[g_iUsedEnemyPoolCnt].m_bIsVisible = true;

				g_iUsedEnemyPoolCnt++;
				g_iAliveEnemyCnt++;
			}
		}
	}
	else
		ChangeMainLoopRunState(false); // error
}

// in game logic

bool IsEnemiesAlive() {
	return (g_iAliveEnemyCnt > 0);
}

void MoveToLocation(FEnemy* const pEnemy) {
	const unsigned short iXDistanceRemainingToTarget = (unsigned short)abs(pEnemy->m_iX - pEnemy->m_iMoveToX);
	const unsigned short iXPosMoveSpeed = (iXDistanceRemainingToTarget > pEnemy->m_iXPosMoveSpeed) ? pEnemy->m_iXPosMoveSpeed : iXDistanceRemainingToTarget;

	if (pEnemy->m_iX < pEnemy->m_iMoveToX)
		pEnemy->m_iX += iXPosMoveSpeed;

	if (pEnemy->m_iX > pEnemy->m_iMoveToX)
		pEnemy->m_iX -= iXPosMoveSpeed;

	if (pEnemy->m_iY < pEnemy->m_iMoveToY)
		pEnemy->m_iY++;

	if (pEnemy->m_iY > pEnemy->m_iMoveToY)
		pEnemy->m_iY--;
}

bool IsMoving(const FEnemy* const pEnemy) {
	if (pEnemy->m_iX != pEnemy->m_iMoveToX || pEnemy->m_iY != pEnemy->m_iMoveToY)
		return true;

	return false;
}

void SetTargetLocation(FEnemy* const pEnemy) {
	const short iRandX = (rand() % (dfSCREEN_WIDTH - 4)) + 2;
	const short iRandY = rand() % (dfSCREEN_HEIGHT / 2);

	pEnemy->m_iMoveToX = iRandX;
	pEnemy->m_iMoveToY = iRandY;
}

_inline void EnemyMovementLogic(const DWORD iCurrentTime, const int iIndex) {
	if (iCurrentTime - g_EnemyActorPoolList[iIndex].m_iLastMovementTime >= g_EnemyActorPoolList[iIndex].m_iMovementDelayTime) {
		if (!IsMoving(&g_EnemyActorPoolList[iIndex]))
			SetTargetLocation(&g_EnemyActorPoolList[iIndex]);

		MoveToLocation(&g_EnemyActorPoolList[iIndex]);

		g_EnemyActorPoolList[iIndex].m_iLastMovementTime = iCurrentTime;
	}
}

_inline void EnemyFireLogic(const DWORD iCurrentTime, const int iIndex) {
	if (iCurrentTime - g_EnemyActorPoolList[iIndex].m_iLastFireTime >= g_EnemyActorPoolList[iIndex].m_iFireDelayTime) {
		Fire(0, g_EnemyActorPoolList[iIndex].m_iX, g_EnemyActorPoolList[iIndex].m_iY + 1, false);
		g_EnemyActorPoolList[iIndex].m_iLastFireTime = iCurrentTime;
	}
}

void EnemyLogic() {
	DWORD iCurrentTime = timeGetTime();

	for (unsigned int i = 0; i < g_iUsedEnemyPoolCnt; i++) {
		if (g_EnemyActorPoolList[i].m_bIsVisible) {
			EnemyMovementLogic(iCurrentTime, i);
			EnemyFireLogic(iCurrentTime, i);
		}
	}
}

bool EnemyCollisionLogic(const unsigned short iX, const unsigned short iY, const unsigned short iDamage) {
	for (unsigned int i = 0; i < g_iUsedEnemyPoolCnt; i++) {
		if (!g_EnemyActorPoolList[i].m_bIsVisible)
			continue;

		const short iEnemyLeft = g_EnemyActorPoolList[i].m_iX - g_EnemyActorPoolList[i].m_iSpriteWidth / 2;
		const short iEnemyRight = g_EnemyActorPoolList[i].m_iX + g_EnemyActorPoolList[i].m_iSpriteWidth / 2;

		if (iEnemyLeft <= iX && iEnemyRight >= iX && g_EnemyActorPoolList[i].m_iY == iY) {
			g_EnemyActorPoolList[i].m_iHP -= iDamage;

			if (g_EnemyActorPoolList[i].m_iHP <= 0) {
				g_EnemyActorPoolList[i].m_bIsVisible = false;
				g_iAliveEnemyCnt--;
			}
			return true;
		}
	}
	return false;
}

// render

void EnemyRendering() {
	for (unsigned int i = 0; i < g_iUsedEnemyPoolCnt; i++) {
		if (g_EnemyActorPoolList[i].m_bIsVisible)
			Sprite_DrawString(g_EnemyActorPoolList[i].m_iX, g_EnemyActorPoolList[i].m_iY, g_EnemyActorPoolList[i].m_sSprite, ESpriteAligment::E_Center);
	}
}