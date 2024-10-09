#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "Mylib.h"
#include "Stud.h"

/*	Mean of a vector.
*/
double Average(const vector<int>& nd);

/*
*/
double Mean(const vector<double>& vec);

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

/*	Function for program testing
*/
void test_multiple_files();

/*	Function to find valid keys in a string
*/
void find_keys(string& line, vector<string>& keys);

#endif