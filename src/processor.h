
/*
  	Numeric System� Library Processor
  	
  	� 2008-2016 IvanK Production
*/

#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include <string>

using  std::string;

int    SetPrec(string strPrec, int iOldT);
int    cpuGetLastError();
bool   cpuResetErrors();

string InitProcessor(string strValue, int iInNS, int iOutNS);

void   cpuMemoryClear(int iIndex);
string cpuMemoryRead(int iIndex);
bool   cpuMemoryAdd(int iIndex, string strVal);
bool   cpuMemorySub(int iIndex, string strVal);
bool   cpuMemoryMul(int iIndex, string strVal);
bool   cpuMemoryDiv(int iIndex, string strVal);

#endif

