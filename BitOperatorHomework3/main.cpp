#include <iostream>

#define BIT 8

int main() {
	unsigned int iValue = 0;

	while (true) {
		unsigned short iOffset;
		std::cout << "위치 (1 ~ 4) : ";
		std::cin >> iOffset;

		unsigned int iInputValue;
		std::cout << "값 [0 ~ 255] : ";
		scanf_s("%d", &iInputValue);

		iValue &= ~(0xff << ((iOffset - 1) * BIT));
		iValue |= (iInputValue << ((iOffset - 1) * BIT));

		for (int i = 0; i < sizeof(unsigned int); i++) {

			printf("%d 번째 바이트 값 : %d\n", (i + 1), (unsigned char)(iValue >> (i * BIT)));
		}

		printf("전체 4바이트 값 : 0x%p\n\n", iValue);
	}

	return 0;
}