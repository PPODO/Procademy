#include <iostream>

#define BIT 8

int main() {

	unsigned short iValue = 0;
	while (true) {
		std::cout << "비트 위치 : ";

		unsigned short iBitOffset;
		std::cin >> iBitOffset;
		--iBitOffset;

		std::cout << "OFF/ON [0, 1] : ";
		bool bBitFlag;
		std::cin >> bBitFlag;

		if (bBitFlag)
			iValue |= (1 << iBitOffset);
		else
			iValue &= ~(1 << iBitOffset);

		for (int i = (sizeof(uint16_t) * BIT) - 1; i >= 0; i--) {
			std::cout << (i + 1) << " 번 Bit : ";

			if (iValue & (1 << i))
				std::cout << "ON\n";
			else
				std::cout << "OFF\n";
		}

		std::cout << std::endl;
	}

	return 0;
}