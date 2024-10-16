#include <iostream>

#define BIT 8

int main() {
	unsigned char iValue = 40;	
	std::cout << iValue << " 의 바이너리 : ";

	for (int i = (sizeof(unsigned char) * BIT) - 1; i >= 0; i--) {
		if (iValue & (1 << i))
			std::cout << '1';
		else
			std::cout << '0';
	}


	return 0;
}