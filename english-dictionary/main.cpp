#include <iostream>

#define WORD_COUNT 10

char g_Dictionary[WORD_COUNT][2][50] =
{
	{ "i", "��" },
	{ "love", "�����" },
	{ "you", "��" },
	{ "miss", "�׸���" },
	{ "hate", "�����Ѵ�" },
	{ "thank", "����" },
	{ "so", "�ſ�" },
	{ "tried", "���ƴ�" },
	{ "prove", "�ſ�" },
	{ "it", "�װ�" }
};

void Dictionary(char* const string) {
	char* pCachedString = string;

	while (true) {
		char* pContext = nullptr;
		char* pResult = strtok_s(pCachedString, " ", &pContext);
		pCachedString = pContext;

		bool bFinded = false;
		for (int i = 0; i < WORD_COUNT; i++) {
			if (strcmp(pResult, g_Dictionary[i][0]) == 0) {
				bFinded = true;
				std::cout << g_Dictionary[i][1] << ", ";
			}
		}

		if (!bFinded)
			std::cout << "������ �������� �ʴ� �ܾ��Դϴ�. ";
		
		if (pContext && strcmp(pContext, "\0") == 0)
			break;
	}
	std::cout << std::endl << std::endl;
}

int main() {
	while (true) {
		std::cout << "128�� �̳��� ���ܾ �Է��� �ּ���.\n";

		char inputString[128];
		gets_s(inputString, 128);

		std::cout << std::endl;

		Dictionary(inputString);
	}
	return 0;
}