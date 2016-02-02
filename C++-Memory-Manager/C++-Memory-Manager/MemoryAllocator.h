#pragma once

#include <iostream>

typedef long long value_type;


const int SIZE_BLOCK = 22;
const int BLOCK_ALIGNMENT = 8;


class MemoryAllocator {
public:
	//typedef value_type* p_value_type;

public:
	MemoryAllocator();
	~MemoryAllocator();

public:
	value_type* MyMalloc(size_t bytes);
	void MyFree(value_type* pBlock);

public:
	void printBlock() const {
		for (int i = 0; i < SIZE_BLOCK; i++) {
			std::cout << "pBlock[" << i << "] = " << pBlock[i] << std::endl;
		}
	}

private:
	value_type* pBlock;

private:
	value_type* pStartBlock;
	value_type* pEndBlock;
};

