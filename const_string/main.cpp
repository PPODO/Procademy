#include <iostream>

int main() {
	char buffer1[] = "test string 1. hello world!";

	const char* buffer2 = "test string 2. hello world!";

	printf("%s\n", buffer1);
	printf("%s\n", buffer2);
	return 0;
}