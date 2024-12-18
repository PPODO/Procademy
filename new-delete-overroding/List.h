#pragma once
#include <stdlib.h>
#include <functional>

template<typename T>
class CList {
	struct FNode {
	public:
		FNode* m_pPrevNode;
		FNode* m_pNextNode;
		T* m_pData;

	public:
		FNode() : m_pNextNode(), m_pPrevNode(), m_pData() {};

	};

private:
	FNode* m_pStartNode;
	FNode* m_pCurrentNode;

private:
	FNode* Find(void* pPtr, const std::function<bool(void* const)>& lambda) {
		FNode* tempCurrentNode = m_pStartNode->m_pNextNode;

		while (tempCurrentNode) {
			if (lambda(tempCurrentNode->m_pData)) return tempCurrentNode;

			tempCurrentNode = tempCurrentNode->m_pNextNode;
		}
		return nullptr;
	}

public:
	CList() {
		m_pStartNode = (FNode*)malloc(sizeof(FNode));
		m_pStartNode->m_pNextNode = nullptr;
		m_pStartNode->m_pPrevNode = nullptr;
	}

	~CList() {
		// loop delete
		free(m_pStartNode);
	}

	void Push(T* pNewData) {
		if (FNode* pNewNode = (FNode*)malloc(sizeof(FNode))) {
			pNewNode->m_pPrevNode = nullptr;
			pNewNode->m_pNextNode = nullptr;
			pNewNode->m_pData = pNewData;

			if (!m_pStartNode->m_pNextNode) {
				pNewNode->m_pPrevNode = m_pStartNode;
				m_pStartNode->m_pNextNode = pNewNode;
				m_pCurrentNode = pNewNode;
			}
			else {
				pNewNode->m_pPrevNode = m_pCurrentNode;
				m_pCurrentNode->m_pNextNode = pNewNode;
				m_pCurrentNode = pNewNode;
			}
		}
	}

	bool RemoveAt(void* pPtr, const std::function<bool(void* const)>&& lambda) {
		if (FNode* pResult = Find(pPtr, lambda)) {
			pResult->m_pPrevNode->m_pNextNode = pResult->m_pNextNode;
			if (pResult->m_pNextNode)
				pResult->m_pNextNode->m_pPrevNode = pResult->m_pPrevNode;

			free(pResult);
			return true;
		}
		return false;
	}

};