// Numeric System Library Strings Module

#ifndef STRINGS_H
#define STRINGS_H

#include <string>

using std::string;

const string NSL_VERSION = "1.4.5";

enum
{
	// Invalid value specified
	ERROR_INVALID_VALUE = 1,
	// More than one fractional divider
	ERROR_MORE_FLOAT = 2,
	// The fractional part expected
	ERROR_WAITING_FLOAT = 3,
	// Invalid precision specified
	ERROR_WRONG_PREC = 4,
	// Division by zero
	ERROR_DIVIDE_BY_ZERO = 5,
	// Invalid numeral system specified
	ERROR_INVALID_NS = 6,
	// Negative and float numbers aren't exist in roman ns
	ERROR_ROMAN_SF = 7,
	// Out of range in roman ns
	ERROR_ROMAN_OUTOFRANGE = 8,
	// Negative numbers aren't exist in nega-pos ns
	ERROR_NEGA_NEGA = 9,
	// Value expected
	ERROR_VALUE_EXPEC = 10,
	// Fibonacci out of range table
	ERROR_FIB_OUTOFRANGE = 11,
	// Float numbers aren't supported in nega-pos ns
	ERROR_NEGA_FLOAT = 12,
	// Float numbers aren't exist in factorial ns
	ERROR_FACT_FLOAT = 13,
	// Float numbers aren't exist in fibonacci ns
	ERROR_FIB_FLOAT = 14
};

#endif
