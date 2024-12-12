#ifndef DATA_UTIL_H_INCLUDED
#define DATA_UTIL_H_INCLUDED

#include "libs.h"
#include "student.h"
#include "util.h"
#include "timer.h"

template<typename Container>
void Input_from_file(Container& local, const string& filename);
template void Input_from_file<vector<student>>(vector<student>& local, const string& filename);
template void Input_from_file<list<student>>(list<student>& local, const string& filename);

template<typename T>
void output_to_file(T& local, const string& filename, const enum selection& print_by);
template void output_to_file<vector<student>>(vector<student>& local, const string& filename, const enum selection& print_by);
template void output_to_file<list<student>>(list<student>& local, const string& filename, const enum selection& print_by);

template<typename T>
void output_to_screen(T& local);
template void output_to_screen<vector<student>>(vector<student>& local);
template void output_to_screen<list<student>>(list<student>& local);

template<typename T>
void manual_input(T& container);
template void manual_input<vector<student>>(vector<student>& container);
template void manual_input<list<student>>(list<student>& container);

void homework_input(vector<int>& homework);

void generate_file(const string& filename, const int& size);

void create_multiple_files(vector<File_info>& files);

void markdown_table();

void test_multiple_files(const vector<string>& files, const enum selection& print_by,
	const string& key, const enum container_types& c_type, const enum strategy& strat);

template<typename T>
void sort_to_categories(T& local, T& Under, T& Over);
template void sort_to_categories<vector<student>>(vector<student>& local, vector<student>& Under, vector<student>& Over);
template void sort_to_categories<list<student>>(list<student>& local, list<student>& Under, list<student>& Over);

template<typename T>
void sort_to_categories2(T& firstc, T& newc);
template void sort_to_categories2<vector<student>>(vector<student>& firstc, vector<student>& newc);
template void sort_to_categories2<list<student>>(list<student>& firstc, list<student>& newc);

template<typename T>
void sort_to_categories3(T& local, T& over);
template void sort_to_categories3<vector<student>>(vector<student>& local, vector<student>& over);
template void sort_to_categories3<list<student>>(list<student>& local, list<student>& over);


#endif