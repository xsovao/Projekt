#pragma once

#include <utility>
#include <vector>

namespace Utils
{
	std::pair< CString, std::vector<CString> > ParseFiles(LPCTSTR lpstrFile);
	void CalcHist(uint32_t* scan0, uint32_t stride, int w, int h, std::vector<int> &histR, std::vector<int> &histG, std::vector<int> &histB, std::vector<int> &histA);
}