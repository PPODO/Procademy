#pragma once

#define ENEMY_SPRITE_WIDTH 5

struct FEnemy {
	unsigned short m_iX;
	unsigned short m_iY;

	unsigned short m_iHP;

	unsigned short m_iXPosMoveSpeed;

	char m_sSprite[ENEMY_SPRITE_WIDTH];
};

void LoadEnemyInformation(char* const sBuffer);