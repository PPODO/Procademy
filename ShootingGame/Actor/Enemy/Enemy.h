#pragma once

#define ENEMY_SPRITE_WIDTH 5

struct FEnemy {
	unsigned short m_iType;

	unsigned short m_iX;
	unsigned short m_iY;

	unsigned short m_iHP;

	unsigned short m_iXPosMoveSpeed;

	char m_sSprite[ENEMY_SPRITE_WIDTH];

	bool m_bIsVisible;
};

void AllocEnemyDatas(const unsigned short iMaxEnemyTypeCount);
void DeallocEnemyDatas();

void LoadEnemyInformation(char* const sBuffer);

void ClearEnemyPoolList();

void AllocEnemyToPool(const unsigned short iActorType, const unsigned short iX, const unsigned short iY);

void EnemyRendering();