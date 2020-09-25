#pragma once
#include "BitArray.h"
#include <intrin.h>
#include <math.h>
#include "FixedSizeAllocator.h"

BitArray* BitArray::CreateBitArray(size_t i_numBits, bool i_startClear, HeapManager* i_pAllocator) {
	size_t sizeOfByte = 8;
	
	BitArray* bitArray = static_cast<BitArray*>(i_pAllocator->_alloc(sizeof(BitArray)));
	
	bitArray->m_numBytes = ceil(i_numBits / static_cast<size_t>(sizeof(size_t) * sizeOfByte));
	bitArray->m_pBits = static_cast<size_t*>(i_pAllocator->_alloc(sizeof(size_t) * bitArray->m_numBytes));


	if (i_startClear)
	{
		for (size_t i = 0; i < bitArray->m_numBytes; i++) {
			bitArray->m_pBits[i] = 0;
	}
	}
	return bitArray;


}


BitArray* BitArray::Create(size_t i_numBits, bool i_startClear = true)
{
	/*size_t sizeOfByte = 8;
	BitArray* bitArrayObj = new BitArray();

	bitArrayObj->numberOfElements = i_numBits / bitsPerItem;
	bitArrayObj->arrayOfBits = new size_t[bitArrayObj->numberOfElements];
	if (i_startClear)
	{
		for (size_t i = 0; i < bitArrayObj->numberOfElements; i++)
		{
			bitArrayObj->arrayOfBits[i] = 0;
		}
	}*/

	return nullptr;
	//return bitArrayObj;
}
//BitArray::BitArray(size_t i_numBits, bool i_bInitToZero,void * i_heapMemory) {
//	m_numBytes = ceil(i_numBits / static_cast<size_t>(sizeof(size_t) * 8));
//	//size_t * sizeArray = 
//	m_pBits = new size_t[m_numBytes];
//	size_t index = 0;
//	if (i_bInitToZero)
//	{
//		while (index < m_numBytes) {
//			m_pBits[index] = 0;
//			//m_pBits[index] = (m_pBits[index] & 0);
//			index++;
//		}
//	}
//	else {
//		while (index < m_numBytes) {
//			//m_pBits[index] = new size_t;
//			m_pBits[index] = ~(m_pBits[index] & 0);
//			index++;
//		}
//	}
//}
BitArray::~BitArray() {
	delete[] m_pBits;
}

void BitArray::ClearAll(void) {
	unsigned long index = 0;


	while (index < m_numBytes) {
		m_pBits[index] = (m_pBits[index] & 0);
		index++;
	}
}
void BitArray::SetAll(void){
	size_t index = 0;

	while (index < m_numBytes) {
		m_pBits[index] = ~(m_pBits[index] & 0);
		index++;
	}
}

bool BitArray::AreAllClear(void) const {
	size_t index = 0;
	unsigned long bit;
	
	while (index < m_numBytes) {
		if (_BitScanForward(&bit, m_pBits[index]))
			return false;
		index++;
	}

	return true;
}
bool BitArray::AreAllSet(void) const {
	size_t index = 0;

	while (index < m_numBytes) {
		if (m_pBits[index] != ~(m_pBits[index] & 0))
			return false;
		index++;
	}
	return true;
}

inline bool BitArray::isBitSet(size_t i_bitNumber) const {
	size_t BytesToSkip = i_bitNumber / static_cast<size_t>(sizeof(size_t));
	size_t BitsToCheck = i_bitNumber % static_cast<size_t>(sizeof(size_t));

	if (BitsToCheck > 0) {
		if (m_pBits[BytesToSkip + 1] & (1 << (BitsToCheck - 1)))
			return true;
		else
			return false;
	}
	else {
		if (m_pBits[BytesToSkip] & (1 << (BitsToCheck - 1)))
			return true;
		else
			return false;
	}
	
}
inline bool BitArray::isBitClear(size_t i_bitNumber) const {
	size_t BytesToSkip = i_bitNumber / static_cast<size_t>(sizeof(size_t));
	size_t BitsToCheck = i_bitNumber % static_cast<size_t>(sizeof(size_t));

	if (BitsToCheck > 0) {
		if (m_pBits[BytesToSkip + 1] & (1 << (BitsToCheck - 1)))
			return true;
		else
			return false;
	}
	else {
		if (m_pBits[BytesToSkip] & (1 << (BitsToCheck - 1)))
			return true;
		else
			return false;
	}
}

void BitArray::SetBit(size_t i_bitNumber) {
	size_t BytesToSkip = i_bitNumber / static_cast<size_t>(sizeof(size_t));
	size_t BitsToCheck = i_bitNumber % static_cast<size_t>(sizeof(size_t));

	if (BitsToCheck > 0) {
		m_pBits[BytesToSkip + 1] = m_pBits[BytesToSkip + 1] | (1 << (BitsToCheck - 1));
	}
	else {
		m_pBits[BytesToSkip] = m_pBits[BytesToSkip] | (1 << (BitsToCheck - 1));
	}

}
void BitArray::ClearBit(size_t i_bitNumber) {
	size_t BytesToSkip = i_bitNumber / static_cast<size_t>(sizeof(size_t));
	size_t BitsToCheck = i_bitNumber % static_cast<size_t>(sizeof(size_t));

	if (BitsToCheck > 0) {
		m_pBits[BytesToSkip + 1] = m_pBits[BytesToSkip + 1] & (1 << (BitsToCheck - 1));
	}
	else {
		m_pBits[BytesToSkip] = m_pBits[BytesToSkip] & (1 << (BitsToCheck - 1));
	}
}

bool BitArray::GetFirstClearBit(size_t& o_bitNumber) const {
	size_t index = 0;
	unsigned long posOfBit = 0;
	while (index < this->m_numBytes) {
		//size_t number = m_pBits[index];
		//size_t number2 = ~(m_pBits[index] & 0);
		// ~(m_pBits[index] & 0)
		if (m_pBits[index] != -1) {
			_BitScanForward(&posOfBit, m_pBits[index]);
			break;
		}

		index++;
		/*if (m_pBits[index] != ~(m_pBits[index] & 0) && _BitScanForward(&posOfBit, m_pBits[index]))
			break;
		index++;*/
	}
	
	o_bitNumber = m_pBits[index] & (1 << (posOfBit - 1));

	if (o_bitNumber)
		return true;
	return false;
}
bool BitArray::GetFirstSetBit(size_t& o_bitNumber) const {
	size_t index = 0;
	unsigned long pos = 0;

	while (index < m_numBytes) {
		_BitScanForward(&pos, m_pBits[index]);
		if(pos != 0)
			o_bitNumber = (m_pBits[index] >> pos) & 1;
		index++;
	}

	if (o_bitNumber)
		return true;
	return false;
}

//bool BitArray::operator[](size_t index) const {
//	return true;
//}