#pragma once
#include "HeapManager.h"
#include "FixedSizeAllocator.h"

//struct FSAInitData
//{
//	size_t sizeBlock;
//	size_t numBlock;
//};


extern HeapManager* heapManager;
extern FixedSizeAllocator* FSA[];
// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);

// Collect - coalesce free blocks in attempt to create larger blocks
void Collect();

// DestroyMemorySystem - destroy your memory systems
void DestroyMemorySystem();

FixedSizeAllocator* CreateFixedSizeAllocator(size_t sizeBlock,size_t numBlock);

FixedSizeAllocator* GetFixedSizeAllocator(size_t sizeBlock);

HeapManager* GetHeapManager();