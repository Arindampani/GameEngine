#pragma once
#include "FixedSizeAllocator.h"
//#include <stdio.h>


FixedSizeAllocator* FixedSizeAllocator::create(HeapManager* i_pheapManager, size_t i_BlockSize, size_t i_numBlock) {
	/*(i_pheapManager->_alloc(sizeof(FixedSizeAllocator) +(i_BlockSize * i_numBlock)),i_BlockSize,i_numBlock,i_pheapManager);*/
		
	FixedSizeAllocator* allocator = static_cast<FixedSizeAllocator*>(i_pheapManager->_alloc(sizeof(FixedSizeAllocator)));
	//printf("assigned value");
	allocator->m_pAllocatorMemory = i_pheapManager->_alloc(i_BlockSize * i_numBlock);
	//allocator->setAllocatorMemory(i_pheapManager->_alloc(i_BlockSize * i_numBlock));
	allocator->m_pAvailableBits = BitArray::CreateBitArray(i_numBlock, true, i_pheapManager);
	allocator->m_BlockSize = i_BlockSize;
	allocator->m_numBlock = i_numBlock;
	//

	return allocator;

	//return nullptr;
}

//void FixedSizeAllocator::setAllocatorMemory(void* i_ptr) {
//	m_pAllocatorMemory = i_ptr;
//}
FixedSizeAllocator :: FixedSizeAllocator(void * const i_pheapMemory,size_t i_BlockSize, size_t i_numBlock,HeapManager* i_pheapManager){

	m_pAllocatorMemory = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(i_pheapMemory) + sizeof(FixedSizeAllocator) );
	m_BlockSize = i_BlockSize; 
	m_numBlock = i_numBlock;

	m_pAvailableBits = BitArray::CreateBitArray(i_numBlock, true, i_pheapManager);
}

void * FixedSizeAllocator::_alloc() {
	size_t i_firstAvailable = 0;

	if (m_pAvailableBits->GetFirstClearBit(i_firstAvailable)) {


		m_pAvailableBits->SetBit(i_firstAvailable);

		return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(m_pAllocatorMemory) + (i_firstAvailable * m_BlockSize));
	}
	else
		return nullptr;
}

FixedSizeAllocator :: ~FixedSizeAllocator() {
	size_t firstClear;

	if (m_pAvailableBits->GetFirstClearBit(firstClear) ){
		//Oh no we have an outstanding allocation
	}

	delete m_pAvailableBits;
}

void FixedSizeAllocator::_free(void * i_ptr) {

	size_t BLockIndex = (reinterpret_cast<uint8_t *>(i_ptr) - m_pAllocatorMemory);
	m_pAvailableBits->ClearBit(BLockIndex);
}
