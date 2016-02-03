//#include "MemoryAllocator.h"
//
//#include <iostream>
//
//
/////
///// Rounds up the bytes to be: bytes % 8 == 0; in order to be aligned the blocks.
/////
//void roundUp(size_t& bytes);
//
/////
///// If the first bit is Up ( 1 ) returns true
///// else returns false
/////
//bool isFirstBitUp(value_type* number);
//// tyrsim nai malkoto i mu pazim poziciqta, kato namerim po malko go zapisvame i taka ..
//
//
//////=====================================
///// ---------------------------------------
//size_t getNeededBlockSpace(size_t& bytes);
//
//
//
//MemoryAllocator::MemoryAllocator() {
//	this->pBlock = new (std::nothrow) value_type[SIZE_BLOCK];
//
//	*pBlock = SIZE_BLOCK * BLOCK_ALIGNMENT - BLOCK_ALIGNMENT - BLOCK_ALIGNMENT; // header of the initial block
//	*(pBlock + SIZE_BLOCK - 1) = SIZE_BLOCK * BLOCK_ALIGNMENT - BLOCK_ALIGNMENT - BLOCK_ALIGNMENT; // footer of the initial block
//
//	pStartBlock = pBlock; // pointer of the start of the block
//	pEndBlock = (pBlock + SIZE_BLOCK - 1); // pointer of the end of the block
//}
//
//MemoryAllocator::~MemoryAllocator() {
//	printBlock();
//
//	delete this->pBlock;
//}
//
//value_type* MemoryAllocator::MyMalloc(size_t bytes) {
//	value_type* startPointerBlock = this->pBlock;
//
//	roundUp(bytes);
//
//	if (bytes > SIZE_BLOCK * BLOCK_ALIGNMENT - BLOCK_ALIGNMENT - BLOCK_ALIGNMENT) {
//		std::cerr << "ERROR! There is not enough memory." << std::endl;
//		return NULL;
//	}
//
//
//	if (!isFirstBitUp(startPointerBlock)) {
//		value_type* pUserBlock = startPointerBlock + 1;
//
//		size_t newHeaderBytes = bytes;
//		newHeaderBytes |= 1; // set the bit to 1
//		size_t oldHeaderBytes = *startPointerBlock;
//		*startPointerBlock = newHeaderBytes;
//		startPointerBlock += bytes / BLOCK_ALIGNMENT + 1;
//		*startPointerBlock = bytes;
//		startPointerBlock += 1;
//		*startPointerBlock = oldHeaderBytes - bytes - BLOCK_ALIGNMENT - BLOCK_ALIGNMENT;
//		startPointerBlock += *startPointerBlock / BLOCK_ALIGNMENT + 1;
//		*startPointerBlock = oldHeaderBytes - bytes - BLOCK_ALIGNMENT - BLOCK_ALIGNMENT;
//
//		return pUserBlock;
//	}
//	else {
//		//while (isFirstBitUp(startPointerBlock) && startPointerBlock >= pStartBlock && startPointerBlock <= pEndBlock) {
//		//	startPointerBlock += *startPointerBlock / BLOCK_ALIGNMENT + 2;
//		//}
//		startPointerBlock = findBestFitBlockSpace();
//
//		if (startPointerBlock == NULL) {
//			std::cerr << "ERROR! There is not enough memory." << std::endl;
//			return NULL;
//		}
//
//		std::cout << "*startPointerBlock: " << *startPointerBlock << std::endl;
//
//		bool isLastAvailableBlock = false;
//		if (*startPointerBlock / BLOCK_ALIGNMENT + 2) {
//			isLastAvailableBlock = true;
//		}
//
//		if ((bytes + BLOCK_ALIGNMENT + BLOCK_ALIGNMENT > *startPointerBlock && !isLastAvailableBlock) || isFirstBitUp(startPointerBlock) || *startPointerBlock == 0) {
//			std::cerr << "ERROR! There is not enough memory." << std::endl;
//			return NULL;
//		}
//
//		value_type* pUserBlock = startPointerBlock + 1;
//
//		if (isLastAvailableBlock && bytes == *startPointerBlock) {
//			size_t newHeaderBytes = bytes;
//			newHeaderBytes |= 1; // set the bit to 1
//			size_t oldHeaderBytes = *startPointerBlock;
//			*startPointerBlock = newHeaderBytes;
//			startPointerBlock += bytes / BLOCK_ALIGNMENT + 1;
//			*startPointerBlock = bytes;
//		}
//		else {
//			if (isLastAvailableBlock && bytes + BLOCK_ALIGNMENT + BLOCK_ALIGNMENT > *startPointerBlock) {
//				std::cerr << "ERROR! There is not enough memory." << std::endl;
//				return NULL;
//			}
//
//			size_t newHeaderBytes = bytes;
//			newHeaderBytes |= 1; // set the bit to 1
//			size_t oldHeaderBytes = *startPointerBlock;
//			*startPointerBlock = newHeaderBytes;
//			startPointerBlock += bytes / BLOCK_ALIGNMENT + 1;
//			*startPointerBlock = bytes;
//			startPointerBlock += 1;
//			*startPointerBlock = oldHeaderBytes - bytes - BLOCK_ALIGNMENT - BLOCK_ALIGNMENT;
//			startPointerBlock += *startPointerBlock / BLOCK_ALIGNMENT + 1;
//			*startPointerBlock = oldHeaderBytes - bytes - BLOCK_ALIGNMENT - BLOCK_ALIGNMENT;
//		}
//
//		return pUserBlock;
//	}
//
//	return NULL;
//}
//
//void MemoryAllocator::MyFree(value_type* pBlock) {
//	if (pBlock == NULL) {
//		std::cerr << "ERROR! Wrong address." << std::endl;
//		return;
//	}
//
//	value_type* currentHeader = pBlock - 1;
//	//std::cout << "currentHeader: " << *currentHeader << std::endl;
//
//	value_type* leftHeader = currentHeader - (*(currentHeader - 1) / BLOCK_ALIGNMENT) - 2;
//	//std::cout << "leftHeader: " << *leftHeader << std::endl;
//
//	value_type* rightHeader = currentHeader + *currentHeader / BLOCK_ALIGNMENT + 2;
//	//std::cout << "rightHeader: " << *rightHeader << std::endl;
//
//	if (currentHeader < pStartBlock || currentHeader > pEndBlock) {
//		std::cerr << "ERROR! Wrong address." << std::endl;
//		return;
//	}
//
//	if (*leftHeader % BLOCK_ALIGNMENT != 0 && *rightHeader % BLOCK_ALIGNMENT != 0 && leftHeader >= pStartBlock && rightHeader <= pEndBlock) {
//		std::cout << "-----first case-----" << std::endl;
//		*currentHeader &= ~1;
//	}
//	else if (*leftHeader % BLOCK_ALIGNMENT == 0 && *rightHeader % BLOCK_ALIGNMENT == 0 && leftHeader >= pStartBlock && rightHeader <= pEndBlock) {
//		std::cout << "-----fourth case-----" << std::endl;
//		*currentHeader &= ~1;
//		size_t newHeaderBytes = *currentHeader + *leftHeader + BLOCK_ALIGNMENT + BLOCK_ALIGNMENT + *rightHeader + BLOCK_ALIGNMENT + BLOCK_ALIGNMENT;
//		currentHeader -= 1;
//		currentHeader -= (*currentHeader / BLOCK_ALIGNMENT + 1);
//		*currentHeader = newHeaderBytes;
//		currentHeader += *currentHeader / BLOCK_ALIGNMENT + 1;
//		*currentHeader = newHeaderBytes;
//	}
//	else if (*rightHeader % BLOCK_ALIGNMENT == 0 && rightHeader <= pEndBlock) {
//		std::cout << "-----second case-----" << std::endl;
//		*currentHeader &= ~1;
//		size_t newHeaderBytes = *currentHeader + *rightHeader + BLOCK_ALIGNMENT + BLOCK_ALIGNMENT;
//		*currentHeader = newHeaderBytes;
//		currentHeader += *currentHeader / BLOCK_ALIGNMENT + 1;
//		*currentHeader = newHeaderBytes;
//
//	}
//	else if (*leftHeader % BLOCK_ALIGNMENT == 0 && leftHeader >= pStartBlock) {
//		std::cout << "-----third case-----" << std::endl;
//		*currentHeader &= ~1;
//		size_t newHeaderBytes = *currentHeader + *leftHeader + BLOCK_ALIGNMENT + BLOCK_ALIGNMENT;
//		currentHeader -= 1;
//		currentHeader -= (*currentHeader / BLOCK_ALIGNMENT + 1);
//		*currentHeader = newHeaderBytes;
//		currentHeader += *currentHeader / BLOCK_ALIGNMENT + 1;
//		*currentHeader = newHeaderBytes;
//
//	}
//	else {
//		std::cout << "-----fifth case-----" << std::endl;
//
//		if (leftHeader < pStartBlock && *rightHeader % BLOCK_ALIGNMENT != 0) {
//			*currentHeader &= ~1;
//		}
//
//		if (rightHeader > pEndBlock && *leftHeader % BLOCK_ALIGNMENT != 0) {
//			*currentHeader &= ~1;
//		}
//	}
//
//}
//
//void roundUp(size_t& bytes) {
//	if (bytes % BLOCK_ALIGNMENT != 0) {
//		bytes = bytes - (bytes % BLOCK_ALIGNMENT) + BLOCK_ALIGNMENT;
//	}
//}
//
//bool isFirstBitUp(value_type* number) {
//	return *number & 1;
//}
//
/////
///// Find best fit block for the needed bytes.
/////
//value_type* MemoryAllocator::findBestFitBlockSpace() {
//	value_type* startPointerBlock = this->pBlock;
//	value_type* pBestFit = NULL;
//	size_t bestFitBytes = SIZE_BLOCK * BLOCK_ALIGNMENT;
//
//	while (startPointerBlock >= pStartBlock && startPointerBlock <= pEndBlock) {
//
//		if (bestFitBytes > *startPointerBlock && (!isFirstBitUp(startPointerBlock))) {
//			bestFitBytes = *startPointerBlock;
//			pBestFit = startPointerBlock;
//		}
//
//		startPointerBlock += *startPointerBlock / BLOCK_ALIGNMENT + 2;
//	}
//
//	return pBestFit;
//}