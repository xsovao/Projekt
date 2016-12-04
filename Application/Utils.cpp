#include "stdafx.h"
#include "Utils.h"
#include <thread>


namespace Utils
{
	//	parse file names from file name string in OPENFILENAME struct
	//	returns pair of directory and vector of filenames
	//
	std::pair< CString, std::vector<CString> > ParseFiles(LPCTSTR lpstrFile)
	{
		CString cs = lpstrFile;

		// skip directory name
		while (*lpstrFile) ++lpstrFile;

		if (*(++lpstrFile))
		{
			CString csDirectory;
			std::vector<CString> names;

			csDirectory = cs + _T("\\");
			// iterate filenames
			for ( ; *lpstrFile; ++lpstrFile)
			{
				names.push_back(lpstrFile);

				while (*lpstrFile) ++lpstrFile;
			}

			return std::make_pair(csDirectory, names);
		}
		else
		{	// only one filename
			CString csName, csExt;
			_tsplitpath_s(cs, nullptr, 0, nullptr, 0, csName.GetBuffer(_MAX_FNAME), _MAX_FNAME, csExt.GetBuffer(_MAX_EXT), _MAX_EXT);
			csName.ReleaseBuffer();
			csExt.ReleaseBuffer();

			return std::make_pair(cs.Left(cs.GetLength() - csName.GetLength() - csExt.GetLength()), std::vector<CString>({ csName + csExt }));
		}

	}

	void CalcHist(uint32_t* scan0, UINT32 stride, int w, int h, std::vector<int> &histR, std::vector<int> &histG, std::vector<int> &histB,int thrs,std::function<bool()> fCancel) {

		uint32_t *pLine;

		std::thread *threads = new std::thread[thrs];

		for (int i = 0; i < thrs; i++) {
			if (i<thrs - 1)
				threads[i] = std::thread(&Utils::ThreadCalc, scan0, stride, i*w / thrs, (i + 1)*w / thrs - 1, 0, h, std::ref(histR), std::ref(histG), std::ref(histB), fCancel);
			else
				threads[i] = std::thread(&Utils::ThreadCalc, scan0, stride, i*w / thrs, w, 0, h, std::ref(histR), std::ref(histG), std::ref(histB), fCancel);
		}
		
		for (int i = 0; i < thrs; i++) {
			threads[i].join();
		}
		
		/*
		for (int y = 0; y < h; y++) {
			pLine = (uint32_t*)((uint8_t*)scan0 + stride*(y));
			if(fCancel())return;
			for (int x = 0; x < w; x++) {
				histR[((*pLine) >> 16) & 0xff]++;
				histG[((*pLine) >> 8) & 0xff]++;
				histB[(*pLine) & 0xff]++;
				pLine++;
			}
			
		}*/
	}

	void ThreadCalc(uint32_t* scan0, UINT32 stride, int x1, int x2,int y1, int y2, std::vector<int> &histR, std::vector<int> &histG, std::vector<int> &histB, std::function<bool()> fCancel) {
		
		uint32_t *pLine;
		for (int y = y1; y < y2; y++) {
			pLine = (uint32_t*)((uint8_t*)scan0 + stride*(y));
			//if(fCancel())return;
			for (int x = x1; x < x2; x++) {
				histR[((*pLine) >> 16) & 0xff]++;
				histG[((*pLine) >> 8) & 0xff]++;
				histB[(*pLine) & 0xff]++;
				pLine++;
			}

		}
	
	}

	void FlipImage(uint32_t* scan0, uint32_t* printH0, uint32_t* printV0, UINT32 stride, int w, int h, int thrs,std::function<bool()> fCancel) {
	
		uint32_t *sLine,*pLine;
		
		std::thread *threads = new std::thread[thrs];

		for (int i = 0; i < thrs; i++) {
			if (i<thrs - 1)
				threads[i] = std::thread(&Utils::ThreadFlip, scan0, printH0,printV0,stride, w,h, i*h/thrs,(i + 1)*h / thrs - 1, fCancel);
			else
				threads[i] = std::thread(&Utils::ThreadFlip, scan0, printH0, printV0, stride,w,h, i*h / thrs, h, fCancel);
		}

		for (int i = 0; i < thrs; i++) {
			threads[i].join();
		}

		/*for (int y = 0; y < h; y++) {
				sLine = (uint32_t*)((uint8_t*)scan0 + stride*(y));
				pLine = (uint32_t*)((uint8_t*)printH0 + stride*(h - 1) - stride*(y));
				if(fCancel())return;
				memcpy(pLine, sLine, w * sizeof(uint32_t));

			}

			for (int y = 0; y < h; y++) {
				if(fCancel())return;
				sLine = (uint32_t*)((uint8_t*)scan0 + stride*(y));
				pLine = (uint32_t*)((uint8_t*)printV0 + stride*(y + 1))-1;

				for (int x = 0; x < w-1; x++) {
					memcpy(pLine, sLine, sizeof(uint32_t));
					sLine++;
					pLine--;
				}
			}*/
		
	}

	void ThreadFlip(uint32_t* scan0, uint32_t* printH0, uint32_t* printV0, UINT32 stride, int w,int h,int h1, int h2, std::function<bool()> fCancel) {
		
		uint32_t *sLine, *pLine;

		for (int y = h1; y < h2; y++) {
			if (fCancel())return;
			sLine = (uint32_t*)((uint8_t*)scan0 + stride*(y));
			pLine = (uint32_t*)((uint8_t*)printH0 + stride*(h - 1) - stride*(y));
			memcpy(pLine, sLine, w * sizeof(uint32_t));
		}

		for (int y = h1; y < h2; y++) {
			if (fCancel())return;
			sLine = (uint32_t*)((uint8_t*)scan0 + stride*(y));
			pLine = (uint32_t*)((uint8_t*)printV0 + stride*(y + 1)) - 1;
			for (int x = 0; x < w - 1; x++) {
				memcpy(pLine, sLine, sizeof(uint32_t));
				sLine++;
				pLine--;
			}
		}
	}
		

}
