#include "MemoryAllocator.h"

#include <iostream>

const int SIZE_BLOCKS = 100;


MemoryAllocator::MemoryAllocator() {
	this->blocks = new (std::nothrow) value_type[SIZE_BLOCKS]; // 100 * 8 = 800 bytes

	*blocks = SIZE_BLOCKS; // header
	*(blocks + SIZE_BLOCKS - 1) = SIZE_BLOCKS; // footer

	for (int i = 0; i < SIZE_BLOCKS; i++) {
		std::cout << "blocks[" << i << "] = " << blocks[i] << std::endl;
	}
}


MemoryAllocator::~MemoryAllocator() {
	delete this->blocks;
}
