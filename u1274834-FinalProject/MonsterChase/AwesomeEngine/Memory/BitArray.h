#pragma once
#include "HeapManager.h"
#include <cstdint>
class BitArray
{
public:
	size_t * m_pBits = nullptr;
	size_t m_numBytes = 0;

	static BitArray* CreateBitArray(size_t i_numBits, bool i_startClear, HeapManager* i_pAllocator);
	static BitArray* Create(size_t, bool);
	//BitArray();
	//BitArray(size_t i_numBits, bool i_bInitToZero, void* i_heapMemory);
	~BitArray();

	void ClearAll(void);
	void SetAll(void);

	bool AreAllClear(void) const;
	bool AreAllSet(void) const;

	inline bool isBitSet(size_t i_bitNumber) const;
	inline bool isBitClear(size_t i_bitNumber) const;

	void SetBit(size_t i_bitNumber);
	void ClearBit(size_t i_bitNumber);

	bool GetFirstClearBit(size_t & o_bitNumber) const;
	bool GetFirstSetBit(size_t & o_bitNumber) const;
};

