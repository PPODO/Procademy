#include <iostream>

#define WORK(a, b) \
do{			\
	(a + b);	\
}while(0)

void Function() {

	do {
		// ���� �˻� ���н�
		if (0) {
			break;
		}

		// ���� �˻� ���н�
		if (0) {
			break;
		}

		// ���� �˻� ���н�
		if (0) {
			break;
		}

		// ���� �˻� ���н�
		if (0) {
			break;
		}

		// ���� ����
		return;
	} while (0);
	
	// �۾��� �����ߴٰ� �Ǵ�. �ʱ�ȭ ����!
}

int main() {

	if (1)
		WORK(1, 2);
	else
		printf("Hello world!");

	return 0;
}