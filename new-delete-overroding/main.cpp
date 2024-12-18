#include <iostream>
#include "memory_leak.h"
#include "List.h"

class C {
public:
	C() {
		printf("Hello");
	}

	~C() {
		printf("Delete");
	}
};

int main() {
	auto pPtr = new C[5];

	delete[] pPtr;
	return 0;
}