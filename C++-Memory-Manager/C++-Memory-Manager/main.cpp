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

	char* test_1 = (char*)custom_allocator.MyMalloc(33);
	char* test_2 = (char*)custom_allocator.MyMalloc(39);
	char* test_3 = (char*)custom_allocator.MyMalloc(16);
	char* test_4 = (char*)custom_allocator.MyMalloc(14);
	//char* test_5 = (char*)custom_allocator.MyMalloc(8);

	test_3[0] = 'a';

	//custom_allocator.MyFree((value_type*)pArr_1);

	custom_allocator.MyFree((value_type*)test_2);
	custom_allocator.MyFree((value_type*)test_2);
	custom_allocator.MyFree((value_type*)test_4);
	custom_allocator.MyFree((value_type*)test_1);
	custom_allocator.MyFree((value_type*)test_4);

	custom_allocator.MyFree((value_type*)test_3);


	char* test_6 = (char*)custom_allocator.MyMalloc(16);
	char* test_7 = (char*)custom_allocator.MyMalloc(6);
	//char* test_8 = (char*)custom_allocator.MyMalloc(12);

	
	//std::cout << test_3[0] << std::endl;


	//BlocksHolder a;
	//char* test1 = (char*)a.MyMalloc(34);
	//char* test2 = (char*)a.MyMalloc(22);
	//char* test3 = (char*)a.MyMalloc(1);
	//char* test4 = (char*)a.MyMalloc(4);

	//char* test5 = (char*)a.MyMalloc(56);
	////long long* test6 = a.MyMalloc(200);
	//char* test7 = (char*)a.MyMalloc(3);
	//char* test8 = (char*)a.MyMalloc(13);
	//char* test9 = (char*)a.MyMalloc(58);
	////a.print();

	//FreeService::MyFree((long long*)test1);
	////a.print();
	////FreeService::MyFree((long long*)test8);
	////a.print();
	////FreeService::MyFree((long long*)test5);
	////a.print();
	//////FreeService::MyFree((long long*)test6);
	////FreeService::MyFree((long long*)test4);
	////a.print();
	////FreeService::MyFree((long long*)test1);
	////a.print();
	////FreeService::MyFree((long long*)test2);
	////a.print();
	////FreeService::MyFree((long long*)test7);
	////a.print();
	////FreeService::MyFree((long long*)test9);


	
	//system("pause");
	return 0;
}