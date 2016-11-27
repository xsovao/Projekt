#pragma once

#include <utility>
#include <vector>
#include <functional>

#define HORIZONTAL 1
#define VERTICAL 2

namespace Utils
{
	std::pair< CString, std::vector<CString> > ParseFiles(LPCTSTR lpstrFile);
	void CalcHist(uint32_t* scan0, UINT32 stride, int w, int h, std::vector<int> &histR, std::vector<int> &histG, std::vector<int> &histB, std::vector<int> &histA, int thrs, std::function<bool()> fCancel());
	void ThreadCalc(uint32_t * scan0, UINT32 stride, int xx, int yy, int w, int h, std::vector<int>& histR, std::vector<int>& histG, std::vector<int>& histB, std::vector<int>& histA);
	void FlipImage(uint32_t * scan0, uint32_t * printH0, uint32_t * printV0, UINT32 stride, int w, int h);
}