#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>

int main() {
	bool bLoopRunState = true;

	while (bLoopRunState) {
		std::cout << "1. �÷��̾� ������ ����\n";
		std::cout << "2. �� ������ ����\n";
		std::cout << "3. ����\n";

		std::cout << "\n";

		int iInput = _getch();

		switch (iInput) {
		case '1':
		{
			std::string sFileName;
			std::cout << "���� �̸��� �Է����ּ���.\n";
			std::cin >> sFileName;

			std::ofstream outStream(sFileName + ".dat", std::ios::out | std::ios::binary);
			if (outStream.is_open()) {

				outStream << "20";

				outStream.close();
			}
			else {
				std::cout << "���� ���� ����! 5�� �� ó�� ȭ������ ���ư��ϴ�.\n";
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