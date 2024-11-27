#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "Player.h"
#include "../../Console/Console.h"
#include "../../DataParse/DataParse.h"

static FPlayer g_CachedInitPlayerInformation;
static FPlayer g_CurrentPlayerInformaiton;

void LoadPlayerInformation(char* const sBuffer) {
	if (sBuffer) {
		ReadInt16(sBuffer, "HP", (short*)&g_CachedInitPlayerInformation.m_iHP);
		ReadInt16(sBuffer, "XPosMoveSpeed", (short*)&g_CachedInitPlayerInformation.m_iXPosMoveSpeed);
	}
}

void InitializePlayerInformation() {
	g_CurrentPlayerInformaiton.m_iX;
	g_CurrentPlayerInformaiton.m_iY;

	g_CurrentPlayerInformaiton.m_iHP = g_CachedInitPlayerInformation.m_iHP;

	g_CurrentPlayerInformaiton.m_iXPosMoveSpeed = g_CachedInitPlayerInformation.m_iXPosMoveSpeed;
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

void PlayerRendering() {
	Sprite_DrawString(g_CurrentPlayerInformaiton.m_iX, g_CurrentPlayerInformaiton.m_iY, "-<->-", ESpriteAligment::E_Center);
}