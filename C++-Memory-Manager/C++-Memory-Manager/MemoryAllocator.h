#pragma once

class MemoryAllocator {
public:
	typedef long long value_type;
	//typedef value_type* p_value_type;

public:
	MemoryAllocator();
	~MemoryAllocator();

public: // private
	value_type* blocks;
};