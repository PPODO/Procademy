#include <iostream>
#include <Windows.h>

void Test2() {
	int temp = 0;
	int* pEBP = (&temp) + 2;
	unsigned long cachedEBP = *pEBP;
	
 	int a = 0;
	int* p = &a;

	// 공격 로직
	if (*pEBP != cachedEBP)
		DebugBreak();


	// 데미지 로직
	if (*pEBP != cachedEBP)
		DebugBreak();


	// 스킬 이펙트 로직
	if (*pEBP != cachedEBP)
		DebugBreak();


	*(p + 3) = 0;
	if (*pEBP != cachedEBP)
		DebugBreak();
}

void Test1() {
	int a = 0;
	int b = 0;

	Test2();

	printf("%d %d", a, b);
}

int main() {
	Test1();

	return 0;
}