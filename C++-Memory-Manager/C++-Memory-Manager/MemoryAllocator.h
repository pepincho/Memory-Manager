#pragma once

#include <iostream>

#include <string>

typedef long long value_type;

///
/// the number of elements we want to have in our block(array)
///
const int SIZE_BLOCK = 22;

///
/// size of the block alignement
///
const int BLOCK_ALIGNMENT = 8;


class MemoryAllocator {
//public:
	//typedef value_type* p_value_type;

public:
	MemoryAllocator();
	~MemoryAllocator();

public:
	value_type* MyMalloc(size_t bytes);
	void MyFree(value_type* pBlock);

public:
	void printBlock() const;
	value_type* getBlock() const;

private:
	value_type* findBestFitBlockSpace();
	void roundUp(size_t& bytes);
	bool isFirstBitUp(value_type* number);

public:
	const char* getMessageOutput() const;

private:
	void clearMessage();

private:
	value_type* pBlock;

private:
	value_type* pStartBlock;
	value_type* pEndBlock;

private:
	const char* msg_output = "";
};

