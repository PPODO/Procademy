#include <iostream>

int main() {
	char* p = (char*)malloc(100);

	free(p);

	*p = 0;

	return 0;
}