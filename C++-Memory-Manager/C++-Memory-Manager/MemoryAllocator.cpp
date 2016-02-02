#include "MemoryAllocator.h"

#include <iostream>

const int SIZE_BLOCK = 22;


MemoryAllocator::MemoryAllocator() {
	this->pBlock = new (std::nothrow) value_type[SIZE_BLOCK];

	*pBlock = SIZE_BLOCK * 8 - 8 - 8; // header
	*(pBlock + SIZE_BLOCK - 1) = SIZE_BLOCK * 8 - 8 - 8; // footer

	pStartBlock = pBlock;
	pEndBlock = (pBlock + SIZE_BLOCK - 1);

	//for (int i = 0; i < 50; i++) {
	//	std::cout << "pBlock[" << i << "] = " << pBlock[i] << std::endl;
	//}
}

MemoryAllocator::~MemoryAllocator() {
	for (int i = 0; i < SIZE_BLOCK; i++) {
		std::cout << "pBlock[" << i << "] = " << pBlock[i] << std::endl;
	}

	delete this->pBlock;
}

value_type* MemoryAllocator::MyMalloc(size_t bytes) {
	value_type* startPointerBlock = this->pBlock;
	
	if (bytes > SIZE_BLOCK * 8 - 8 - 8) {
		//....
		std::cerr << "Error" << std::endl;
		return NULL;
	}

	if (bytes % 8 != 0) {
		//....
		std::cerr << "Error" << std::endl;
		return NULL;
	}

	if (*startPointerBlock % 8 == 0) {
		value_type* pUserBlock = startPointerBlock + 1;
		
		size_t newHeaderBytes = bytes;
		newHeaderBytes |= 1; // set the bit to 1
		size_t oldHeaderBytes = *startPointerBlock;
		*startPointerBlock = newHeaderBytes;
		startPointerBlock += bytes / 8 + 1;
		*startPointerBlock = bytes;
		startPointerBlock += 1;
		*startPointerBlock = oldHeaderBytes - bytes - 8 - 8;
		startPointerBlock += *startPointerBlock / 8 + 1;
		*startPointerBlock = oldHeaderBytes - bytes - 8 - 8;
		
		return pUserBlock;
	}
	else {
		while (*startPointerBlock % 8 != 0 && *startPointerBlock < SIZE_BLOCK * 8 && *startPointerBlock > 0) {
			startPointerBlock += *startPointerBlock / 8 + 2;
		}
		bool isLastAvailableBlock = false;
		if (*startPointerBlock / 8 + 2) {
			isLastAvailableBlock = true;
		}

		if ((bytes + 8 + 8 > *startPointerBlock && ! isLastAvailableBlock) || *startPointerBlock % 8 != 0 || *startPointerBlock == 0) {
			//....
			std::cerr << "Error" << std::endl;
			return NULL;
		}

		value_type* pUserBlock = startPointerBlock + 1;
			
		if (isLastAvailableBlock && bytes == *startPointerBlock) {
			size_t newHeaderBytes = bytes;
			newHeaderBytes |= 1; // set the bit to 1
			size_t oldHeaderBytes = *startPointerBlock;
			*startPointerBlock = newHeaderBytes;
			startPointerBlock += bytes / 8 + 1;
			*startPointerBlock = bytes;
		}
		else {
			if (isLastAvailableBlock && bytes + 8 + 8 > *startPointerBlock) {
				//....
				std::cerr << "Error" << std::endl;
				return NULL;
			}
			size_t newHeaderBytes = bytes;
			newHeaderBytes |= 1; // set the bit to 1
			size_t oldHeaderBytes = *startPointerBlock;
			*startPointerBlock = newHeaderBytes;
			startPointerBlock += bytes / 8 + 1;
			*startPointerBlock = bytes;
			startPointerBlock += 1;
			*startPointerBlock = oldHeaderBytes - bytes - 8 - 8;
			startPointerBlock += *startPointerBlock / 8 + 1;
			*startPointerBlock = oldHeaderBytes - bytes - 8 - 8;
		}
		

		return pUserBlock;

	}


	return NULL;
}

void MemoryAllocator::MyFree(value_type* pBlock) {

	std::cout << *pBlock << std::endl;

	value_type* currentHeader = pBlock - 1;
	std::cout << "curr: " << *currentHeader << std::endl;

	value_type* leftHeader  = currentHeader - (*(currentHeader - 1) / 8) - 2;
	std::cout << "left: " << *leftHeader << std::endl;
	
	value_type* rightHeader = currentHeader + *currentHeader / 8 + 2;
	std::cout << "right: " << *rightHeader << std::endl;

	if (*leftHeader % 8 != 0 && *rightHeader % 8 != 0 && *leftHeader < SIZE_BLOCK * 8 - 8 - 8 && *rightHeader < SIZE_BLOCK * 8 - 8 - 8) {
		std::cout << "-----first case" << std::endl;
		*currentHeader &= ~1;
	}
	else if (*leftHeader % 8 != 0 && ((*rightHeader % 8 == 0 && *rightHeader < SIZE_BLOCK * 8 - 8 - 8) || *rightHeader > SIZE_BLOCK * 8 - 8 - 8) && *leftHeader < SIZE_BLOCK * 8 - 8 - 8) {
		std::cout << "-----second case" << std::endl;
		*currentHeader &= ~1;
		size_t newHeaderBytes = *currentHeader + *rightHeader + 8 + 8;
		*currentHeader = newHeaderBytes;
		currentHeader += *currentHeader / 8 + 1;
 		*currentHeader = newHeaderBytes;

	}
	else if (*leftHeader % 8 == 0 && *rightHeader % 8 != 0 && *leftHeader < SIZE_BLOCK * 8 - 8 - 8 && *rightHeader < SIZE_BLOCK * 8 - 8 - 8) {
		std::cout << "-----third case" << std::endl;
		*currentHeader &= ~1;
		size_t newHeaderBytes = *currentHeader + *leftHeader + 8 + 8;
		currentHeader -= 1;
		currentHeader -=  (*currentHeader / 8 + 1);
		*currentHeader = newHeaderBytes;
		currentHeader += *currentHeader / 8 + 1;
		*currentHeader = newHeaderBytes;
	}
	else if (*leftHeader % 8 == 0 && *rightHeader % 8 == 0 && *leftHeader < SIZE_BLOCK * 8 - 8 - 8 && *rightHeader < SIZE_BLOCK * 8 - 8 - 8) {
		std::cout << "-----fourth case" << std::endl;
		*currentHeader &= ~1;
		size_t newHeaderBytes = *currentHeader + *leftHeader + 8 + 8 + *rightHeader + 8 + 8;
		currentHeader -= 1;
		currentHeader -= (*currentHeader / 8 + 1);
		*currentHeader = newHeaderBytes;
		currentHeader += *currentHeader / 8 + 1;
		*currentHeader = newHeaderBytes;
	}

}
