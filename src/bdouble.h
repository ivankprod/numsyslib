
/*
  	Numeric System™ Library BigDouble Class
  	
  	© 2008-2016 IvanK Production
*/

#ifndef _BDOUBLE_H_
#define _BDOUBLE_H_

#include "utils.h"

#include <vector>

#define forp(i, a, b, c) for (i = (a); (c) > 0 ? i <= (b) : i >= (b); i += (c))
#define forn(i, n) forp(i, 0, (n) - 1, 1)
#define form(i, n) forp(i, (n) - 1, 0, - 1)
#define forv(it, v) for(it = (v).begin(); it != (v).end(); ++ it)

#define uint long long

#define sint int
#define vsint vector<sint>
#define sz size()
#define at(v, i) (0 <= (i) && (i) < (v).size() ? v[i] : 0)
#define erase_null(v) while ((v).size() > 1 && (v).back() == 0) (v).pop_back();
#define next_mod(v, i) if (0 <= (i) + 1 && (i) + 1 < (v).size()) { v[(i) + 1] += v[(i)] / 10; v[(i)] %= 10; }

using std::string;
using std::vector;

void  SetSize(int);
int   GetSize();
int   bdGetLastError();
bool  bdResetErrors();

class bdouble {
public:
    vsint a;
    char sign;
    
    bdouble(string str_val = "0.0") {
	    sscan(str_val);
	}
    
    void   sscan(string s);
    void   normal();
    string print();

    friend bdouble operator - (bdouble a);    
    friend int cmp(bdouble a, bdouble b);
    friend int zcmp(bdouble a);
    friend bdouble power(bdouble a, int n);
    
    bdouble operator = (const bdouble &bdVal) {
    	this->a = bdVal.a;
    	this->sign = bdVal.sign;
    	
    	return bdVal;
	}
    
    friend bdouble operator + (bdouble a, bdouble b);
    friend bdouble operator - (bdouble a, bdouble b);
    friend bdouble operator * (bdouble a, bdouble b);
    friend bdouble operator / (bdouble a, bdouble b);
    friend bdouble operator % (bdouble a, bdouble b);
};

#endif

