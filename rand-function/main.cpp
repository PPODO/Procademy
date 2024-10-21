#include <iostream>

int g_iSeed = 1;

void my_srand(const int iNewSeed) {
	g_iSeed = iNewSeed;
}

int my_rand() {
	g_iSeed = ((g_iSeed * 0x343FD) + 0x269EC3);

	return ((g_iSeed >> 16) & 0x7FFF);
}

int main() {
	srand(time(nullptr));
	my_srand(time(nullptr));

	std::cout << "Test Case 1\n";

	std::cout << "CRT Rand : " << rand() << std::endl;
	std::cout << "My Rand : " << my_rand() << std::endl;

	std::cout << std::endl << std::endl;

	std::cout << "Test Case 2\n";

	std::cout << "CRT Rand : " << rand() << std::endl;
	std::cout << "My Rand : " << my_rand() << std::endl;

	std::cout << std::endl << std::endl;

	std::cout << "Test Case 3\n";

	std::cout << "CRT Rand : " << rand() << std::endl;
	std::cout << "My Rand : " << my_rand() << std::endl;

	return 0;
}