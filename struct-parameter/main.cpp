#include <iostream>

struct stDATA {
	int a;
	int b;
	int c;

	char buffer[128];
};

void Test(stDATA data) {
	data.b = 10;

}

int main() {
	stDATA data;
	data.a = 0;
	data.b = 1;
	data.c = 2;

	Test(data);

	return 0;
}