#pragma once

struct FPlayer {
	unsigned short m_iX;
	unsigned short m_iY;

	unsigned short m_iHP;


};

void InitializePlayerInformation();

void MoveX(const short iX);
void MoveY(const short iY);

void PlayerRendering();