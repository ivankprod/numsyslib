// Numeric System Library Main Module

#include <windows.h>

#include "strings.h"
#include "utils.h"
#include "processor.h"

#include "numsyslib_api.h"

NSL_API char *nslGetLibVersion() { return StrToCStr(NSL_VERSION); }
NSL_API int nslGetLastError() { return cpuGetLastError(); }
NSL_API bool nslResetErrors() { return cpuResetErrors(); }

NSL_API char *nslConvert(char *lpsValue, int iInNS, int iOutNS)
{
	return StrToCStr(InitProcessor(CStrToStr(lpsValue), iInNS, iOutNS));
}

NSL_API int nslSetPrecision(char *lpsPrecision, int iOldPrec)
{
	return SetPrec(CStrToStr(lpsPrecision), iOldPrec);
}

NSL_API bool nslMemClear(int iIndex)
{
	if ((iIndex < 0) && (iIndex > 4))
		return false;
	else
		cpuMemoryClear(iIndex);

	return true;
}

NSL_API char *nslMemRead(int iIndex)
{
	if ((iIndex < 0) && (iIndex > 4))
		return StrToCStr(string("+"));

	return StrToCStr(cpuMemoryRead(iIndex));
}

NSL_API bool nslMemAdd(int iIndex, char *lpsValue)
{
	if ((iIndex < 0) && (iIndex > 4))
		return false;

	return cpuMemoryAdd(iIndex, CStrToStr(lpsValue));
}

NSL_API bool nslMemSub(int iIndex, char *lpsValue)
{
	if ((iIndex < 0) && (iIndex > 4))
		return false;

	return cpuMemorySub(iIndex, CStrToStr(lpsValue));
}

NSL_API bool nslMemMul(int iIndex, char *lpsValue)
{
	if ((iIndex < 0) && (iIndex > 4))
		return false;

	return cpuMemoryMul(iIndex, CStrToStr(lpsValue));
}

NSL_API bool nslMemDiv(int iIndex, char *lpsValue)
{
	if ((iIndex < 0) && (iIndex > 4))
		return false;

	return cpuMemoryDiv(iIndex, CStrToStr(lpsValue));
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		/// init

		break;
	}

	case DLL_PROCESS_DETACH:
	{
		/// close

		break;
	}

	case DLL_THREAD_ATTACH:
	{
		break;
	}

	case DLL_THREAD_DETACH:
	{
		break;
	}
	}

	return TRUE;
}
