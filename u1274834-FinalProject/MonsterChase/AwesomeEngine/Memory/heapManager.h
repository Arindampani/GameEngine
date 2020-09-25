#pragma once
#include <assert.h>
struct BlockDescriptors {
	void* m_pBLockStartAddr;
	size_t m_sizeBLock;
	BlockDescriptors* next;
};

class HeapManager
{

public:

	BlockDescriptors* pFreeMemoryList = nullptr;
	BlockDescriptors* pOutstandingAllocationList = nullptr;
	BlockDescriptors* pFreeDescriptorList = nullptr;
	size_t m_NumDescriptors;
	size_t m_MemorySizeAllocatable;
	void* pAllocatableStart = nullptr;

	static HeapManager* create(void* const i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);

	// allocates memory. named with a underscore to resolve name clash 
	void* _alloc(size_t i_bytes);
	// allocation with alignment. returns a block of memory with a given alignment
	void* _alloc(size_t i_bytes, unsigned int i_alignment);

	void* operator new(size_t i_size, HeapManager* i_pHeap);
	void* operator new(size_t i_size, void* i_ptr, HeapManager* i_pHeap);
	void operator delete(void* ptr, HeapManager* i_pHeap);

	void* operator new[](size_t i_size, HeapManager* i_pHeap);
	void operator delete[](void* ptr, HeapManager* i_pHeap);

	enum NewAlignment {
		NEW_ALIGN_DEFAULT,
		NEW_ALIGN_16 = 16,
		NEW_ALIGN_32 = 32
	};

	void* operator new(size_t i_size, HeapManager* i_pHeap, NewAlignment i_align);
	void operator delete(void* i_ptr, HeapManager* i_pHeap, NewAlignment i_align);

	//BlockDescriptors* searchAvailableDescriptorSpace();

	inline void insertInOutstandingList(BlockDescriptors* const newBlock);

	inline bool insertInFreeList(BlockDescriptors* const newBlock);
	// frees an allocation
	bool _free(void* const i_ptr);

	// attempt to merge abutting blocks.
	void collect();

	inline void insertInFreeDescriptorList(BlockDescriptors* const newBlock);

	// tells us the size of the largest free block
	inline size_t getLargestFreeBlock() const;
	// tells us how much total memory is available
	inline size_t getTotalFreeMemory() const;

	// tells us if a pointer is within this HeapManagers managed memory
	inline bool Contains(void* i_ptr) const;
	// tells us if this pointer is an outstanding allocation from this block
	inline bool IsAllocated(void* i_ptr) const;

	// a debugging helper function to show us all the free blocks.
	inline void ShowFreeBlocks() const;
	// a debugging helper function to show us all the outstanding blocks.
	void destroy();

	inline void ShowOutstandingAllocations() const;

	inline void* roundUp(void* i_ptr, size_t i_align);


};

#include "HeapManager-inl.h"


