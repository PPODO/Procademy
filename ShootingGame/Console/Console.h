#pragma once
#ifndef __CONSOLE__
#define __CONSOLE__

#define dfSCREEN_WIDTH		81		// ÄÜ¼Ö °¡·Î 80Ä­ + NULL
#define dfSCREEN_HEIGHT		24		// ÄÜ¼Ö ¼¼·Î 24Ä­

enum ESpriteAligment {
	E_Left,
	E_Center,
	E_Right
};

void cs_Initial(void);

void cs_MoveCursor(int iPosX, int iPosY);

void cs_ClearScreen(void);


void Buffer_Flip(void);
void Buffer_Clear(void);
void Sprite_DrawCharacter(int iX, int iY, char chSprite);
void Sprite_DrawString(const int iX, const int iY, const char* const strSprite, const ESpriteAligment aligment);

void ChangeMainLoopRunState(const bool bNewState);
inline bool GetMainLoopRunState();

#endif