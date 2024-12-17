#include <iostream>
#include <Windows.h>
#include <conio.h>

#define SCREEN_WIDTH 75
#define MAX_OBJECT_COUNT 20

class CBaseObject {
protected:
	int m_iX;
	bool m_bIsActive;
	
public:
	CBaseObject() : m_iX(), m_bIsActive(true) {};

	inline bool IsAlive() const { return m_bIsActive; }

public:
	virtual void Update() = 0;
	virtual void Render() = 0;

};

class COneStar : public CBaseObject {
public:
	virtual void Update() override final {
		if (m_iX > SCREEN_WIDTH) {
			m_bIsActive = false;
			return;
		}
		m_iX++;
	}

	virtual void Render() override final {
		for (int i = 0; i < m_iX; i++)
			std::cout << ' ';

		std::cout << "*";
	}

};

class CTwoStar : public CBaseObject {
public:
	virtual void Update() override final {
		if (m_iX > SCREEN_WIDTH - 1) {
			m_bIsActive = false;
			return;
		}
		m_iX += 2;
	}

	virtual void Render() override final {
		for (int i = 0; i < m_iX; i++)
			std::cout << ' ';

		std::cout << "**";
	}

};

class CThreeStar : public CBaseObject {
public:
	virtual void Update() override final {
		if (m_iX > SCREEN_WIDTH - 2) {
			m_bIsActive = false;
			return;
		}

		m_iX += 3;;
	}

	virtual void Render() override final {
		for (int i = 0; i < m_iX; i++)
			std::cout << ' ';

		std::cout << "***";
	}

};

CBaseObject* g_pBaseObjects[MAX_OBJECT_COUNT] = { nullptr };

void KeyProcess() {
	if (_kbhit() != 0) {
		int iKeyInput = _getch();

		CBaseObject** pObjectIndex = nullptr;
		for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
			if (!g_pBaseObjects[i]) {
				pObjectIndex = &g_pBaseObjects[i];
				break;
			}
		}

		if (pObjectIndex) {
			switch (iKeyInput) {
			case '1':
				*pObjectIndex = new COneStar;
				break;
			case '2':
				*pObjectIndex = new CTwoStar;
				break;
			case '3':
				*pObjectIndex = new CThreeStar;
				break;
			}
		}
	}
}

void Update() {
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		if (g_pBaseObjects[i]) {
			if (g_pBaseObjects[i]->IsAlive()) 
				g_pBaseObjects[i]->Update();
			else {
				delete g_pBaseObjects[i];
				g_pBaseObjects[i] = nullptr;
			}
		}
	}
}

void Render() {
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		if (g_pBaseObjects[i] && g_pBaseObjects[i]->IsAlive())
			g_pBaseObjects[i]->Render();

		std::cout << '\n';
	}
}

int main() {
	while (true) {
		KeyProcess();

		Update();

		system("cls");

		Render();

		Sleep(50);
	}

	return 0;
}