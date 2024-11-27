#pragma once

struct FPlayer {
	unsigned short m_iX;
	unsigned short m_iY;

	unsigned short m_iHP;

	unsigned short m_iXPosMoveSpeed;
};

void LoadPlayerInformation(char* const sBuffer);

void InitializePlayerInformation();

void MoveX(const short iX);
void MoveY(const short iY);

void PlayerRendering();