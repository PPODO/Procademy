#pragma once
#include <Windows.h>
#include "List.h"

struct FAllocInformation {
public:
	void* m_pPtr;
	size_t m_iSize;
	char m_sFilePath[MAX_PATH];
	unsigned short m_iLine;
	bool m_bIsArray;

public:
	FAllocInformation() : m_pPtr(), m_iSize(), m_iLine(), m_bIsArray() { ZeroMemory(m_sFilePath, MAX_PATH); }

	void Initialize(void* const pPtr, const size_t iSize, const char* const sFilePath, const unsigned short iLine, const bool bIsArray) {
		m_pPtr = pPtr;
		m_iSize = iSize;
		m_iLine = iLine;
		m_bIsArray = bIsArray;

		CopyMemory(m_sFilePath, sFilePath, MAX_PATH);
	}

};

class CMemoryLeak {
private:
	CList<FAllocInformation> m_memoryManager;

public:
	CMemoryLeak() {
	}

	~CMemoryLeak() {
	}

public:
	void Register(void* pPtr, const size_t iSize, const char* const sFile, unsigned short iLine, bool bIsArray) {
		if (auto pResult = (FAllocInformation*)malloc(sizeof(FAllocInformation))) {
			pResult->Initialize(pPtr, iSize, sFile, iLine, bIsArray);

			m_memoryManager.Push(pResult);
		}
	}

	void Unregister(void* pPtr) {
		auto lambda = [&](void* const pData) -> bool {  if (auto pAllocInfo = reinterpret_cast<FAllocInformation*>(pData)) return pAllocInfo->m_pPtr == pPtr; };

		if (m_memoryManager.RemoveAt(pPtr, lambda))
			free(pPtr);
#ifdef _WIN32
		else if (m_memoryManager.RemoveAt(reinterpret_cast<int*>(pPtr) - 1, lambda))
			free(reinterpret_cast<int*>(pPtr) - 1);
#endif
#ifdef _WIN64
		else if (m_memoryManager.RemoveAt(reinterpret_cast<int*>(pPtr) - 2, lambda))
			free(reinterpret_cast<int*>(pPtr) - 2);
#endif
	}

};

void* operator new(const size_t iSize, const char* const sFile, const int iLine);
void* operator new[](const size_t iSize, const char* const sFile, const int iLine);

void operator delete(void* pPtr, const char* const sFile, const int iLine);
void operator delete[](void* pPtr, const char* const sFile, const int iLine);

void operator delete(void* pPtr);
void operator delete[](void* pPtr);

#define new new(__FILE__, __LINE__)