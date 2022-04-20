
/*
  	Numeric System� Library Utilities
  	
  	� 2008-2016 IvanK Production
*/

#ifndef _UTILS_H_
#define _UTILS_H_

#include <cstring>
#include <string>

using  std::string;

string CStrToStr(char * lpsInput);
char * StrToCStr(string strInput);
int    StrToNum(const string &str);
string NumToStr(int iNumber);

string TrimLeft(string STR);
string TrimRight(string STR);
string Trim(string STR);
string Reverse(string STR);

#endif

