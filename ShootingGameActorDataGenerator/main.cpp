#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>

int main() {
	bool bLoopRunState = true;

	while (bLoopRunState) {
		std::cout << "1. 플레이어 데이터 생성\n";
		std::cout << "2. 적 데이터 생성\n";
		std::cout << "3. 종료\n";

		std::cout << "\n";

		int iInput = _getch();

		switch (iInput) {
		case '1':
		{
			std::string sFileName;
			std::cout << "파일 이름을 입력해주세요.\n";
			std::cin >> sFileName;

			std::ofstream outStream(sFileName + ".dat", std::ios::out | std::ios::binary);
			if (outStream.is_open()) {

				outStream << "20";

				outStream.close();
			}
			else {
				std::cout << "파일 생성 실패! 5초 뒤 처음 화면으로 돌아갑니다.\n";
				Sleep(5000);
				system("cls");
				continue;
			}
		}
			break;
		case '2':

			break;
		case 'q':
			bLoopRunState = false;
			break;
		}
	}
	return 0;
}