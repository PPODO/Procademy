#include <iostream>

struct stDATA {
	char a;  // 1����Ʈ �� �е�
	short b; // 2����Ʈ ä���.

	int c; // 4����Ʈ

	char e; // 1����Ʈ ����, 1����Ʈ �е�(���� ū ����� 2����Ʈ�̱� ������ 1����Ʈ�� �е�)
};

int main() {

	std::cout << sizeof(stDATA) << std::endl;

	return 0;
}