#include "Enemy.h"
#include <stdlib.h>
#include <memory.h>
#include "../../Console/Console.h"
#include "../../DataParse/DataParse.h"

#define dfENEMY_POOL_SIZE 100

static FEnemy* g_pEnemyDatas = NULL;

static FEnemy g_EnemyActorPoolList[dfENEMY_POOL_SIZE];
static unsigned int g_iEnemyPoolCnt = 0;

static unsigned short g_iMaxEnemyTypeCount = 0;

void AllocEnemyDatas(const unsigned short iMaxEnemyTypeCount) {
	g_iMaxEnemyTypeCount = iMaxEnemyTypeCount;

	g_pEnemyDatas = (FEnemy*)malloc(sizeof(FEnemy) * g_iMaxEnemyTypeCount);
}

void DeallocEnemyDatas() {
	if (g_pEnemyDatas)
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
		ReadString(sBuffer, "Sprite", g_pEnemyDatas[iLoadedCnt].m_sSprite, ENEMY_SPRITE_WIDTH);

		iLoadedCnt++;
	}
}

void ClearEnemyPoolList() {
	g_iEnemyPoolCnt = 0;
	memset(g_EnemyActorPoolList, 0, sizeof(FEnemy) * dfENEMY_POOL_SIZE);
}

void AllocEnemyToPool(const unsigned short iActorType, const unsigned short iX, const unsigned short iY) {
	if (g_pEnemyDatas) {
		for (unsigned short i = 0; i < g_iMaxEnemyTypeCount; i++) {
			if (g_pEnemyDatas[i].m_iType == iActorType) {
				g_EnemyActorPoolList[g_iEnemyPoolCnt].m_iX = iX;
				g_EnemyActorPoolList[g_iEnemyPoolCnt].m_iY = iY;

				g_EnemyActorPoolList[g_iEnemyPoolCnt].m_iHP = g_pEnemyDatas[i].m_iHP;
				g_EnemyActorPoolList[g_iEnemyPoolCnt].m_iType = g_pEnemyDatas[i].m_iType;
				g_EnemyActorPoolList[g_iEnemyPoolCnt].m_iXPosMoveSpeed = g_pEnemyDatas[i].m_iXPosMoveSpeed;

				memcpy(g_EnemyActorPoolList[g_iEnemyPoolCnt].m_sSprite, g_pEnemyDatas[i].m_sSprite, ENEMY_SPRITE_WIDTH);

				g_EnemyActorPoolList[g_iEnemyPoolCnt].m_bIsVisible = true;

				g_iEnemyPoolCnt++;
			}
		}
	}
}

void EnemyRendering() {
	for (unsigned int i = 0; i < g_iEnemyPoolCnt; i++) {
		if (g_EnemyActorPoolList[i].m_bIsVisible)
			Sprite_DrawString(g_EnemyActorPoolList[i].m_iX, g_EnemyActorPoolList[i].m_iY, g_EnemyActorPoolList[i].m_sSprite, ESpriteAligment::E_Center);
	}
}