#pragma once
#include <inttypes.h>
#include <malloc.h>
#include <stdio.h>
#include "MemorySystem.h"
HeapManager* heapManager;
FixedSizeAllocator* FSA[] = {nullptr,nullptr,nullptr};

//void* __cdecl malloc(size_t i_size)
//{
//	void* pReturn = nullptr;
//	FixedSizeAllocator* pFSA = GetFixedSizeAllocator(i_size);
//
//	if (pFSA)
//		pReturn = pFSA->_alloc();
//
//	if (pReturn == nullptr)
//		pReturn = GetHeapManager()->_alloc(i_size);
//
//	return pReturn;
//
//}

//void __cdecl free(void * i_ptr)
//{
//	HeapManager* pheapManager = GetHeapManager();
//	if (pheapManager->Contains(i_ptr) && pheapManager->IsAllocated(i_ptr))
//		pheapManager->_free(i_ptr);
//
//	FixedSizeAllocator* pFSA;
//	size_t i_size = 16;
//	pFSA = GetFixedSizeAllocator(i_size);
//	if ((i_ptr >= pFSA->m_pAllocatorMemory) && (i_ptr < reinterpret_cast<void*>((reinterpret_cast<uintptr_t>(pFSA->m_pAllocatorMemory) + (pFSA->m_BlockSize * pFSA->m_numBlock))))) {
//		pFSA->_free(i_ptr);
//	}
//	i_size = 32;
//	pFSA = GetFixedSizeAllocator(i_size);
//	if ((i_ptr >= pFSA->m_pAllocatorMemory) && (i_ptr < reinterpret_cast<void*>((reinterpret_cast<uintptr_t>(pFSA->m_pAllocatorMemory) + (pFSA->m_BlockSize * pFSA->m_numBlock))))) {
//		pFSA->_free(i_ptr);
//	}
//	i_size = 96;
//	pFSA = GetFixedSizeAllocator(i_size);
//	if ((i_ptr >= pFSA->m_pAllocatorMemory) && (i_ptr < reinterpret_cast<void*>((reinterpret_cast<uintptr_t>(pFSA->m_pAllocatorMemory) + (pFSA->m_BlockSize * pFSA->m_numBlock))))) {
//		pFSA->_free(i_ptr);
//	}
//}

//void * operator new(size_t i_size)
//{
//	return malloc(i_size);
//}
//
//void operator delete(void * i_ptr)
//{
//	return free(i_ptr);
//}
//
//void * operator new[](size_t i_size)
//{
//	return malloc(i_size);
//}
//
//void operator delete [](void * i_ptr)
//{
//	return free(i_ptr);
//}