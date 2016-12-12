#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Library/Library.h"
#include <vector>

#define pos(x,y) x+w*y
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

		int sum(std::vector<int> a) {
			int s = 0;
			for (int i = 0; i < (int)(a.size()); i++)s += (int)a[i];
			return s;
		}
	public:
		TEST_METHOD(TestHist_ZeroMap)
		{
			int w = 160;
			int h = 160;
			uint32_t* pBitmap = new uint32_t[w * h];
			for (int x = 0; x <w*h; x++) {
					pBitmap[x] = 0x0;
			}
			std::vector<int> r, g, b;
			r.assign(256, 0);
			g.assign(256, 0);
			b.assign(256, 0);
			CalcHist(pBitmap, w*4, w, h, r, g, b, 1, [this]() {return false; });
			Assert::AreEqual(w*h,r[0],L"allR in 0");
			Assert::AreEqual(w*h,g[0],L"allG in 0");
			Assert::AreEqual(w*h,b[0],L"allB in 0");
		}
		TEST_METHOD(TestHist_OneMap)
		{
			int w = 160;
			int h = 160;
			uint32_t* pBitmap = new uint32_t[w * h];
			for (int x = 0; x <w*h; x++) {
				pBitmap[x] = 0xffffffff;
			}
			std::vector<int> r, g, b;
			r.assign(256, 0);
			g.assign(256, 0);
			b.assign(256, 0);
			CalcHist(pBitmap, w * 4, w, h, r, g, b, 1, [this]() {return false; });
			Assert::AreEqual(w*h, r[255], L"allR in 255");
			Assert::AreEqual(w*h, g[255], L"allG in 255");
			Assert::AreEqual(w*h, b[255], L"allB in 255");
		}
		TEST_METHOD(TestHist_AllGreenMap)
		{
			int w = 160;
			int h = 160;
			uint32_t* pBitmap = new uint32_t[w * h];
			for (int x = 0; x <w*h; x++) {
				pBitmap[x] = 0x0000ff00;
			}
			std::vector<int> r, g, b;
			r.assign(256, 0);
			g.assign(256, 0);
			b.assign(256, 0);
			CalcHist(pBitmap, w * 4, w, h, r, g, b, 1, [this]() {return false; });

			Assert::AreEqual(w*h,g[255], L"all G = 255");
			Assert::AreEqual(w*h,r[0], L"all R = 0");
			Assert::AreEqual(w*h,b[0], L"all B = 0");
			
		}
		TEST_METHOD(TestHist_Threads2)
		{
			int w = 160;
			int h = 160;
			uint32_t* pBitmap = new uint32_t[w * h];
			for (int x = 0; x <w*h; x++) {
				pBitmap[x] = 0xffffffff;
			}
			std::vector<int> r, g, b;
			r.assign(256, 0);
			g.assign(256, 0);
			b.assign(256, 0);
			CalcHist(pBitmap, w * 4, w, h, r, g, b, 2, [this]() {return false; });

			Assert::AreEqual(w*h, sum(r), L"R passed all");
			Assert::AreEqual(w*h, sum(g), L"G passed all");
			Assert::AreEqual(w*h, sum(b), L"B passed all");

		}

		TEST_METHOD(TestHist_Threads3)
		{
			int w = 160;
			int h = 160;
			uint32_t* pBitmap = new uint32_t[w * h];
			for (int x = 0; x <w*h; x++) {
				pBitmap[x] = 0xffffffff;
			}
			std::vector<int> r, g, b;
			r.assign(256, 0);
			g.assign(256, 0);
			b.assign(256, 0);
			CalcHist(pBitmap, w * 4, w, h, r, g, b, 3, [this]() {return false; });

			Assert::AreEqual(w*h, sum(r), L"R passed all");
			Assert::AreEqual(w*h, sum(g), L"G passed all");
			Assert::AreEqual(w*h, sum(b), L"B passed all");

		}
	};

	TEST_CLASS(FlipUnitTest) {
		TEST_METHOD(TestFlip)
		{
			int w = 10;
			int h = 10;
			uint32_t* pBitmap = new uint32_t[w * h];
			uint32_t* pBitmap2 = new uint32_t[w * h];
			uint32_t* pBitmap3 = new uint32_t[w * h];

			for (int x = 0; x <w*h; x++) {
				if(x<w*h/4 || x>w*h*3/4)pBitmap[x] = 0x0;
				else pBitmap[x] = 0xffffffff;
			}

			FlipImage(pBitmap, pBitmap2,pBitmap3, w*4, w, h, 1, [] {return false; });
			Assert::AreEqual(pBitmap[pos(0, 0)], pBitmap2[pos(0, h - 1)], L"horizontal flip");
			Assert::AreEqual(pBitmap[pos(0, 0)], pBitmap3[pos(h-1, 0)], L"vertical flip");
		}

		TEST_METHOD(TestFlip_Threads2)
		{
			int w = 10;
			int h = 10;
			uint32_t* pBitmap = new uint32_t[w * h];
			uint32_t* pBitmap2 = new uint32_t[w * h];
			uint32_t* pBitmap3 = new uint32_t[w * h];

			for (int x = 0; x <w*h; x++) {
				if (x<w*h / 4 || x>w*h * 3 / 4)pBitmap[x] = 0x0;
				else pBitmap[x] = 0xffffffff;
			}

			FlipImage(pBitmap, pBitmap2, pBitmap3, w * 4, w, h, 2, [] {return false; });
			Assert::AreEqual(pBitmap[pos(0, 0)], pBitmap2[pos(0, h - 1)], L"horizontal flip");
			Assert::AreEqual(pBitmap[pos(0, 0)], pBitmap3[pos(h - 1, 0)], L"vertical flip");
		}

	};
}
