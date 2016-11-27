#include "stdafx.h"
#include "Utils.h"


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

	void CalcHist(uint32_t* scan0, UINT32 stride, int w, int h, std::vector<int> &histR, std::vector<int> &histG, std::vector<int> &histB, std::vector<int> &histA,int thrs,std::function<bool()> fCancel()) {

		uint32_t *pLine;

		for (int y = 0; y < h; y++) {
			pLine = (uint32_t*)((uint8_t*)scan0 + stride*(y));
			//if(fCancel())return;
			for (int x = 0; x < w; x++) {
				histR[((*pLine) >> 16) & 0xff]++;
				histG[((*pLine) >> 8) & 0xff]++;
				histB[(*pLine) & 0xff]++;
				pLine++;
			}
			
		}
	}

	void ThreadCalc(uint32_t* scan0, UINT32 stride, int xx, int yy,int w, int h, std::vector<int> &histR, std::vector<int> &histG, std::vector<int> &histB, std::vector<int> &histA) {
		
		uint32_t *pLine;
		for (int y = yy; y < h; y++) {
			pLine = (uint32_t*)((uint8_t*)scan0 + stride*(y));
			//if(fCancel())return;
			for (int x = xx; x < w; x++) {
				histR[((*pLine) >> 16) & 0xff]++;
				histG[((*pLine) >> 8) & 0xff]++;
				histB[(*pLine) & 0xff]++;
				pLine++;
			}

		}
	
	}

	void FlipImage(uint32_t* scan0, uint32_t* printH0, uint32_t* printV0, UINT32 stride, int w, int h) {
	
		uint32_t *sLine,*pLine;
		
		for (int y = 0; y < h; y++) {
				sLine = (uint32_t*)((uint8_t*)scan0 + stride*(y));
				pLine = (uint32_t*)((uint8_t*)printH0 + stride*(h - 1) - stride*(y));
				//if(fCancel())return;
				memcpy(pLine, sLine, w * sizeof(uint32_t));

				//	for (int x = 0; x < w; x++) {}
			}

			for (int y = 0; y < h; y++) {
				sLine = (uint32_t*)((uint8_t*)scan0 + stride*(y));
				pLine = (uint32_t*)((uint8_t*)printV0 + stride*(y + 1))-1;
				//if(fCancel())return;

				for (int x = 0; x < w-1; x++) {
					memcpy(pLine, sLine, sizeof(uint32_t));
					sLine++;
					pLine--;
				}
			}
		
	}
		

}
