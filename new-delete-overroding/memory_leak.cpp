#include "memory_leak.h"

CMemoryLeak g_memoryLeak;

#undef new

void* operator new(const size_t iSize, const char* const sFile, const int iLine) {
	auto pNewPtr = (void*)malloc(iSize);

	g_memoryLeak.Register(pNewPtr, iSize, sFile, iLine, false);

	return pNewPtr;
}

void* operator new[](const size_t iSize, const char* const sFile, const int iLine) {
	auto pNewPtr = (void*)malloc(iSize);

	g_memoryLeak.Register(pNewPtr, iSize, sFile, iLine, true);

	return pNewPtr;
}

void operator delete(void* pPtr, const char* const sFile, const int iLine) {
}

void operator delete[](void* pPtr, const char* const sFile, const int iLine) {
}

void operator delete(void* pPtr) {
	g_memoryLeak.Unregister(pPtr);
}

void operator delete[](void* pPtr) {
	g_memoryLeak.Unregister(pPtr);
}
