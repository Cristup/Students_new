#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "Mylib.h"

/*	Mean of a vector.
*/
double Average(const vector<int>& nd);

/*	Median of a vector.
*/
double Median(vector<int> nd);

/*	Final result calculation.
*/
double Result(const int& egz, const double& value);

/*	Function returns:
*		TRUE if all symbols in the string are numbers.
*		FALSE if there's at least one symbol other than number in the string
*/
bool is_digits(const string& str);

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
void create_data_chuncked(const string& filename, const int& start, const int& stop);

/*	Function for spliting test data generation into threads
*/
void create_data(const string& filename, const int& size);

#endif