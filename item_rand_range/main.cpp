#include <iostream>
#include <conio.h>

#define ITEM_NAME_LENGTH 50

struct s_Item {
public:
	char m_sItemName[ITEM_NAME_LENGTH];
	int m_iRange;

public:
	s_Item() {
		memset(m_sItemName, 0, ITEM_NAME_LENGTH);
		m_iRange = 0;
	}

	s_Item(const char* const sItemName, const int iRange) : m_iRange(iRange) {
		strcpy_s(m_sItemName, ITEM_NAME_LENGTH, sItemName);
	}
};

s_Item g_RandTable[] = 
{ 
	{ "칼", 300 },
	{ "방패", 25 }, 
	{ "물약", 25 },
	{ "모자", 10 },
	{ "레어레어레어신발", 1 },
};

int iTryCount = 0;

void Random() {
	const int iTableSize = sizeof(g_RandTable) / sizeof(s_Item);

	int iTotalPoss = 0;
	for (int i = 0; i < iTableSize; i++)
		iTotalPoss += g_RandTable[i].m_iRange;

	int iNumber = rand() % iTotalPoss + 1;

	int iCurrent = 0;
	for (int i = 0; i < iTableSize; i++) {
		iCurrent += g_RandTable[i].m_iRange;
		if (iNumber <= iCurrent) {
			printf("%d : %s, %d / %d\n", iTryCount, g_RandTable[i].m_sItemName, g_RandTable[i].m_iRange, iTotalPoss);
			return;
		}
	}
}

int main() {
	while (true) {
		_getch();
		Random();
	}
	return 0;
}