#include <iostream>

#define WORD_COUNT 10

char g_Dictionary[WORD_COUNT][2][50] =
{
	{ "i", "나" },
	{ "love", "사랑해" },
	{ "you", "너" },
	{ "miss", "그립다" },
	{ "hate", "혐오한다" },
	{ "thank", "고맙다" },
	{ "so", "매우" },
	{ "tried", "지쳤다" },
	{ "prove", "매우" },
	{ "it", "그걸" }
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
			std::cout << "사전에 존재하지 않는 단어입니다. ";
		
		if (pContext && strcmp(pContext, "\0") == 0)
			break;
	}
	std::cout << std::endl << std::endl;
}

int main() {
	while (true) {
		std::cout << "128자 이내로 영단어를 입력해 주세요.\n";

		char inputString[128];
		gets_s(inputString, 128);

		std::cout << std::endl;

		Dictionary(inputString);
	}
	return 0;
}