#pragma once
#include "BitArray.h"
#include "HeapManager.h"
class FixedSizeAllocator
{
public:
	void* m_pAllocatorMemory = nullptr;
	BitArray* m_pAvailableBits = nullptr;
	size_t m_BlockSize = 0;
	size_t m_numBlock = 0;

	static FixedSizeAllocator* create(HeapManager * i_pheapManager, size_t m_BlockSize, size_t m_numBlock);

	FixedSizeAllocator(void * const i_pheapMemory,size_t m_BlockSize, size_t m_numBlock, HeapManager* i_pheapManager);
	void * _alloc();
	//void setAllocatorMemory(void * i_ptr);
	void _free(void * i_ptr);
	~FixedSizeAllocator();
	
private:
	//void* m_pAllocatorMemory = nullptr;
	


};

