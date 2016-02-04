#include "stdafx.h"
#include "CppUnitTest.h"

#include "../C++-Memory-Manager/MemoryAllocator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMemoryManager
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			MemoryAllocator obj;
		}

	};
}