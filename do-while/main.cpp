#include <iostream>

#define WORK(a, b) \
do{			\
	(a + b);	\
}while(0)

void Function() {

	do {
		// 조건 검사 실패시
		if (0) {
			break;
		}

		// 조건 검사 실패시
		if (0) {
			break;
		}

		// 조건 검사 실패시
		if (0) {
			break;
		}

		// 조건 검사 실패시
		if (0) {
			break;
		}

		// 메인 로직
		return;
	} while (0);
	
	// 작업이 실패했다고 판단. 초기화 진행!
}

int main() {

	if (1)
		WORK(1, 2);
	else
		printf("Hello world!");

	return 0;
}