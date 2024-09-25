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
	string	vardas;		//- student name;
	string	pavarde;	//- student last name;
	vector<int> nd;		//- vector for storing home work marks;
	int		egz;		//- exam result;
	double	vid;		//- average value of all homework marks;
	double	med;		//- median value of all homework marks.
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

/*	Data table printing in terminal:
		Name, Surname, Final result using
		Average and Median values.
*/
void output(vector<Stud> local);

/*	Data table writing in file:
		Name, Surname, Final result using
		Average and Median values.	
*/
void output_to_file(vector<Stud> local);

/*	Reading students data from a file to Stud structure
*		Function counts number of homeworks;
*		Then reads all data in a single line;
*		Then counts Average and Median values;
*		Then pushes data to Students vector;
*		And repeats until the end of the file.
*/
void Input_from_file(vector<Stud>& local, string filename);

/*	Function for sorting all students:
*		First by name,
*		If names are the same
		then by surname
*/
void sort_students(vector<Stud>& local);

#endif