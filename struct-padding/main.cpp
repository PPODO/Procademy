#include <iostream>

struct stDATA {
	char a;  // 1바이트 후 패딩
	short b; // 2바이트 채우기.

	int c; // 4바이트

	char e; // 1바이트 이후, 1바이트 패딩(가장 큰 사이즈가 2바이트이기 때문에 1바이트만 패딩)
};

int main() {

	std::cout << sizeof(stDATA) << std::endl;

	return 0;
}