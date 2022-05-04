// Numeric System Library Strings Module

#ifndef STRINGS_H
#define STRINGS_H

#include <string>

using std::string;

const string NSL_VERSION = "1.5.0";

enum
{
	// Invalid value specified
	ERROR_INVALID_VALUE = 1,
	// More than one fractional divider
	ERROR_MORE_FLOAT = 2,
	// Invalid precision specified
	ERROR_WRONG_PREC = 3,
	// Division by zero
	ERROR_DIVIDE_BY_ZERO = 4,
	// Invalid numeral system specified
	ERROR_INVALID_NS = 5,
	// Negative and float numbers aren't exist in roman ns
	ERROR_ROMAN_SF = 6,
	// Out of range in roman ns
	ERROR_ROMAN_OUTOFRANGE = 7,
	// Negative numbers aren't exist in nega-pos ns
	ERROR_NEGA_NEGA = 8,
	// Value expected
	ERROR_VALUE_EXPEC = 9,
	// Fibonacci out of range table
	ERROR_FIB_OUTOFRANGE = 10,
	// Float numbers aren't supported in nega-pos ns
	ERROR_NEGA_FLOAT = 11,
	// Float numbers aren't exist in factorial ns
	ERROR_FACT_FLOAT = 12,
	// Float numbers aren't exist in fibonacci ns
	ERROR_FIB_FLOAT = 13
};

#endif
