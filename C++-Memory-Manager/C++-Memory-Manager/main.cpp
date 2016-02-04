///
///  main.cpp : Defines the entry point for the console application.
///  Course project for the Data-Structures-and-Algorithms with C++ course in FMI 
///
///  Memory Manager
///
///  Created by Petar Ivanov with #45121.
///

#include <iostream>

#include "MemoryAllocator.h"


MemoryAllocator custom_allocator;


value_type* MyMalloc(size_t bytes) {
	return custom_allocator.MyMalloc(bytes);
}

void MyFree(value_type* pBlock) {
	custom_allocator.MyFree(pBlock);
}


int main() {

	std::cout << "========================================================================" << std::endl;
	std::cout << "<><><><><><><><><><>Memory Allocator by Petar Ivanov<><><><><><><><><><>" << std::endl;
	std::cout << "========================================================================" << std::endl;


	//////////////////////////////////////////////////////////////
	/// TEST 1
	//////////////////////////////////////////////////////////////


	int* pArr_1 = new int[4];

	char* test_1 = (char*)MyMalloc(33);
	char* test_2 = (char*)MyMalloc(39);
	char* test_4 = (char*)MyMalloc(14);
	char* test_3 = (char*)MyMalloc(16);
	char* test_5 = (char*)custom_allocator.MyMalloc(8);

	test_3[0] = 'a';

	MyFree((value_type*)test_2);
	MyFree((value_type*)test_2);
	MyFree((value_type*)test_4);
	MyFree((value_type*)test_1);
	MyFree((value_type*)test_4);

	MyFree((value_type*)test_3);
	MyFree((value_type*)test_3);


	char* test_6 = (char*)MyMalloc(160);
	MyFree((value_type*)test_6);
	char* test_7 = (char*)MyMalloc(1);
	char* test_8 = (char*)MyMalloc(12);
	value_type* test_9 = (value_type*)MyMalloc(88);

	char* test_10 = (char*)MyMalloc(1);

	MyFree((value_type*)test_10);
	//custom_allocator.MyFree((value_type*)test_9);
	//std::cout << "Ho" << std::endl;
	MyFree((value_type*)(test_9 + 11 + 1));
	MyFree((value_type*)(test_9));


	//////////////////////////////////////////////////////////////
	/// TEST 2
	//////////////////////////////////////////////////////////////


	//MemoryAllocator obj;
	//value_type* test_1 = (value_type*)obj.MyMalloc(37);
	//value_type* test_2 = (value_type*)obj.MyMalloc(24);
	//value_type* test_3 = (value_type*)obj.MyMalloc(31);
	//value_type* test_4 = (value_type*)obj.MyMalloc(14);

	//obj.MyFree((value_type*)test_2);
	//std::cout << *(test_2 - 1) << std::endl;

	//obj.MyFree((value_type*)test_4);

	//value_type* test_5 = (value_type*)obj.MyMalloc(9);


	//////////////////////////////////////////////////////////////
	/// TEST 3
	//////////////////////////////////////////////////////////////


	//MemoryAllocator custom_allocator;

	////char* test_1 = (char*)custom_allocator.MyMalloc(136);
	////char* test_2 = (char*)custom_allocator.MyMalloc(6);

	//int* pArr_1 = new int[4];

	//char* test_1 = (char*)custom_allocator.MyMalloc(33);
	//char* test_2 = (char*)custom_allocator.MyMalloc(39);
	//char* test_3 = (char*)custom_allocator.MyMalloc(16);
	//char* test_4 = (char*)custom_allocator.MyMalloc(14);
	////char* test_5 = (char*)custom_allocator.MyMalloc(8);

	//test_3[0] = 'a';

	////custom_allocator.MyFree((value_type*)pArr_1);

	//custom_allocator.MyFree((value_type*)test_2);
	//custom_allocator.MyFree((value_type*)test_2);
	//custom_allocator.MyFree((value_type*)test_4);
	//custom_allocator.MyFree((value_type*)test_1);
	//custom_allocator.MyFree((value_type*)test_4);

	//custom_allocator.MyFree((value_type*)test_3);
	//custom_allocator.MyFree((value_type*)test_3);


	//char* test_6 = (char*)custom_allocator.MyMalloc(160);
	//custom_allocator.MyFree((value_type*)test_6);
	//char* test_7 = (char*)custom_allocator.MyMalloc(1);
	//char* test_8 = (char*)custom_allocator.MyMalloc(12);
	//value_type* test_9 = (value_type*)custom_allocator.MyMalloc(88);

	//char* test_10 = (char*)custom_allocator.MyMalloc(1);

	//custom_allocator.MyFree((value_type*)test_10);
	////custom_allocator.MyFree((value_type*)test_9);
	////std::cout << "Ho" << std::endl;
	//custom_allocator.MyFree((value_type*)(test_9 + 11 + 1));
	//custom_allocator.MyFree((value_type*)(test_9));

	
	//system("pause");
	return 0;
}