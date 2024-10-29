#include <iostream>

void __stdcall Test1(int a, int b, int c) {
	int x = a;
	int y = b;
	int z = c;

	z = x + y + z;
}

void __cdecl Test2(int a, int b, int c ) {
	int x = a;
	int y = b;
	int z = c;

	z = x + y + z;
}

int main() {
	Test1(10, 20, 30);
	int a = 0xffffffff;
	Test2(10, 20, 30);

	return 0;
}