#include <iostream>

int main() {
	int* p = new int;
	*p = 5;
	free(p);

	printf("%d", *p);

	return 0;
}