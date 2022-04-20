// Numeric System Library API

#ifndef NUMSYSLIB_API_H
#define NUMSYSLIB_API_H

#define NSL_API __declspec(dllexport)

#include <windows.h>

extern "C"
{
	NSL_API void nslAboutLib(HWND hWndOwner = 0);
	NSL_API char *nslGetLibVersion();

	NSL_API int nslGetLastError();
	NSL_API bool nslResetErrors();
	NSL_API char *nslConvert(char *lpsValue, int iInNS, int iOutNS);
	NSL_API int nslSetPrecision(char *lpsPrecision, int iOldPrec);

	NSL_API bool nslMemClear(int iIndex);
	NSL_API char *nslMemRead(int iIndex);
	NSL_API bool nslMemAdd(int iIndex, char *lpsValue);
	NSL_API bool nslMemSub(int iIndex, char *lpsValue);
	NSL_API bool nslMemMul(int iIndex, char *lpsValue);
	NSL_API bool nslMemDiv(int iIndex, char *lpsValue);
}

#endif
