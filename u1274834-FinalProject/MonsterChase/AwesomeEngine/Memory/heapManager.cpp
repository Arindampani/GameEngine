#include "HeapManager.h"
#include <assert.h>
#include <stdio.h>

HeapManager* HeapManager::create(void* const i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors) {
	HeapManager* heapManager = static_cast<HeapManager*>(i_pHeapMemory);
	BlockDescriptors* FreeMemoryBlockDescriptor = reinterpret_cast<BlockDescriptors*>(reinterpret_cast<uintptr_t>(i_pHeapMemory) + sizeof(HeapManager));
	FreeMemoryBlockDescriptor->m_pBLockStartAddr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(i_pHeapMemory) + sizeof(heapManager) + i_numDescriptors * sizeof(BlockDescriptors));
	FreeMemoryBlockDescriptor->m_sizeBLock = i_HeapMemorySize - (sizeof(heapManager) + i_numDescriptors * sizeof(BlockDescriptors));
	FreeMemoryBlockDescriptor->next = nullptr;
	heapManager->pFreeMemoryList = FreeMemoryBlockDescriptor;
	BlockDescriptors* FreeBlockDescriptorList = FreeMemoryBlockDescriptor + 1;
	BlockDescriptors* startNode = FreeBlockDescriptorList;
	size_t i = i_numDescriptors - 1;
	while (i) {
		BlockDescriptors* newBlock = startNode + 1;
		newBlock->m_pBLockStartAddr = nullptr;
		newBlock->m_sizeBLock = 0;
		newBlock->next = nullptr;
		startNode->next = newBlock;
		startNode = startNode->next;
		i--;
	}
	heapManager->pOutstandingAllocationList = nullptr;
	heapManager->pFreeDescriptorList = FreeBlockDescriptorList;
	heapManager->m_NumDescriptors = i_numDescriptors;
	heapManager->m_MemorySizeAllocatable = heapManager->pFreeMemoryList->m_sizeBLock;
	heapManager->pAllocatableStart = heapManager->pFreeMemoryList->m_pBLockStartAddr;
	return heapManager;
}

void* HeapManager::_alloc(size_t i_bytes) {

	BlockDescriptors* startNode = pFreeMemoryList;
	while (startNode) {
		if (startNode->m_sizeBLock > i_bytes)
		{
			BlockDescriptors* newBlock = pFreeDescriptorList;
			pFreeDescriptorList = pFreeDescriptorList->next;
			newBlock->m_pBLockStartAddr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(startNode->m_pBLockStartAddr) + startNode->m_sizeBLock - i_bytes);
			newBlock->m_sizeBLock = i_bytes;
			newBlock->next = nullptr;

			insertInOutstandingList(newBlock);
			startNode->m_sizeBLock = startNode->m_sizeBLock - i_bytes;
			return newBlock->m_pBLockStartAddr;
		}/*else if (startNode->m_sizeBLock == i_bytes) {
			BlockDescriptors* newBLock = startNode;
			startNode = startNode->next;
			newBLock->next = nullptr;

			insertInOutstandingList(newBLock);
			return newBLock->m_pBLockStartAddr;
		}*/

		startNode = startNode->next;
	}
	/*BlockDescriptors* startNode = pFreeMemoryList;
	if (pFreeDescriptorList) {
		while (startNode) {
			if (startNode->m_sizeBLock > i_bytes)
			{
				BlockDescriptors* newBlock = pFreeDescriptorList;
				pFreeDescriptorList = pFreeDescriptorList->next;
				newBlock->m_pBLockStartAddr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(startNode->m_pBLockStartAddr) + startNode->m_sizeBLock - i_bytes);
				newBlock->m_sizeBLock = i_bytes;
				newBlock->next = nullptr;

				insertInOutstandingList(newBlock);
				startNode->m_sizeBLock = startNode->m_sizeBLock - i_bytes;
				return newBlock->m_pBLockStartAddr;
			}
			else if (startNode->m_sizeBLock == i_bytes) {
				BlockDescriptors* newBLock = startNode;
				startNode = startNode->next;
				newBLock->next = nullptr;
				insertInOutstandingList(newBLock);
				return newBLock->m_pBLockStartAddr;
			}

			startNode = startNode->next;
		}
	}
	else {
		if (startNode) {
			return nullptr;
		}
		else if (startNode != nullptr && startNode->m_sizeBLock == i_bytes) {
			BlockDescriptors* newBLock = startNode;
			startNode = startNode->next;
			insertInOutstandingList(newBLock);
			return newBLock->m_pBLockStartAddr;
		}
		else
		{
			while (startNode) {
				if (startNode->next->m_sizeBLock == i_bytes) {

					BlockDescriptors* newBLock = startNode->next;
					startNode->next = startNode->next->next;
					insertInOutstandingList(newBLock);
					return newBLock->m_pBLockStartAddr;
				}
				startNode = startNode->next;
			}
		}

		startNode = pFreeMemoryList;
		while (startNode) {
			if (startNode->next->m_sizeBLock > i_bytes) {

				BlockDescriptors* newBLock = startNode->next;
				startNode->next = startNode->next->next;
				insertInOutstandingList(newBLock);
				return newBLock->m_pBLockStartAddr;
			}
			startNode = startNode->next;
		}

	}*/

	return NULL;
}

void* HeapManager::_alloc(size_t i_bytes, unsigned int i_alignment) {
	_alloc(i_bytes);
	return NULL;
}

bool HeapManager::_free(void* const i_ptr) {
	assert(i_ptr);
	BlockDescriptors* startNode = pOutstandingAllocationList;
	BlockDescriptors* prevNode = startNode;
	if (startNode == nullptr) {
		return false;
	}
	if (startNode->m_pBLockStartAddr <= i_ptr && (reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(startNode->m_pBLockStartAddr) + startNode->m_sizeBLock) > i_ptr))
	{
		BlockDescriptors* newBlock = startNode;
		pOutstandingAllocationList = newBlock->next;
		newBlock->next = nullptr;
		return insertInFreeList(newBlock);
	}
	startNode = startNode->next;
	while (startNode) {
		if (startNode->m_pBLockStartAddr <= i_ptr && (reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(startNode->m_pBLockStartAddr) + startNode->m_sizeBLock) > i_ptr))
		{
			BlockDescriptors* newBlock = startNode;
			prevNode->next = newBlock->next;
			newBlock->next = nullptr;
			return insertInFreeList(newBlock);
		}
		else {
			prevNode = prevNode->next;
			startNode = startNode->next;
		}
	}
	return false;

}

void HeapManager::collect() {
	BlockDescriptors* startNode = pFreeMemoryList;
	while (startNode) {
		if (startNode->next != nullptr && reinterpret_cast<void*>((reinterpret_cast<uintptr_t>(startNode->m_pBLockStartAddr) + startNode->m_sizeBLock)) == startNode->next->m_pBLockStartAddr)
		{
			startNode->m_sizeBLock = startNode->m_sizeBLock + startNode->next->m_sizeBLock;
			BlockDescriptors* newblock = startNode->next;
			startNode->next = newblock->next;
			newblock->m_pBLockStartAddr = nullptr;
			newblock->m_sizeBLock = 0;
			newblock->next = nullptr;
			insertInFreeDescriptorList(newblock);
		}
		else {
			/*if (startNode->m_sizeBLock == 0 || (startNode->next != nullptr && startNode->next->m_sizeBLock == 0))
				printf("test");*/
			startNode = startNode->next;
		}

	}

	return;
}

void HeapManager::destroy() {
	BlockDescriptors* startNode = pFreeDescriptorList;
	while (startNode)
	{
		BlockDescriptors* temp = startNode;
		temp->next = nullptr;
		temp = nullptr;
		startNode = startNode->next;
	}
	pFreeDescriptorList = nullptr;
	startNode = pFreeMemoryList;
	while (startNode)
	{
		BlockDescriptors* temp = startNode;
		temp->next = nullptr;
		temp = nullptr;
		startNode = startNode->next;
	}
	pFreeMemoryList = nullptr;
	pOutstandingAllocationList = nullptr;
}

void* HeapManager::operator new(size_t i_size, HeapManager* i_pHeap) {
	assert(i_pHeap);

	return i_pHeap->_alloc(i_size);
}

void* HeapManager::operator new(size_t i_size, void* i_ptr, HeapManager* i_pHeap) {
	assert(i_ptr);
	assert(i_pHeap);

	if (i_pHeap->Contains(i_ptr) && !i_pHeap->IsAllocated(i_ptr)) {
		BlockDescriptors* startNode = i_pHeap->pFreeMemoryList;

		while (startNode) {

			if (startNode->m_pBLockStartAddr <= i_ptr && (reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(startNode->m_pBLockStartAddr) + startNode->m_sizeBLock) > i_ptr) && reinterpret_cast<void*>(reinterpret_cast<uintptr_t*>(i_ptr) + i_size) < reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(startNode->m_pBLockStartAddr) + startNode->m_sizeBLock)) {
				BlockDescriptors* newBlock = i_pHeap->pFreeDescriptorList;
				i_pHeap->pFreeDescriptorList = i_pHeap->pFreeDescriptorList->next;
				newBlock->m_pBLockStartAddr = i_ptr;
				newBlock->m_sizeBLock = i_size;
				newBlock->next = nullptr;
				i_pHeap->insertInOutstandingList(newBlock);
				startNode->m_sizeBLock = startNode->m_sizeBLock - i_size;
				return newBlock->m_pBLockStartAddr;
			}

			startNode = startNode->next;
		}
	}

	return nullptr;
}

void HeapManager::operator delete(void* i_ptr, HeapManager* i_pHeap) {
	assert(i_pHeap);

	if (i_ptr)
		i_pHeap->_free(i_ptr);

}

void* HeapManager::operator new[](size_t i_size, HeapManager* i_pHeap) {

	assert(i_pHeap);

	return i_pHeap->_alloc(i_size);
}

void HeapManager::operator delete[](void* i_ptr, HeapManager* i_pHeap) {
	assert(i_pHeap);

	if (i_ptr)
		i_pHeap->_free(i_ptr);

}


void* HeapManager::operator new(size_t i_size, HeapManager* i_pHeap, NewAlignment i_align) {
	assert(i_pHeap);

	switch (i_align) {
	case NEW_ALIGN_16:
	case NEW_ALIGN_32:
		return i_pHeap->_alloc(i_size, i_align);
	default:
		return i_pHeap->_alloc(i_size, 4);
	}
}

void HeapManager::operator delete(void* i_ptr, HeapManager* i_pHeap, NewAlignment i_align) {
	assert(i_pHeap);
	if (i_ptr)
		i_pHeap->_free(i_ptr);
}