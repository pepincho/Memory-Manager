#include "stdafx.h"
#include "CppUnitTest.h"

#include "../C++-Memory-Manager/MemoryAllocator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMemoryManager {		
	TEST_CLASS(MemoryAllocatorTest) {
	public:
		
		TEST_METHOD(CreateMemoryAllocator) {
			MemoryAllocator obj;
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

		TEST_METHOD(MyFreeLeftAndRight) {
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

		TEST_METHOD(MyFreeLeftAndNotRight_1) {
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

		TEST_METHOD(MyFreeLeftAndNotRight_2) {
			MemoryAllocator obj;
			value_type* test_1 = (value_type*)obj.MyMalloc(37);
			value_type* test_2 = (value_type*)obj.MyMalloc(24);
			value_type* test_3 = (value_type*)obj.MyMalloc(31);
			value_type* test_4 = (value_type*)obj.MyMalloc(14);

			obj.MyFree((value_type*)test_4);

			Assert::AreEqual((int)(*(test_4 - 1)), 16);
		}

		TEST_METHOD(MyFreeNotLeftAndRight_1) {
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
	};
}