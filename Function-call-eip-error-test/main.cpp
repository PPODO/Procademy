#include <iostream>

void Test() {
	int x = 10;
	int* p = &x;

	*(p + 3) = 0;
}

int main() {
	Test();

	return 0;
}