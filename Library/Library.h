// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIBRARY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LIBRARY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LIBRARY_EXPORTS
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif

#include <functional>
// This class is exported from the Library.dll
//class LIBRARY_API CLibrary {
//public:
//	CLibrary(void);
//	// TODO: add your methods here.
//};
//
//extern LIBRARY_API int nLibrary;
//
//LIBRARY_API int fnLibrary(void);

LIBRARY_API std::pair< CString, std::vector<CString> > ParseFiles(LPCTSTR lpstrFile);

LIBRARY_API void CalcHist(uint32_t* scan0, UINT32 stride, int w, int h, std::vector<int> &histR, std::vector<int> &histG, std::vector<int> &histB, int thrs, std::function<bool()> fCancel);
LIBRARY_API void FlipImage(uint32_t * scan0, uint32_t * printH0, uint32_t * printV0, UINT32 stride, int w, int h, int thrs, std::function<bool()> fCancel);

