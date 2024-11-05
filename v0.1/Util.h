#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "Mylib.h"

/*	Mean of a vector.
*/
double Average(vector<int> nd);

/*	Median of a vector.
*/
double Median(vector<int> nd);

/*	Final result calculation.
*/
double Result(int egz, double value);

/*	Function returns:
*		TRUE if all symbols in the string are numbers.
*		FALSE if there's at least one symbol other than number in the string
*/
bool is_digits(string str);

#endif