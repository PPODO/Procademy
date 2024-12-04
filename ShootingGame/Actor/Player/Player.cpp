#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <Windows.h>
#include "Player.h"
#include "../Bullet/Bullet.h"
#include "../../Console/Console.h"
#include "../../Game/GameManager.h"
#include "../../DataParse/DataParse.h"

static FPlayer g_CachedInitPlayerInformation;
static FPlayer g_CurrentPlayerInformaiton;

void LoadPlayerInformation(char* const sBuffer) {
	if (sBuffer) {
		ReadInt16(sBuffer, "HP", (short*)&g_CachedInitPlayerInformation.m_iHP);
		ReadInt16(sBuffer, "XPosMoveSpeed", (short*)&g_CachedInitPlayerInformation.m_iXPosMoveSpeed);

		ReadString(sBuffer, "Sprite", g_CachedInitPlayerInformation.m_sSprite, PLAYER_SPRITE_WIDTH);

		ReadInt32(sBuffer, "FireDelayTime", (int*)&g_CachedInitPlayerInformation.m_iFireDelayTime);
	}
}

void InitializePlayerInformation(const short iX, const short iY) {
	g_CurrentPlayerInformaiton.m_iX = iX;
	g_CurrentPlayerInformaiton.m_iY = iY;

	g_CurrentPlayerInformaiton.m_iHP = g_CachedInitPlayerInformation.m_iHP;

	g_CurrentPlayerInformaiton.m_iXPosMoveSpeed = g_CachedInitPlayerInformation.m_iXPosMoveSpeed;

	g_CurrentPlayerInformaiton.m_iFireDelayTime = g_CachedInitPlayerInformation.m_iFireDelayTime;

	memcpy(g_CurrentPlayerInformaiton.m_sSprite, g_CachedInitPlayerInformation.m_sSprite, PLAYER_SPRITE_WIDTH);
	g_CurrentPlayerInformaiton.m_iSpriteWidth = (unsigned short) strlen(g_CurrentPlayerInformaiton.m_sSprite);
}

void MoveX(const short iX) {
	const short iRequestXPos = (short)g_CurrentPlayerInformaiton.m_iX + (iX * g_CurrentPlayerInformaiton.m_iXPosMoveSpeed);

	if (iRequestXPos >= 0 && iRequestXPos < (dfSCREEN_WIDTH - 1))
		g_CurrentPlayerInformaiton.m_iX = iRequestXPos;
}

void MoveY(const short iY) {
	const short iRequestYPos = (short)g_CurrentPlayerInformaiton.m_iY + iY;

	if (iRequestYPos >= (dfSCREEN_HEIGHT / 2) && iRequestYPos < dfSCREEN_HEIGHT)
		g_CurrentPlayerInformaiton.m_iY = iRequestYPos;
}

bool PlayerCollisionLogic(const unsigned short iX, const unsigned short iY, const unsigned short iDamage) {
	if (g_CurrentPlayerInformaiton.m_iX - (g_CurrentPlayerInformaiton.m_iSpriteWidth / 2) <= iX &&
		g_CurrentPlayerInformaiton.m_iX + (g_CurrentPlayerInformaiton.m_iSpriteWidth / 2) >= iX &&
		g_CurrentPlayerInformaiton.m_iY == iY) {
		short iCachedNewHP = g_CurrentPlayerInformaiton.m_iHP -= iDamage;
		if (iCachedNewHP <= 0)
			ChangeScene(ESceneType::E_GAMEOVER);
		else
			g_CurrentPlayerInformaiton.m_iHP = iCachedNewHP;
		
		return true;
	}
	return false;
}

void PlayerFire() {
	static DWORD prevFireTime = 0;
	
	DWORD currentTime = timeGetTime();
	if (currentTime - prevFireTime >= g_CurrentPlayerInformaiton.m_iFireDelayTime) {
		Fire(0, g_CurrentPlayerInformaiton.m_iX, g_CurrentPlayerInformaiton.m_iY, true);

		prevFireTime = currentTime;
	}
}

void PlayerRendering() {
	Sprite_DrawString(g_CurrentPlayerInformaiton.m_iX, g_CurrentPlayerInformaiton.m_iY, g_CurrentPlayerInformaiton.m_sSprite, ESpriteAligment::E_Center);
}