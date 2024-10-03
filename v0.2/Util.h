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

/*	Function for creating test file
	Precondition:
*		filename - data output file
*		size - number of lines
*/
//void create_test_file(string filename, int size);

/*	Function for creating test data
*	Precondition:
		filename - data output file
		start - First index of students
		stop - Last index
*	Postcondition:
		File with stop - start lines and
		student names, surnames and random homework and exam results
*/
void create_data_chuncked(string filename, int start, int stop);

/*	Function for spliting test data generation into threads
*/
void create_data(string filename, int size);

#endif