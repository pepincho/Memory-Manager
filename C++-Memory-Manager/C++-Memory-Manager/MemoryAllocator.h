#pragma once

typedef long long value_type;

class MemoryAllocator {
public:
	//typedef value_type* p_value_type;

public:
	MemoryAllocator();
	~MemoryAllocator();

public:
	value_type* MyMalloc(size_t bytes);
	void MyFree(value_type* pBlock);

private:
	value_type* pBlock;

private:
	value_type* pStartBlock;
	value_type* pEndBlock;
};

