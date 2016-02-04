#include "stdafx.h"
#include "CppUnitTest.h"

#include "../C++-Memory-Manager/MemoryAllocator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMemoryManager {		
	TEST_CLASS(MemoryAllocatorTest) {
	public:
		
		TEST_METHOD(CreateMemoryAllocator) {
			MemoryAllocator obj;

			Assert::AreEqual((int)((obj.getBlock()[0])), 160);
			Assert::AreEqual((int)((obj.getBlock()[21])), 160);
		}

		TEST_METHOD(MyMallocTooMuchBytes) {
			MemoryAllocator obj;
			char* test_1 = (char*)obj.MyMalloc(400);
			Assert::AreEqual(test_1, NULL);
		}
		
		TEST_METHOD(MyMallocAllignedBytes) {
			MemoryAllocator obj;
			value_type* test_1 = (value_type*)obj.MyMalloc(1);
			int wanted_bytes = *(test_1 + 1);
			Assert::AreEqual(wanted_bytes, 8);
		}

		TEST_METHOD(MyMallocBestFit) {
			MemoryAllocator obj;
			value_type* test_1 = (value_type*)obj.MyMalloc(37);
			value_type* test_2 = (value_type*)obj.MyMalloc(24);
			value_type* test_3 = (value_type*)obj.MyMalloc(31);
			value_type* test_4 = (value_type*)obj.MyMalloc(14);
			
			obj.MyFree((value_type*)test_2);
			Assert::AreEqual((int)(*(test_2 - 1)), 24);

			obj.MyFree((value_type*)test_4);
			Assert::AreEqual((int)*(test_4 - 1), 16);

			test_4 = (value_type*)obj.MyMalloc(9);

			Assert::AreEqual((int)(*(test_2 - 1)), 24);
			Assert::AreEqual((int)(*(test_4 - 1)), 17);
		}

		TEST_METHOD(MyFree_Left_And_Right) {
			MemoryAllocator obj;
			value_type* test_1 = (value_type*)obj.MyMalloc(37);
			value_type* test_2 = (value_type*)obj.MyMalloc(24);
			value_type* test_3 = (value_type*)obj.MyMalloc(31);
			value_type* test_4 = (value_type*)obj.MyMalloc(14);

			obj.MyFree((value_type*)test_2);
			obj.MyFree((value_type*)test_4);

			Assert::AreEqual((int)(*(test_2 - 1)), 24);
			Assert::AreEqual((int)*(test_4 - 1), 16);
		}

		TEST_METHOD(MyFree_Left_And_NotRight_1) {
			MemoryAllocator obj;
			value_type* test_1 = (value_type*)obj.MyMalloc(37);
			value_type* test_2 = (value_type*)obj.MyMalloc(24);
			value_type* test_3 = (value_type*)obj.MyMalloc(31);
			value_type* test_4 = (value_type*)obj.MyMalloc(14);

			obj.MyFree((value_type*)test_1);
			obj.MyFree((value_type*)test_4);

			obj.MyFree((value_type*)test_3);

			Assert::AreEqual((int)(*(test_3 - 1)), 32 + 16 + 16);
		}

		TEST_METHOD(MyFree_Left_And_NotRight_2) {
			MemoryAllocator obj;
			value_type* test_1 = (value_type*)obj.MyMalloc(37);
			value_type* test_2 = (value_type*)obj.MyMalloc(24);
			value_type* test_3 = (value_type*)obj.MyMalloc(31);
			value_type* test_4 = (value_type*)obj.MyMalloc(14);

			obj.MyFree((value_type*)test_4);

			Assert::AreEqual((int)(*(test_4 - 1)), 16);
		}

		TEST_METHOD(MyFree_NotLeft_And_Right_1) {
			MemoryAllocator obj;
			value_type* test_1 = (value_type*)obj.MyMalloc(37);
			value_type* test_2 = (value_type*)obj.MyMalloc(24);
			value_type* test_3 = (value_type*)obj.MyMalloc(31);
			value_type* test_4 = (value_type*)obj.MyMalloc(14);

			obj.MyFree((value_type*)test_1);
			obj.MyFree((value_type*)test_4);

			obj.MyFree((value_type*)test_2);

			Assert::AreEqual((int)(*(test_1 - 1)), 40 + 24 + 16);
			Assert::AreEqual((int)(*(test_4 - 1)), 16);
		}

		TEST_METHOD(MyFree_NotLeft_And_Right_2) {
			MemoryAllocator obj;
			value_type* test_1 = (value_type*)obj.MyMalloc(37);
			value_type* test_2 = (value_type*)obj.MyMalloc(24);
			value_type* test_3 = (value_type*)obj.MyMalloc(31);
			value_type* test_4 = (value_type*)obj.MyMalloc(14);

			obj.MyFree((value_type*)test_1);

			Assert::AreEqual((int)(*(test_1 - 1)), 40);
		}

		TEST_METHOD(MyFree_NotLeft_And_NotRight) {
			MemoryAllocator obj;
			value_type* test_1 = (value_type*)obj.MyMalloc(160);
			Assert::AreEqual((int)(*(test_1 - 1)), 161);

			obj.MyFree((value_type*)test_1);

			Assert::AreEqual((int)(*(test_1 - 1)), 160);
		}

		TEST_METHOD(MyFreeWrongAddress_1) {
			MemoryAllocator obj;
			value_type* test_1 = (value_type*)obj.MyMalloc(37);
			value_type* test_2 = (value_type*)obj.MyMalloc(24);
			value_type* test_3 = (value_type*)obj.MyMalloc(31);
			value_type* test_4 = (value_type*)obj.MyMalloc(14);

			obj.MyFree((value_type*)test_1);
			Assert::AreEqual(obj.getMessageOutput(), "");
			
			obj.MyFree((value_type*)test_1);
			Assert::AreEqual(obj.getMessageOutput(), "ERROR! Wrong address.");
		}

		TEST_METHOD(MyFreeWrongAddress_2) {
			MemoryAllocator obj;
			int* pArr_1 = new int[4];
			value_type* test_1 = (value_type*)obj.MyMalloc(160);

			obj.MyFree((value_type*)pArr_1);
			Assert::AreEqual(obj.getMessageOutput(), "ERROR! Wrong address.");
			
			obj.MyFree((value_type*)test_1);
			Assert::AreEqual(obj.getMessageOutput(), "");

			obj.MyFree((value_type*)test_1);
			Assert::AreEqual(obj.getMessageOutput(), "ERROR! Wrong address.");
		}
	};
}