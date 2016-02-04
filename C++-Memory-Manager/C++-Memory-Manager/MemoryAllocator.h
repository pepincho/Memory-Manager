#pragma once

#include <iostream>

#include <string>

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

	value_type* getBlock() const {
		return this->pBlock;
	}

	value_type* findBestFitBlockSpace();

public:
	const char* getMessageOutput() const {
		return this->msg_output;
	}

private:
	void clearMessage() {
		this->msg_output = "";
	}

private:
	value_type* pBlock;

private:
	value_type* pStartBlock;
	value_type* pEndBlock;

private:
	const char* msg_output = "";
};

