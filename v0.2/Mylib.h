#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <mutex>
#include <thread>
#include <numeric>
#include <functional>
#include <map>

#include <chrono>

using std::vector;
using std::string;
using std::ostringstream;
using std::stringstream;
using std::istringstream;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::map;

using std::numeric_limits;
using std::streamsize;

using std::exception;
using std::invalid_argument;
using std::out_of_range;
using std::runtime_error;

using std::random_device;
using std::uniform_int_distribution;

using std::mutex;
using std::lock_guard;
using std::thread;
using std::ref;

using std::chrono::high_resolution_clock;
using std::chrono::duration;

using std::cout;
using std::cin;
using std::cerr;

using std::log10;
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