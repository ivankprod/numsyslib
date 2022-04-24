// Numeric System Library Utilities

#include <sstream>
#include <cstring>
#include <string>

#include "../include/utils.h"

using std::istringstream;
using std::ostringstream;
using std::swap;

string CStrToStr(char *lpsInput)
{
	string strResult(lpsInput);

	return strResult;
}

char *StrToCStr(string strInput)
{
	const char *clpsInput = strInput.c_str();
	size_t sz = strlen(clpsInput);
	char *p = new char[sz];

	strcpy(p, clpsInput);

	return p;
}

int StrToNum(const string &str)
{
	string strt = str;

	for (int i = 0; i < strt.length(); i++)
	{
		if ((strt[i] != '0') && (strt[i] != '1') && (strt[i] != '2') && (strt[i] != '3') &&
			(strt[i] != '4') && (strt[i] != '5') && (strt[i] != '6') && (strt[i] != '7') &&
			(strt[i] != '8') && (strt[i] != '9'))
			strt.erase(i);
	}

	istringstream iss(strt);
	int Res;
	iss >> Res;

	return Res;
}

string NumToStr(int iNumber)
{
	ostringstream oss;

	oss << iNumber;

	return oss.str();
}

string TrimLeft(string STR)
{
	int len = STR.length();

	for (int i = 0; i < len; i++)
	{
		if (STR[0] == '0')
			STR.erase(0, 1);
		else
			continue;
	}

	if (STR[0] == '.')
		STR.insert(0, 1, '0');

	return STR;
}

string TrimRight(string STR)
{
	int len = STR.length() - 1;

	for (int i = len; i > 0; i--)
	{
		if (STR[STR.length() - 1] == '0')
			STR.erase(STR.length() - 1, 1);
		else
			continue;
	}

	if (STR[STR.length() - 1] == '.')
		STR.erase(STR.length() - 1, 1);

	return STR;
}

string Trim(string STR) { return (TrimLeft(TrimRight(STR))); }

string Reverse(string STR)
{
	unsigned int i, j;

	for (i = 0, j = STR.length() - 1; i < j; i++, j--)
		swap(STR[i], STR[j]);

	return STR;
}
