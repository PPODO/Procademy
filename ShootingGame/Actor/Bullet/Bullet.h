#pragma once

struct FBullet {
	unsigned short m_iType;

	unsigned short m_iX;
	unsigned short m_iY;

	unsigned short m_iXPosSpeed;
	unsigned short m_iYPosSpeed;

	unsigned short m_iDamage;

	bool m_bIsPlayerOwned;
	bool m_bIsVisible;

	unsigned int m_iLastMovementTime;
	unsigned int m_iMovementDelayTime;

	char m_cSprite;
};

void AllocBulletDatas(const unsigned short iMaxBulletTypeCount);
void DeallocBulletDatas();

void ClearBulletPoolList();

void LoadBulletInformation(char* const sBuffer);

void Fire(const unsigned short iBulletType, const unsigned short iX, const unsigned short iY, const bool bIsPlayerRequest);

void BulletLogic();

void BulletRendering();