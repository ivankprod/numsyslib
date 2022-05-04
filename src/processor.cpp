// Numeric System Library Processor

#include <algorithm>
#include <math.h>
#include <vector>
#include <sstream>
#include <cstring>
#include <string>

#include "bdouble.h"
#include "strings.h"
#include "utils.h"
#include "processor.h"

#define DIG "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

#define NEGA_POSITIONAL_NUMSYS -2
#define ROMAN_NUMSYS -1
#define FACTORIAL_NUMSYS 0
#define FIBONACCI_NUMSYS 1
#define POSITIONAL_NUMSYS 2

//#define MAX_UINT64 "27777890035286.0"

typedef unsigned __int64 uint64;

bdouble MAIN_REGISTER[5] = {bdouble("0"), bdouble("0"), bdouble("0"), bdouble("0"), bdouble("0")};

using std::istringstream;
using std::ostringstream;
using std::vector;

int cpuERR_CODE = 0;
int iMainPrec = 4;
const int iFibCount = 65;

bool dcless(char c, int ns);
bool dcless_for(string s, int ns);

string RoundZ(string strNumber);

bool CheckValid(string &strValue, int iNS);
bool CheckValidPrec(string strPrecVal);

string bfConvertFromDec(bdouble, int, int);
bdouble bfConvertToDec(string, int);

const int arabar[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
const char *romanar[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};

char *ArabToRoman(unsigned short int arab);
unsigned short int RomanToArab(char *roman);

class Processor
{
private:
	vector<int> a;
	int NSoriginal;

public:
	Processor(string strSource, int iNumSys)
	{
		this->NSoriginal = iNumSys;

		for (int i = 0; i < strSource.length(); i++)
			this->a.push_back(CharToInt(strSource[i]));
	}

	int CharToInt(char c)
	{
		if ((c >= '0') && (c <= '9') && (c - '0') < this->NSoriginal)
			return c - '0';
		else
		{
			if ((c >= 'A') && (c <= 'Z') && (c - 'A') < this->NSoriginal)
			{
				return c - 'A' + 10;
			}
			else
				return -1;
		}
	}

	char IntToChar(int c)
	{
		if ((c >= 0) && (c <= 9))
			return c + '0';
		else
			return c + 'A' - 10;
	}

	int NextNumber(int NSfinal)
	{
		int temp = 0;

		for (int i = 0; i < this->a.size(); i++)
		{
			temp = temp * this->NSoriginal + this->a[i];
			a[i] = temp / NSfinal;
			temp %= NSfinal;
		}

		return temp;
	}

	bool IsZero()
	{
		for (int i = 0; i < this->a.size(); i++)
		{
			if (a[i] != 0)
				return false;
		}

		return true;
	}

	string Convert(int NSfinal)
	{
		vector<int> b;
		int size = 0;

		do
		{
			b.push_back(this->NextNumber(NSfinal));
			size++;
		} while (!this->IsZero());

		string sTemp = "";
		for (int i = b.size() - 1; i >= 0; i--)
			sTemp += IntToChar(b[i]);

		return sTemp;
	}
};

class Fibonacci
{
private:
	uint64 *LPFib;

public:
	Fibonacci()
	{
		LPFib = new uint64[iFibCount];

		LPFib[0] = 1;
		LPFib[1] = 2;

		for (int i = 2; i < iFibCount; i++)
		{
			LPFib[i] = LPFib[i - 1] + LPFib[i - 2];
		}
	}

	~Fibonacci()
	{
		if (LPFib)
		{
			delete[] LPFib;
			LPFib = 0;
		}
	}

	uint64 DecToFib(uint64 vf)
	{
		if ((vf >= LPFib[iFibCount - 1]) || (vf == -1))
		{
			return -1;
		}

		uint64 res = 0;

		if (vf == 0)
			return (res);

		uint64 fixp = 0x01;
		for (int i = iFibCount - 2; i >= 0; i--)
		{
			if (vf == LPFib[i])
			{
				res |= (fixp << i);
				break;
			}
			if (vf > LPFib[i])
			{
				vf -= LPFib[i];
				res |= (fixp << i);
			}
		}

		return (res);
	}

	uint64 FibToDec(uint64 vi)
	{
		if ((vi >= LPFib[iFibCount - 1]) || (vi == -1))
		{
			return -1;
		}

		uint64 res = 0;

		if (vi == 0)
			return (res);

		uint64 fixp = 0x01;
		for (int i = 0; i <= iFibCount - 2; i++)
		{
			res += LPFib[i] * (fixp & (vi >> i));
		}

		return (res);
	}

	string FibToStrBin(uint64 a)
	{
		string bstr = "";

		do
		{
			(a % 2) ? bstr.insert(0, "1") : bstr.insert(0, "0");
			a /= 2;
		} while (a > 0);

		return bstr;
	}
};

void cpuMemoryClear(int iIndex) { MAIN_REGISTER[iIndex] = bdouble("0.0"); }

string cpuMemoryRead(int iIndex) { return RoundZ(MAIN_REGISTER[iIndex].print()); }

bool cpuMemoryAdd(int iIndex, string strVal)
{
	bdouble x(strVal);

	MAIN_REGISTER[iIndex] = MAIN_REGISTER[iIndex] + x;

	return true;
}

bool cpuMemorySub(int iIndex, string strVal)
{
	bdouble x(strVal);

	MAIN_REGISTER[iIndex] = MAIN_REGISTER[iIndex] - x;

	return true;
}

bool cpuMemoryMul(int iIndex, string strVal)
{
	bdouble x(strVal);

	MAIN_REGISTER[iIndex] = MAIN_REGISTER[iIndex] * x;

	return true;
}

bool cpuMemoryDiv(int iIndex, string strVal)
{
	bdouble x(strVal);

	if (zcmp(x))
	{
		cpuERR_CODE = ERROR_DIVIDE_BY_ZERO;
		return false;
	}
	else
		MAIN_REGISTER[iIndex] = MAIN_REGISTER[iIndex] / x;

	return true;
}

int cpuGetLastError()
{
	if (bdGetLastError() != 0)
		return bdGetLastError();

	return cpuERR_CODE;
}

bool cpuResetErrors()
{
	bdResetErrors();
	cpuERR_CODE = 0;

	return true;
}

int SetPrec(string strPrec, int iOldT)
{
	if (CheckValidPrec(strPrec))
	{
		iMainPrec = StrToNum(strPrec);
		SetSize(iMainPrec);

		return iMainPrec;
	}
	else
	{
		cpuERR_CODE = ERROR_WRONG_PREC;

		return iOldT;
	}
}

bool dcless(char c, int ns)
{
	int n = 37;

	for (int i = 0; i <= 36; i++)
		if (c == DIG[i])
			n = i;

	if (n < ns)
		return true;
	else
		return false;
}

bool dcless_for(string s, int ns)
{
	ns = (ns < -1 ? -ns : (ns == 1 ? 2 : ns));

	if (ns > 36 || ns < 2)
	{
		cpuERR_CODE = ERROR_INVALID_NS;
		return false;
	}

	for (int i = 0; i < s.length(); i++)
	{
		if ((!dcless(s[i], ns)) && (s[i] != '.'))
		{
			cpuERR_CODE = ERROR_INVALID_VALUE;
			return false;
		}
	}

	return true;
}

string RoundZ(string strNumber)
{
	string strResult = strNumber;

	for (int rz = strNumber.length() - 1; rz >= 0; rz--)
	{
		if (strResult[rz] == '0')
			strResult.erase(rz, 1);
		else
		{
			if (strResult[strResult.length() - 1] == '.')
				strResult.erase(strResult.length() - 1, 1);
			return strResult;
		}
	}

	if (strResult[strResult.length() - 1] == '.')
		strResult.erase(strResult.length() - 1, 1);

	return strResult;
}

bool CheckValidPrec(string strPrecVal)
{
	int islen = strPrecVal.length();
	char BIT;
	string TMP = "";

	if (islen == 0)
	{
		cpuERR_CODE = ERROR_WRONG_PREC;
		return false;
	}

	for (int k = 0; k < islen; k++)
	{
		BIT = strPrecVal[k];
		TMP += strPrecVal[k];

		if (!dcless(BIT, 10))
		{
			cpuERR_CODE = ERROR_WRONG_PREC;
			return false;
		}
	}

	if (StrToNum(TMP) <= 0)
	{
		cpuERR_CODE = ERROR_WRONG_PREC;
		return false;
	}

	return true;
}

bool CheckValid(string &strValue, int iNS)
{
	cpuERR_CODE = ERROR_INVALID_VALUE;

	strValue += (strValue[strValue.length() - 1] == '.' ? "0" : "");

	int iStrLen = strValue.length();
	int iFCount = std::count(strValue.begin(), strValue.end(), '.');

	if (iFCount > 1)
	{
		cpuERR_CODE = ERROR_MORE_FLOAT;
		return false;
	}

	switch (iNS)
	{
	case ROMAN_NUMSYS:
	{
		if (iFCount > 0)
		{
			cpuERR_CODE = ERROR_ROMAN_SF;
			return false;
		}

		int M = std::count(strValue.begin(), strValue.end(), 'M');
		int D = std::count(strValue.begin(), strValue.end(), 'D');
		int C = std::count(strValue.begin(), strValue.end(), 'C');
		int L = std::count(strValue.begin(), strValue.end(), 'L');
		int X = std::count(strValue.begin(), strValue.end(), 'X');
		int V = std::count(strValue.begin(), strValue.end(), 'V');
		int I = std::count(strValue.begin(), strValue.end(), 'I');

		if (!(M || D || C || L || X || V || I))
			return false;

		break;
	}

	default:
	{
		return dcless_for(strValue, iNS);

		break;
	}
	}

	return cpuResetErrors();
}

char *ArabToRoman(unsigned short int arab)
{
	static char roman[80];
	const int m = sizeof(arabar) / sizeof(int) - 1, arabmax = arabar[m];
	const char romanmax = romanar[m][0];
	int i, n;

	if (!arab)
	{
		*roman = 0;
		return roman;
	}

	i = 0;

	while (arab > arabmax)
	{
		roman[i++] = romanmax;
		arab -= arabmax;
	}

	n = m;

	while (arab > 0)
	{
		if (arab >= arabar[n])
		{
			roman[i++] = romanar[n][0];

			if (n & 1)
				roman[i++] = romanar[n][1];

			arab -= arabar[n];
		}
		else
			n--;
	}

	roman[i] = 0;

	return roman;
}

unsigned short int RomanToArab(char *roman)
{
	const int m = sizeof(arabar) / sizeof(int) - 1;
	unsigned short int arab;
	int len, n, i, pir;

	len = strlen(roman);

	if (len > 4)
		return 11111;

	arab = 0;
	n = m;
	i = 0;

	while (n >= 0 && i < len)
	{
		pir = n & 1;

		if (roman[i] == romanar[n][0] && (!pir || roman[i + 1] == romanar[n][1]))
		{
			arab += arabar[n];
			i += 1 + pir;
		}
		else
			n--;
	}

	return arab;
}

// remove ints
string bfConvertFromDec(bdouble x, int NSYS, int T)
{
	string strRes = "0.";
	int a;

	while ((strRes.length() - 2) < T)
	{
		bdouble T1(NumToStr(NSYS));
		x = x * T1;

		// ������ floor - x.floor_out()
		a = (int)floor(StrToNum(x.print()));

		if (a >= 10)
			strRes += (char)(a - 10 + (int)'A');
		else
			strRes += (char)(a + (int)'0');

		bdouble T2(NumToStr(a));
		x = x - T2;
	}

	return strRes;
}

bdouble bfConvertToDec(string strNum, int NSYS)
{
	bdouble k(NumToStr(NSYS));
	bdouble x("0.0");

	for (int i = strNum.length() - 1; i > strNum.find('.'); i--)
	{
		int n = (int)strNum[i];

		if (n >= (int)'A')
			n = n - ((int)'A') + 10;
		else
			n -= (int)'0';

		bdouble nt(NumToStr(n));

		x = (x + nt) / k;
	}

	return x;
}

string DecToNegaNS(bdouble value, int iOutNS)
{
	string result = "";
	bdouble bdNS(NumToStr(iOutNS) + ".0");
	int n;

	while (zcmp(value) == 0)
	{
		bdouble remainder = value % bdNS;

		value = value / bdNS;

		string str = value.print();
		str.erase(str.find('.'), str.length());

		value = bdouble(str);

		if (cmp(remainder, bdouble("0.0")) == -1)
		{
			remainder = remainder + (-bdNS);
			value = value + bdouble("1.0");
		}

		string strt = RoundZ(remainder.print());

		n = (int)StrToNum(strt);

		if (n >= 10)
			result += (char)(n - 10 + (int)'A');
		else
			result += (char)(n + (int)'0');
	}

	return Reverse(result);
}

bdouble NegaNSToDec(string value, int iInNS)
{
	bdouble result;
	bdouble bdNS(NumToStr(iInNS) + ".0");

	int ilen = value.length();
	int c = 0;
	int n;

	for (int i = ilen - 1; i >= 0; i--)
	{
		n = (int)value[c];

		if (n >= (int)'A')
			n = n - ((int)'A') + 10;
		else
			n = n - (int)'0';

		bdouble x(NumToStr(n));

		result = result + (x * power(bdNS, i));

		c++;
	}

	return result;
}

string InitProcessor(string strValue, int iInNS, int iOutNS)
{
	bool bSigned = false;
	bool bFloat = false;
	int iFloatPos = 0;
	int iStrLen = strValue.length();

	string strResult = "0";

	if (!((iInNS <= 36) && (iInNS >= -36)) || !((iOutNS <= 36) && (iOutNS >= -36)))
	{
		cpuERR_CODE = ERROR_INVALID_NS;
		return "+";
	}

	if (iStrLen == 0)
	{
		cpuERR_CODE = ERROR_VALUE_EXPEC;
		return "+";
	}

	if (strValue[0] == '-')
	{
		bSigned = true;
		strValue[0] = '0';

		if (iInNS <= NEGA_POSITIONAL_NUMSYS)
		{
			cpuERR_CODE = ERROR_NEGA_NEGA;
			return "+";
		}
	}

	for (int its = 0; its < iStrLen; its++)
	{
		if ((strValue[its] == '.') || (strValue[its] == ','))
		{
			bFloat = true;
			iFloatPos = its;
		}
	}

	if (!CheckValid(strValue, iInNS))
		return "+";

	///
	/// parsing process:
	///
	/// roman to roman
	if ((iInNS == ROMAN_NUMSYS) && (iOutNS == ROMAN_NUMSYS))
	{
		if ((!bSigned) && (!bFloat))
		{
			unsigned short int ArabNum = RomanToArab(StrToCStr(strValue));

			if (ArabNum <= 3999)
				return strValue;
			else
			{
				cpuERR_CODE = ERROR_ROMAN_OUTOFRANGE;
				return "+";
			}
		}
		else
		{
			cpuERR_CODE = ERROR_ROMAN_SF;
			return "+";
		}
	}

	/// roman to nega-positional
	else if ((iInNS == ROMAN_NUMSYS) && (iOutNS <= NEGA_POSITIONAL_NUMSYS))
	{
		if ((!bSigned) && (!bFloat))
		{
			unsigned short int ArabNum = RomanToArab(StrToCStr(strValue));

			if (ArabNum > 3999)
			{
				cpuERR_CODE = ERROR_ROMAN_OUTOFRANGE;
				return "+";
			}

			string strRes = NumToStr(ArabNum);

			return DecToNegaNS(bdouble(strRes), iOutNS);
		}
		else
		{
			cpuERR_CODE = ERROR_ROMAN_SF;
			return "+";
		}
	}

	/// roman to positional
	else if ((iInNS == ROMAN_NUMSYS) && (iOutNS >= POSITIONAL_NUMSYS))
	{
		if ((!bSigned) && (!bFloat))
		{
			unsigned short int ArabNum = RomanToArab(StrToCStr(strValue));

			if (ArabNum > 3999)
			{
				cpuERR_CODE = ERROR_ROMAN_OUTOFRANGE;
				return "+";
			}

			Processor nslCPU(NumToStr(ArabNum), 10);
			strResult = nslCPU.Convert(iOutNS);

			return strResult;
		}
		else
		{
			cpuERR_CODE = ERROR_ROMAN_SF;
			return "+";
		}
	}

	/// roman to factorial
	/*
	else if ((iInNS == ROMAN_NUMSYS) && (iOutNS == FACTORIAL_NUMSYS)) {
		if ((!bSigned) && (!bFloat)) {
			unsigned short int ArabNum = RomanToArab(StrToCStr(strValue));

			if (ArabNum > 3999) { cpuERR_CODE = ERROR_ROMAN_OUTOFRANGE; return "+"; }

			Processor nslCPU (NumToStr(ArabNum), 10);
			strResult = nslCPU.Convert(iOutNS);

			/// to factorial ns

			return strResult;
		}
		else { cpuERR_CODE = ERROR_ROMAN_SF; return "+"; }

	}

	/// roman to fibonacci
	else if ((iInNS == ROMAN_NUMSYS) && (iOutNS == FIBONACCI_NUMSYS)) {
		if ((!bSigned) && (!bFloat)) {
			unsigned short int ArabNum = RomanToArab(StrToCStr(strValue));

			if (ArabNum > 3999) { cpuERR_CODE = ERROR_ROMAN_OUTOFRANGE; return "+"; }

			Fibonacci newFib;
			strResult = newFib.FibToStrBin(newFib.DecToFib(ArabNum));

			return strResult;
		}
		else { cpuERR_CODE = ERROR_ROMAN_SF; return "+"; }

	}
	*/

	/// nega-positional to roman
	else if ((iInNS <= NEGA_POSITIONAL_NUMSYS) && (iOutNS == ROMAN_NUMSYS))
	{
		if (bFloat)
		{
			cpuERR_CODE = ERROR_NEGA_FLOAT;
			return "+";
		} /// fix later

		bdouble x = NegaNSToDec(strValue, iInNS);
		strResult = RoundZ(x.print());

		if (strResult[0] == '-')
		{
			cpuERR_CODE = ERROR_ROMAN_SF;
			return "+";
		}
		if (cmp(x, bdouble("3999.0")) == 1)
		{
			cpuERR_CODE = ERROR_ROMAN_OUTOFRANGE;
			return "+";
		}

		return CStrToStr(ArabToRoman(StrToNum(strResult)));
	}

	/// nega-positional to nega-positional
	else if ((iInNS <= NEGA_POSITIONAL_NUMSYS) && (iOutNS <= NEGA_POSITIONAL_NUMSYS))
	{
		if (bFloat)
		{
			cpuERR_CODE = ERROR_NEGA_FLOAT;
			return "+";
		} /// fix later

		return DecToNegaNS(NegaNSToDec(strValue, iInNS), iOutNS);
	}

	/// nega-positional to positional
	else if ((iInNS <= NEGA_POSITIONAL_NUMSYS) && (iOutNS >= POSITIONAL_NUMSYS))
	{
		if (bFloat)
		{
			cpuERR_CODE = ERROR_NEGA_FLOAT;
			return "+";
		} /// fix later

		bool bSignedOut = false;

		bdouble x = NegaNSToDec(strValue, iInNS);
		string strRes = RoundZ(x.print());

		if (strRes[0] == '-')
		{
			strRes[0] = '0';
			bSignedOut = true;
		}

		Processor nslCPU(strRes, 10);
		strResult = nslCPU.Convert(iOutNS);

		if (bSignedOut)
			strResult.insert(0, 1, '-');

		return strResult;
	}

	/*
	/// nega-positional to factorial
	else if ((iInNS <= NEGA_POSITIONAL_NUMSYS) && (iOutNS == FACTORIAL_NUMSYS)) {
		if (bFloat) { cpuERR_CODE = ERROR_NEGA_FLOAT; return "+"; } /// fix later

		/// code here

	}

	/// nega-positional to fibonacci
	else if ((iInNS <= NEGA_POSITIONAL_NUMSYS) && (iOutNS == FIBONACCI_NUMSYS)) {
		if (bFloat) { cpuERR_CODE = ERROR_NEGA_FLOAT; return "+"; } /// fix later

		bool bSignedOut = false;

		bdouble x = NegaNSToDec(strValue, iInNS);
		strResult = RoundZ(x.print());

		if (strResult[0] == '-') { strResult[0] = '0'; bSignedOut = true; }

		Fibonacci newFib;
		int ir = newFib.DecToFib(StrToNum_S(strResult));

		if (ir == -1) { cpuERR_CODE = ERROR_FIB_OUTOFRANGE; return "+"; }

		strResult = newFib.FibToStrBin(ir);

		return ((bSignedOut ? "-" : "") + strResult);

	}
	*/

	/// positional to roman
	else if ((iInNS >= POSITIONAL_NUMSYS) && (iOutNS == ROMAN_NUMSYS))
	{
		if ((!bSigned) && (!bFloat))
		{
			Processor nslCPU(strValue, iInNS);
			strValue = nslCPU.Convert(10);

			if (cmp(bdouble(strValue), bdouble("3999.0")) == 1)
			{
				strResult = CStrToStr(ArabToRoman(StrToNum(strValue)));

				return strResult;
			}
			else
			{
				cpuERR_CODE = ERROR_ROMAN_OUTOFRANGE;
				return "+";
			}
		}
		else
		{
			cpuERR_CODE = ERROR_ROMAN_SF;
			return "+";
		}
	}

	/// positional to nega-positional
	else if ((iInNS >= POSITIONAL_NUMSYS) && (iOutNS <= NEGA_POSITIONAL_NUMSYS))
	{
		if (bFloat)
		{
			cpuERR_CODE = ERROR_NEGA_FLOAT;
			return "+";
		} /// fix later

		Processor nslCPU(strValue, iInNS);
		strResult = nslCPU.Convert(10);

		if (bSigned)
			strResult.insert(0, 1, '-');

		return DecToNegaNS(bdouble(strResult), iOutNS);
	}

	/// positional to positional
	else if ((iInNS >= POSITIONAL_NUMSYS) && (iOutNS >= POSITIONAL_NUMSYS))
	{
		if (!bFloat)
		{
			Processor nslCPU(strValue, iInNS);
			strResult = (bSigned ? "-" : "") + nslCPU.Convert(iOutNS);

			return strResult;
		}
		else
		{
			string FloatTS = "";
			string FloatOS = "0.";
			string FloatRES = "";

			for (int nnt = 0; nnt < iStrLen; nnt++)
			{
				if (nnt < iFloatPos)
					FloatTS += strValue[nnt];
				if (nnt > iFloatPos)
					FloatOS += strValue[nnt];
			}

			Processor nslCPU(FloatTS, iInNS);
			FloatRES = nslCPU.Convert(iOutNS);

			string FloatROS = bfConvertFromDec(bfConvertToDec(FloatOS, iInNS), iOutNS, iMainPrec);

			for (int nnt2 = 1; nnt2 < FloatROS.length(); nnt2++)
				FloatRES += FloatROS[nnt2];

			FloatRES = RoundZ(FloatRES);
			strResult = (bSigned ? string("-").append(FloatRES) : FloatRES);

			return strResult;
		}
	}

	/*
	/// positional to factorial
	else if ((iInNS >= POSITIONAL_NUMSYS) && (iOutNS == FACTORIAL_NUMSYS)) {

		if (bFloat) { cpuERR_CODE = ERROR_FACT_FLOAT; return "+"; }

		/// code here
		/// strResult = (bSigned ? "-" : "") + strResult;

		return strResult;

	}

	/// positional to fibonacci
	else if ((iInNS >= POSITIONAL_NUMSYS) && (iOutNS == FIBONACCI_NUMSYS)) {

		if (bFloat) { cpuERR_CODE = ERROR_FIB_FLOAT; return "+"; }

		Processor nslCPU (strValue, iInNS);
		strResult = nslCPU.Convert(10);

		Fibonacci newFib;
		int ir = newFib.DecToFib(StrToNum_S(strResult));

		if (ir == -1) { cpuERR_CODE = ERROR_FIB_OUTOFRANGE; return "+"; }

		strResult = (bSigned ? "-" : "") + newFib.FibToStrBin(ir);

		return strResult;

	}
	*/

	/*
	/// factorial to factorial
	else if ((iInNS == FACTORIAL_NUMSYS) && (iOutNS == FACTORIAL_NUMSYS)) {

		if (bFloat) { cpuERR_CODE = ERROR_FACT_FLOAT; return "+"; }

		return ((bSigned ? "-" : "") + TrimLeft(strValue));

	}

	/// factorial to roman
	else if ((iInNS == FACTORIAL_NUMSYS) && (iOutNS == ROMAN_NUMSYS)) {

		if (bFloat)  { cpuERR_CODE = ERROR_FACT_FLOAT; return "+"; }
		if (bSigned) { cpuERR_CODE = ERROR_ROMAN_SF;   return "+"; }

		/// code here

		return strResult;

	}

	/// factorial to nega-positional
	else if ((iInNS == FACTORIAL_NUMSYS) && (iOutNS <= NEGA_POSITIONAL_NUMSYS)) {

		if (bFloat) { cpuERR_CODE = ERROR_FACT_FLOAT; return "+"; }

		/// code here
		/// strInp = (bSigned ? "-" : "") + strInp;

		return strResult;

	}

	/// factorial to positional
	else if ((iInNS == FACTORIAL_NUMSYS) && (iOutNS >= POSITIONAL_NUMSYS)) {

		if (bFloat) { cpuERR_CODE = ERROR_FACT_FLOAT; return "+"; }

		/// code here
		strResult = (bSigned ? "-" : "") + strResult;

		return strResult;

	}

	/// factorial to fibonacci
	else if ((iInNS == FACTORIAL_NUMSYS) && (iOutNS == FIBONACCI_NUMSYS)) {

		if (bFloat) { cpuERR_CODE = ERROR_FACT_FLOAT; return "+"; }

		/// code here
		strResult = (bSigned ? "-" : "") + strResult;

		return strResult;

	}

	/// fibonacci to fibonacci
	else if ((iInNS == FIBONACCI_NUMSYS) && (iOutNS == FIBONACCI_NUMSYS)) {

		if (bFloat) { cpuERR_CODE = ERROR_FIB_FLOAT; return "+"; }

		return ((bSigned ? "-" : "") + TrimLeft(strValue));

	}

	/// fibonacci to roman
	else if ((iInNS == FIBONACCI_NUMSYS) && (iOutNS == ROMAN_NUMSYS)) {

		if (bFloat)  { cpuERR_CODE = ERROR_FIB_FLOAT; return "+"; }
		if (bSigned) { cpuERR_CODE = ERROR_ROMAN_SF;  return "+"; }

		Processor nslCPU (strValue, 2);
		strResult = nslCPU.Convert(10);

		Fibonacci newFib;
		int iResult = newFib.FibToDec(StrToNum_S(strResult));

		if (iResult == -1) { cpuERR_CODE = ERROR_FIB_OUTOFRANGE; return "+"; }
		else if (iResult > 3999) { cpuERR_CODE = ERROR_ROMAN_OUTOFRANGE; return "+"; }
		else {
			strResult = CStrToStr(ArabToRoman(iResult)); return strResult;
		}
	}

	/// fibonacci to nega-positional
	else if ((iInNS == FIBONACCI_NUMSYS) && (iOutNS <= NEGA_POSITIONAL_NUMSYS)) {

		if (bFloat) { cpuERR_CODE = ERROR_FIB_FLOAT; return "+"; }

		Processor nslCPU (strValue, 2);
		strResult = nslCPU.Convert(10);

		Fibonacci newFib;
		int ir = newFib.FibToDec(StrToNum_S(strResult));

		if (ir == -1) { cpuERR_CODE = ERROR_FIB_OUTOFRANGE; return "+"; }

		strResult = (bSigned ? "-" : "") + NumToStr(ir);

		return DecToNegaNS(bdouble (strResult), iOutNS);

	}

	/// fibonacci to positional
	else if ((iInNS == FIBONACCI_NUMSYS) && (iOutNS >= POSITIONAL_NUMSYS)) {

		if (bFloat) { cpuERR_CODE = ERROR_FIB_FLOAT; return "+"; }

		Processor nslCPU (strValue, 2);
		strResult = nslCPU.Convert(10);

		Fibonacci newFib;
		int ir = newFib.FibToDec(StrToNum_S(strResult));

		if (ir == -1) { cpuERR_CODE = ERROR_FIB_OUTOFRANGE; return "+"; }

		strResult = NumToStr(ir);
		Processor nslCPU2 (strResult, 10);

		return ((bSigned ? "-" : "") + nslCPU2.Convert(iOutNS));

	}

	/// fibonacci to factorial
	else if ((iInNS == FIBONACCI_NUMSYS) && (iOutNS == FACTORIAL_NUMSYS)) {

		if (bFloat) { cpuERR_CODE = ERROR_FIB_FLOAT; return "+"; }

		/// code here
		strResult = (bSigned ? "-" : "") + strResult;

		return strResult;

	}*/

	return strResult;
}
