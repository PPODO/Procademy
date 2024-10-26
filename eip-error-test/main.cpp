#include <iostream>

void Test3() {
	int a = 2;
	int* p = &a;

	*(p + 3) = 0;
}

void Test2() {
	int a = 10;

	Test3();

	printf("Test2 : %d", a);
}

void Test1() {
	int a = 5;
	int b = 10;

	Test2();

	printf("%d, %d", a, b);
}

int main() {
	Test1();

	return 0;
}