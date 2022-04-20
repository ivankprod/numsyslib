// Numeric System Library Processor

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>

using std::string;

int SetPrec(string strPrec, int iOldT);
int cpuGetLastError();
bool cpuResetErrors();

string InitProcessor(string strValue, int iInNS, int iOutNS);

void cpuMemoryClear(int iIndex);
string cpuMemoryRead(int iIndex);
bool cpuMemoryAdd(int iIndex, string strVal);
bool cpuMemorySub(int iIndex, string strVal);
bool cpuMemoryMul(int iIndex, string strVal);
bool cpuMemoryDiv(int iIndex, string strVal);

#endif
