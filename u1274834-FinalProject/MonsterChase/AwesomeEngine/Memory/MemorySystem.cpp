#include "MemorySystem.h"


bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	// create your HeapManager and FixedSizeAllocators

	heapManager = HeapManager::create(i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors);
	FSA[0] = CreateFixedSizeAllocator(16, 100);
	FSA[1] = CreateFixedSizeAllocator(32, 200);
	FSA[2] = CreateFixedSizeAllocator(64, 400);
	return true;
}

void Collect()
{
	heapManager->collect();
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
}

void DestroyMemorySystem()
{
	// Destroy your HeapManager and FixedSizeAllocators
	heapManager->destroy();
	FSA[0]->~FixedSizeAllocator();
	FSA[1]->~FixedSizeAllocator();
	FSA[2]->~FixedSizeAllocator();
	heapManager = nullptr;
}

FixedSizeAllocator* CreateFixedSizeAllocator(size_t sizeBlock,size_t numBlock){
	return FixedSizeAllocator::create(heapManager, sizeBlock, numBlock);
}

FixedSizeAllocator* GetFixedSizeAllocator(size_t i_size) {
	if (i_size <= 16 && i_size > 0) {
		return FSA[0];
	}
	else if (i_size <= 32 && i_size > 16) {
		return FSA[1];
	}
	else if (i_size <= 96 && i_size > 32) {
		return FSA[2];
	}
	return nullptr;
}

HeapManager* GetHeapManager() {
	return heapManager;
}

