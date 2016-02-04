#include "stdafx.h"
#include "CppUnitTest.h"

#include "../C++-Memory-Manager/MemoryAllocator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


BEGIN_TEST_MODULE_ATTRIBUTE()
	TEST_MODULE_ATTRIBUTE(L"Project", L"MemoryManager")
	TEST_MODULE_ATTRIBUTE(L"Date", L"03/02/2016")
END_TEST_MODULE_ATTRIBUTE()


namespace MemoryManagerTest {		
	TEST_CLASS(UnitTest1) {
	public:
		
		UnitTest1() {
			Logger::WriteMessage("Entering UnitTest1::UnitTest1()");
		}

		~UnitTest1() {
			Logger::WriteMessage("Entering UnitTest1::~UnitTest1()");
		}

		TEST_CLASS_INITIALIZE(ClassInitialize) {
			Logger::WriteMessage("Entering ClassInitialize");
		}

		TEST_CLASS_CLEANUP(ClassCleanup) {
			Logger::WriteMessage("Entering ClassCleanup");
		}

		
		TEST_METHOD(CreateMemoryAllocator) {
			//MemoryAllocator obj;
		}

	};
}