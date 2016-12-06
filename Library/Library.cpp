// Library.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Library.h"
#include "../Application/Utils.h"


//// This is an example of an exported variable
//LIBRARY_API int nLibrary=0;
//
//// This is an example of an exported function.
//LIBRARY_API int fnLibrary(void)
//{
//    return 42;
//}
//
//// This is the constructor of a class that has been exported.
//// see Library.h for the class definition
//CLibrary::CLibrary()
//{
//    return;
//}

//	parse file names from file name string in OPENFILENAME struct
//	returns pair of directory and vector of filenames
//
LIBRARY_API std::pair< CString, std::vector<CString> > ParseFiles(LPCTSTR lpstrFile)
{
	return Utils::ParseFiles(lpstrFile);
}

LIBRARY_API void CalcHist(uint32_t* scan0, uint32_t stride, int w, int h, std::vector<int> &histR, std::vector<int> &histG, std::vector<int> &histB, int thrs, std::function<bool()> fCancel) {
	return Utils::CalcHist(scan0, stride, w, h, histR, histG, histB,thrs,fCancel);
}

LIBRARY_API void FlipImage(uint32_t * scan0, uint32_t * printH0, uint32_t * printV0, UINT32 stride, int w, int h, int thrs, std::function<bool()> fCancel) {
	return FlipImage(scan0, printH0, printV0, stride, w, h, thrs, fCancel);
}


