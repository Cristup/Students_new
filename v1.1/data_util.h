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

void generate_file(const string& filename, const int& size);

void create_multiple_files(vector<File_info>& files);

#endif