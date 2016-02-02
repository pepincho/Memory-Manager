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

int main() {

	std::cout << "<><><><><>Memory Allocator.<><><><><>" << std::endl;

	MemoryAllocator custom_allocator;

	int* pArr_1 = new int[4];

	char* test_1 = (char*)custom_allocator.MyMalloc(40);
	char* test_2 = (char*)custom_allocator.MyMalloc(39);
	char* test_3 = (char*)custom_allocator.MyMalloc(16);
	char* test_4 = (char*)custom_allocator.MyMalloc(14);
	//char* test_5 = (char*)custom_allocator.MyMalloc(8);

	test_3[0] = 'a';

	//custom_allocator.MyFree((value_type*)pArr_1);

	custom_allocator.MyFree((value_type*)test_3);
	custom_allocator.MyFree((value_type*)test_4);
	custom_allocator.MyFree((value_type*)test_1);

	char* test_6 = (char*)custom_allocator.MyMalloc(16);
	//char* test_7 = (char*)custom_allocator.MyMalloc(8);
	char* test_8 = (char*)custom_allocator.MyMalloc(12);

	//custom_allocator.MyFree((value_type*)test_2);
	
	//std::cout << test_3[0] << std::endl;


	
	//system("pause");
	return 0;
}