#ifndef STUD_H_INCLUDED
#define STUD_H_INCLUDED

#include "Mylib.h"
#include "Util.h"

/*	Structure for students data:
*		vardas	- student name;
*		pavarde - student last name;
*		nd		- vector for storing home work marks;
*		egz		- exam result;
*		vid		- average value of all homework marks;
*		med		- median value of all homework marks.
*/
struct Stud {
	string		vardas,		//- student name;
				pavarde;	//- student last name;
	vector<int> nd;			//- vector for storing home work marks;
	int			egz;		//- exam result;
	double		final_vid,	//- final result using average value of homeworks;
				final_med;	//- final result using median value of homeworks;
	enum category { Under, Over } cat;// Under if result < 5 and Over if result >= 5.
};

/*	Function for deleting students data:
*		Name, Surname & Homework vector.
*
	Precondition:
*		local - type Stud argument.
*/
void clean(Stud& local);

/*	Function that generates and inputs values from
*		uniform distribution to Students structure.
*		Also, prints generated values to terminal.
*
	Generated values:
*		Exam result in interval [1;10];
*		Number of homeworks in interval [5;15];
*		Homework marks in interval [1;10].
*/
void Automatic_input(Stud& local);

/*	Function for entering x homework marks in
*		terminal and managing user input.
*
	Data is writen to Stud.nd vector until
*		user presses Enter twice.
*
	Function checks if:
*		there is at least one value provided by user;
*		value is an integer;
*		value isn't something else;
*		value is in interval [1;10].
*/
void Manual_input(Stud& local);

/*	Function for sorting all students by key:
		Students - data container
		key - comparator
*/
template<typename T>
void sort_students(T& Students, const string& key);

/*	Function for sorting Students vector into two separate vectors by category.
*/
template<typename T>
void sort_to_categories(T& local, T& Under, T& Over);

template<typename T>
void sort_to_categories2(T& firstc, T& newc);

template<typename T>
void sort_to_categories3(T& local, T& Under, T& Over);

/*	Function for data input in terminal.
*		local - type Stud argument for single student data.
	Part 1:
*		Name & Surname input to local structure
	Part 2:
*		Either exam result or 'auto' choice
*		and input managing.
		Part 2.1:
*			If user provided good exam result value,
*			then it is directed to Manual_input() function.
		Part 2.2:
*			User chose to generate data, in which case
*			Automatic_input() function is called.
	Part 3:
*		Finnaly function calculates Average and Median
*		values and saves them in local sstructure.
*/
void input(Stud& local);

/*	Data table writing in file:
		Name, Surname, Final result using
		Average and/or Median values based on `print_by`.
		Printing to file named `filename`
*/
template<typename T>
void output_to_file(T& local, const string& filename, const enum selection& print_by);

/*	Reading students data from a file to Stud structure
		and checking for errors.
*		Function counts number of homeworks;
*		Then reads all data in a single line;
*		Then counts Average and Median values;
*		Then pushes data to Students vector;
*		And repeats until the end of the file.
*/
template<typename Container>
void Input_from_file(Container& local, const string& filename);

template<typename T>
int find_in_container(const T& container, const Stud& element);

/*
	CONSTRUCTING FUNCTIONS
*/
//With vector<>
template void Input_from_file<vector<Stud>>(vector<Stud>& local, const string& filename);
template void output_to_file<vector<Stud>>(vector<Stud>& local, const string& filename, const enum selection& print_by);
template void sort_students<vector<Stud>>(vector<Stud>& Students, const string& key);
template void sort_to_categories<vector<Stud>>(vector<Stud>& local, vector<Stud>& Under, vector<Stud>& Over);
template void sort_to_categories2<vector<Stud>>(vector<Stud>& firstc, vector<Stud>& newc);
template void sort_to_categories3<vector<Stud>>(vector<Stud>& local, vector<Stud>& Under, vector<Stud>& Over);
template int find_in_container<vector<Stud>>(const vector<Stud>& container, const Stud& element);
//With list<>
template void Input_from_file<list<Stud>>(list<Stud>& local, const string& filename);
template void output_to_file<list<Stud>>(list<Stud>& local, const string& filename, const enum selection& print_by);
template void sort_students<list<Stud>>(list<Stud>& Students, const string& key);
template void sort_to_categories<list<Stud>>(list<Stud>& local, list<Stud>& Under, list<Stud>& Over);
template void sort_to_categories2<list<Stud>>(list<Stud>& firstc, list<Stud>& newc);
template void sort_to_categories3<list<Stud>>(list<Stud>& local, list<Stud>& Under, list<Stud>& Over);
template int find_in_container<list<Stud>>(const list<Stud>& container, const Stud& element);

/*
	COMPARATORS
*/

int nam_sur(const Stud& a, const Stud& b);

int nam_ave(const Stud& a, const Stud& b);

int nam_med(const Stud& a, const Stud& b);

int sur_nam(const Stud& a, const Stud& b);

int sur_ave(const Stud& a, const Stud& b);

int sur_med(const Stud& a, const Stud& b);

int ave_nam(const Stud& a, const Stud& b);

int ave_sur(const Stud& a, const Stud& b);

int ave_med(const Stud& a, const Stud& b);

int med_nam(const Stud& a, const Stud& b);

int med_sur(const Stud& a, const Stud& b);

int med_ave(const Stud& a, const Stud& b);

int nam(const Stud& a, const Stud& b);

int sur(const Stud& a, const Stud& b);

int ave(const Stud& a, const Stud& b);

int med(const Stud& a, const Stud& b);

#endif