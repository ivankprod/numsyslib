// Numeric System Library BigDouble Class

#include <cstring>
#include <string>

#include <math.h>

#include "bdouble.h"
#include "utils.h"

using std::string;
using std::max;
using std::min;

int DoubleSize = 4;
int bdERR_CODE = 0;

void SetSize(int iVal) { DoubleSize = iVal; }
int GetSize() { return DoubleSize; }
int bdGetLastError() { return bdERR_CODE; }
bool bdResetErrors()
{
	bdERR_CODE = 0;
	return true;
}

string strofchar(string C, int n)
{
	string RES = "";

	for (int i = 0; i < n; i++)
		RES.append(C);

	return RES;
}

vsint shift_left(vsint s, int k)
{
	if (k <= 0)
		return s;
	s.insert(s.begin(), k, 0);

	return s;
}

vsint shift_right(vsint s, int k)
{
	if (k <= 0)
		return s;
	s.erase(s.begin(), s.begin() + min(k, (int)s.sz));

	return s;
}

int cmp(vsint &a, vsint &b)
{
	for (int i = max(a.sz, b.sz) + 1; i >= 0; --i)
	{
		if (at(a, i) > at(b, i))
			return 1;
		if (at(a, i) < at(b, i))
			return -1;
	}

	return 0;
}

int zcmp(vsint &a)
{
	for (int i = 0; i < a.sz; i++)
	{
		if (a[i] != 0)
			return 0;
	}

	return 1;
}

vsint add(vsint &a, vsint &b)
{
	vsint c(max(a.sz, b.sz) + 1, 0);

	for (int i = 0; i < c.sz - 1; ++i)
	{
		c[i] += at(a, i) + at(b, i);
		next_mod(c, i);
	}

	erase_null(c);
	return c;
}

vsint sub(vsint &a, vsint &b)
{
	vsint c(a.sz, 0);

	for (int i = 0; i < c.sz; ++i)
	{
		c[i] += at(a, i) - at(b, i);

		if (c[i] < 0 && i + 1 < c.sz)
		{
			c[i] += 10;
			--c[i + 1];
		}
	}

	erase_null(c);
	return c;
}

void sub_from(vsint &a, vsint &b)
{
	for (int i = 0; i < a.sz; ++i)
	{
		a[i] -= at(b, i);

		if (a[i] < 0 && i + 1 < a.sz)
		{
			a[i] += 10;
			--a[i + 1];
		}
	}

	erase_null(a);
}

vsint mul(vsint &a, vsint &b)
{
	vsint c(a.sz + b.sz + 2, 0);

	for (int i = 0; i < a.sz; ++i)
	{
		for (int j = 0; j < b.sz; ++j)
		{
			c[i + j] += a[i] * b[j];
			next_mod(c, i + j);
		}
	}

	for (int i = 0; i < c.sz; ++i)
		next_mod(c, i);

	erase_null(c);
	return c;
}
vsint div(vsint &a, vsint &b, vsint &r)
{
	r.assign(1, 0);
	vsint s(a.sz, 0);

	for (int i = a.sz - 1; i >= 0; --i)
	{
		r.insert(r.begin(), a[i]);

		while (cmp(r, b) >= 0)
		{
			++s[i];
			sub_from(r, b);
		}
	}

	erase_null(s);
	erase_null(r);
	return s;
}

vsint sqrt(vsint &a)
{
	int n = (a.size() + 1) / 2;

	vsint x(n, 0);

	for (int i = n - 1; i >= 0; --i)
	{
		for (x[i] = 9; x[i] > 0; --x[i])
		{
			vsint xx = mul(x, x);
			if (cmp(xx, a) <= 0)
				break;
		}
	}

	return x;
}

void bdouble::sscan(string s)
{
	sign = 1;
	if (s[0] == '-')
	{
		sign = -1;
		s = s.substr(1);
	}

	int i, j;
	int n = s.size();
	int z = s.find('.');
	if (z == string::npos)
		z = n;

	a.assign(DoubleSize, 0);
	for (i = z + 1; i < n; ++i)
		a[DoubleSize - (i - (z + 1)) - 1] = s[i] - '0';
	for (i = z - 1; i >= 0; --i)
		a.push_back(s[i] - '0');
}

void bdouble::normal()
{
	while (a.sz < DoubleSize + 1)
		a.push_back(0);
}

string bdouble::print()
{
	string output = "";

	if (sign < 0)
		output = "-";

	for (int i = a.sz - 1; i >= 0; --i)
	{
		output.append(NumToStr(a[i]));

		if (i == DoubleSize)
			output.append(".");
	}

	return output;
}

bdouble operator-(bdouble a)
{
	a.sign = -a.sign;

	return a;
}

int cmp(bdouble a, bdouble b)
{
	if (a.sign > b.sign)
		return 1;
	if (a.sign < b.sign)
		return -1;

	return cmp(a.a, b.a) * a.sign;
}

int zcmp(bdouble a) { return zcmp(a.a); }

bdouble operator+(bdouble a, bdouble b)
{
	if (a.sign != b.sign)
	{
		if (b.sign < 0)
			return a - (-b);
		else
			return b - (-a);
	}

	bdouble c;
	c.a = add(a.a, b.a);
	c.sign = a.sign;
	c.normal();

	return c;
}

bdouble operator-(bdouble a, bdouble b)
{
	if (cmp(a, b) < 0)
		return -(b - a);
	if (b.sign < 0)
		return a + (-b);

	bdouble c;
	c.a = sub(a.a, b.a);
	c.sign = 1;
	c.normal();

	return c;
}

bdouble operator*(bdouble a, bdouble b)
{
	bdouble c;

	c.a = mul(a.a, b.a);
	c.a = shift_right(c.a, DoubleSize);
	c.sign = a.sign * b.sign;
	c.normal();

	return c;
}

bdouble operator/(bdouble a, bdouble b)
{
	bdouble c;

	if (zcmp(b))
	{
		bdERR_CODE = 5;
		return c;
	}

	a.a = shift_left(a.a, DoubleSize);
	vsint r;

	c.a = div(a.a, b.a, r);
	c.sign = a.sign * b.sign;
	c.normal();

	return c;
}

bdouble operator%(bdouble a, bdouble b)
{
	bdouble c;

	if (zcmp(b))
	{
		bdERR_CODE = 5;
		return c;
	}

	c = a / b;

	string str = c.print();
	str.erase(str.find('.'), str.length());

	c = bdouble(str);

	return a - (c * b);
}

bdouble bsqrt(bdouble a)
{
	bdouble x;

	a.a = shift_left(a.a, DoubleSize);
	x.a = sqrt(a.a);
	x.sign = 1;
	x.normal();

	return x;
}

bdouble power(bdouble a, int n)
{
	bdouble result("1.0");

	for (int na = abs(n); na > 0; na >>= 1)
	{
		if (na % 2 == 1)
		{
			result = result * a;
		}

		a = a * a;
	}

	return n < 0 ? bdouble("1.0") / result : result;
}
