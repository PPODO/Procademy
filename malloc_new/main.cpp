#include <iostream>

int main() {
	char* buffer = (char*)malloc(20);
	char* buffer2 = (char*)malloc(20);

	buffer[21] = '0';

	std::cout << std::endl;

	free(buffer2);
	free(buffer);
	return 0;
}