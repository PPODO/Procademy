#include "Player.h"
#include "../../Console/Console.h"

FPlayer g_PlayerInformaiton;

void InitializePlayerInformation(){
	g_PlayerInformaiton.m_iX = 40;
	g_PlayerInformaiton.m_iY = 12;

	g_PlayerInformaiton.m_iHP = 100;
}

void MoveX(const short iX) {
	const short iRequestXPos = (short)g_PlayerInformaiton.m_iX + iX;
	if (iRequestXPos >= 0 && iRequestXPos < (dfSCREEN_WIDTH - 1))
		g_PlayerInformaiton.m_iX = iRequestXPos;
}

void MoveY(const short iY) {
	const short iRequestYPos = (short)g_PlayerInformaiton.m_iY + iY;
	if (iRequestYPos >= 0 && iRequestYPos < dfSCREEN_HEIGHT)
		g_PlayerInformaiton.m_iY = iRequestYPos;
}

void PlayerRendering() {
	Sprite_DrawString(g_PlayerInformaiton.m_iX, g_PlayerInformaiton.m_iY, "-O-", ESpriteAligment::E_Center);
}