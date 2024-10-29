#include <iostream>

void Test() {
	static int g_A = rand();

}

int main() {
	Test();
	Test();
	Test();

	return 0;
}