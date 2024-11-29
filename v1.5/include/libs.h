#ifndef LIBS_H_INCLUDED
#define LIBS_H_INCLUDED

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <numeric>
#include <functional>
#include <map>
#include <list>
#include <type_traits>
#include <ppl.h>
#include <thread>
#include <direct.h>
#include <chrono>

using std::vector;
using std::list;
using std::string;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::map;
using std::function;

using std::numeric_limits;
using std::streamsize;
using std::is_same;

using std::exception;
using std::invalid_argument;
using std::out_of_range;
using std::runtime_error;

using std::random_device;
using std::uniform_int_distribution;

using std::chrono::high_resolution_clock;
using std::chrono::duration;

using std::cout;
using std::cin;
using std::cerr;

using std::log10;
using std::to_string;
using std::pow;
using std::count;
using std::distance;
using std::accumulate;
using std::endl;
using std::setw;
using std::fixed;
using std::setprecision;
using std::left;
using std::sort;
using std::swap;
using std::transform;
using std::stoi;
using std::getline;

#endif