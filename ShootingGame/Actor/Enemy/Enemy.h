#pragma once

#define ENEMY_SPRITE_WIDTH 5

struct FEnemy {
	unsigned short m_iType;

	unsigned short m_iX;
	unsigned short m_iY;

	short m_iHP;

	unsigned short m_iXPosMoveSpeed;

	unsigned short m_iMoveToX;
	unsigned short m_iMoveToY;

	bool m_bIsVisible;

	char m_sSprite[ENEMY_SPRITE_WIDTH];
	unsigned short m_iSpriteWidth;

	unsigned int m_iLastMovementTime;
	unsigned int m_iMovementDelayTime;

	unsigned int m_iLastFireTime;
	unsigned int m_iFireDelayTime;
};

void AllocEnemyDatas(const unsigned short iMaxEnemyTypeCount);
void DeallocEnemyDatas();

void LoadEnemyInformation(char* const sBuffer);

void ClearEnemyPoolList();

void AllocEnemyToPool(const unsigned short iActorType, const unsigned short iX, const unsigned short iY);

bool IsEnemiesAlive();

void EnemyLogic();
bool EnemyCollisionLogic(const unsigned short iX, const unsigned short iY, const unsigned short iDamage);

void EnemyRendering();