#include <iostream>

struct stDATA {
	int a;
	int b;
	int c;
	char buffer[128];
};

stDATA Test() {
	stDATA data;

	data.a = 1;
	data.b = 1;
	data.c = 1;

	memset(data.buffer, 0, 128);

	return data;
}

int main() {
	stDATA data = Test();

	printf("%d, %d, %d\n", data.a, data.b, data.c);
	return 0;
}