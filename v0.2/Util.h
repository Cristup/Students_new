#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "Mylib.h"
#include "Stud.h"
#include "timer.h"

struct File_info {
	string name;
	size_t size;
};

enum selection {
	Average,
	Median,
	Both
};

/*	Mean of a type int vector.
*/
double average_int(const vector<int>& nd);

/*	Median of a vector.
*/
double median(vector<int> nd);

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
		File with (stop - start) lines and
		student names, surnames and random homework and exam results
*/
void create_data_chuncked(const string& filename, const int& start, const int& stop);

/*	Function for spliting test data generation into threads
*/
void create_data(const string& filename, const int& size);

/*	Function for creating test files:
*		files.name - file name
*		files.size - file size
*/
void create_multiple_files(const vector<File_info>& files);

/*	Function for program testing
*/
void test_multiple_files(const vector<string>& files, const enum selection& print_by, const string& key);

/*	Function to find valid keys in a string
*/
void find_keys(string& line, const enum selection& print_by, size_t& n_keys, vector<string>& keys);

/*	Finding valid keys in a string
*/
enum selection print_selection();

/*
*/
string sort_selection(const enum selection& print_by);

/*
*/
void create_file_selection(vector<File_info>& files);

/*
*/
void file_selection(vector<string>& files);

#endif