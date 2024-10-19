#include <iostream>

int main() {
	int a = 0;

	switch (a) {
	case 5:
		a = 10;
		break;
	case 6:
		a = 20;
		break;
	case 7:
		a = 30;
		break;
	case 4:
		a = 40;
		break;
	case 3:
		a = 50;
		break;
	case 2:
		a = 60;
		break;
	case 1:
		a = 70;
		break;
	}

	std::cout << a << std::endl;
	return 0;
}