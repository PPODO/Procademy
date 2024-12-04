#pragma once

#define PLAYER_SPRITE_WIDTH 5

struct FPlayer {
	unsigned short m_iX;
	unsigned short m_iY;

	unsigned short m_iHP;

	unsigned short m_iXPosMoveSpeed;

	unsigned int m_iFireDelayTime;

	char m_sSprite[PLAYER_SPRITE_WIDTH];
	unsigned short m_iSpriteWidth;
};

void LoadPlayerInformation(char* const sBuffer);

void InitializePlayerInformation(const short iX, const short iY);

void MoveX(const short iX);
void MoveY(const short iY);

bool PlayerCollisionLogic(const unsigned short iX, const unsigned short iY, const unsigned short iDamage);

void PlayerFire();

void PlayerRendering();