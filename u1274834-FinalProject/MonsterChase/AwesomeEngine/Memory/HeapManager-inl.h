#pragma once
#include <stdio.h>
inline void HeapManager::insertInOutstandingList(BlockDescriptors* const newBlock) {
	assert(newBlock);
	BlockDescriptors* startNode = pOutstandingAllocationList;
	if (startNode == nullptr || (startNode->m_pBLockStartAddr >= newBlock->m_pBLockStartAddr)) {
		newBlock->next = startNode;
		pOutstandingAllocationList = newBlock;
	}
	else {
		while (startNode->next != NULL && (startNode->next->m_pBLockStartAddr < newBlock->m_pBLockStartAddr)) {
			startNode = startNode->next;

		}
		newBlock->next = startNode->next;
		startNode->next = newBlock;
	}
	return;
}

inline bool HeapManager::insertInFreeList(BlockDescriptors* const newBlock) {
	assert(newBlock);
	BlockDescriptors* startNode = pFreeMemoryList;

	if (startNode == nullptr || (startNode->m_pBLockStartAddr >= newBlock->m_pBLockStartAddr)) {
		newBlock->next = startNode;
		pFreeMemoryList = newBlock;
		return true;
	}
	else {
		while (startNode->next != NULL && startNode->next->m_pBLockStartAddr < newBlock->m_pBLockStartAddr) {
			startNode = startNode->next;
		}
		newBlock->next = startNode->next;
		startNode->next = newBlock;
		return true;
	}
}

inline void HeapManager::insertInFreeDescriptorList(BlockDescriptors* const newBlock) {
	assert(newBlock);

	//if (newBlock->m_sizeBLock == 0) {
	//	printf("testing");
	//}
	BlockDescriptors* startNode = pFreeDescriptorList;
	if (startNode == NULL) {
		pFreeDescriptorList = newBlock;
	}
	else {
		newBlock->next = startNode->next;
		startNode->next = newBlock;
	}
	return;
}


inline size_t HeapManager::getLargestFreeBlock() const {
	BlockDescriptors* startNode = pFreeMemoryList;
	size_t largest = 0;
	assert(startNode);

	while (startNode) {
		if (startNode->m_sizeBLock > largest)
			largest = startNode->m_sizeBLock;

		startNode = startNode->next;
	}
	return largest;
}

inline size_t HeapManager::getTotalFreeMemory() const {
	BlockDescriptors* startNode = pFreeMemoryList;
	size_t freeMemory = 0;

	while (startNode)
	{
		freeMemory = freeMemory + startNode->m_sizeBLock;
		startNode = startNode->next;
	}
	return freeMemory;
}


inline bool HeapManager::Contains(void* i_ptr) const {
	return (i_ptr >= pAllocatableStart && i_ptr < reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pAllocatableStart) + m_MemorySizeAllocatable));
}

inline bool HeapManager::IsAllocated(void* i_ptr) const {
	BlockDescriptors* startNode = pOutstandingAllocationList;
	while (startNode) {
		if (startNode->m_pBLockStartAddr == i_ptr)
			return true;

		startNode = startNode->next;
	}
	return false;
}

inline void HeapManager::ShowFreeBlocks() const {
	BlockDescriptors* startNode = pFreeMemoryList;

	while (startNode) {
		startNode = startNode->next;
	}
}

inline void HeapManager::ShowOutstandingAllocations() const {
	BlockDescriptors* startNode = pOutstandingAllocationList;

	while (startNode) {
		startNode = startNode->next;
	}
}
inline void* HeapManager::roundUp(void* i_ptr, size_t i_align) {

	return i_ptr;
}
