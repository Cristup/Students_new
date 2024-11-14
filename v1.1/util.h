#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "libs.h"
#include "student.h"
#include "timer.h"

struct File_info {
	string name;
	size_t size;
};

struct Directory_files {
	int id;
	string name;
	enum types { Data, Results } type;
};

struct Record {

	double input = 0.0;
	double sorting = 0.0;
	double categorising = 0.0;
	double output = 0.0;
	double total = 0.0;
	int	   count = 0;
};

struct Test_data {
	map<string, Record> vec_test;
	map<string, Record> list_test;
	map<string, double> fg_durations;
};

enum selection {
	Average,
	Median,
	Both
};

enum strategy {
	s1 = 1, s2 = 2, s3 = 3
};

enum container_types {
	Vector,
	List
};

void update_info(stringstream& info, const enum container_types& type);

void update_files(vector<Directory_files>& files);

void table(const vector<Directory_files> files);

bool is_data_file(const string& filename);

void get_type(const enum container_types& type);

bool is_digits(const string& str);

void progress_clock(const size_t& lines);

void find_keys(string& line, const enum selection& print_by, size_t& n_keys, vector<string>& keys);

enum selection print_selection();

string sort_selection(const enum selection& print_by);

void create_file_selection(vector<File_info>& files);

void file_selection(vector<string>& files);

enum strategy cycle_strat(enum strategy& strat);

#endif
