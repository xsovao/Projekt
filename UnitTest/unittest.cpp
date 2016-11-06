#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Library/Library.h"

#include <vector>

namespace UnitTest
{
	TEST_CLASS(ParseFilesUnitTest)
	{
	public:

		TEST_METHOD(ParseFiles_TestOneFile)
		{
			auto result = ParseFiles(L"C:\\directory\\subdirectory\\file.name.ext\0");
			Assert::AreEqual(result.first, L"C:\\directory\\subdirectory\\", L"directory");
			Assert::IsTrue(result.second.size() == 1, L"count of files");
			Assert::AreEqual(result.second[0], L"file.name.ext", "filename");
		}

		TEST_METHOD(ParseFiles_TestMultipleFiles)
		{
			auto result = ParseFiles(L"C:\\directory\\subdirectory\0file1.name.ext\0file2.name.ext\0");
			Assert::AreEqual(result.first, L"C:\\directory\\subdirectory\\", L"directory");
			Assert::IsTrue(result.second.size() == 2, L"count of files");
			Assert::AreEqual(result.second[0], L"file1.name.ext", "filename 1");
			Assert::AreEqual(result.second[1], L"file2.name.ext", "filename 2");
		}
	};
	TEST_CLASS(HistogramUnitTest)
	{
	public:
		TEST_METHOD(TestHist)
		{
			//TODO unit test
			int w = 1024;
			int h = 1024;
			uint32_t* pBitmap = new uint32_t[1024*1024];
			for (int x = 0; x < 1024*1024; x++) {
					pBitmap[x] = 0xffff;
			}

			std::vector<int> r, g, b, i;
			r.assign(256, 0);
			g.assign(256, 0);
			b.assign(256, 0);
			i.assign(256, 0);
			CalcHist(pBitmap,w*4,w,h,r,g,b,i);

			Assert::AreEqual(r[255],w*h,L"allR in 255");
			Assert::AreEqual(g[255], w*h, L"allG in 255");
			Assert::AreEqual(b[255], w*h, L"allB in 255");
		}
	};
}
