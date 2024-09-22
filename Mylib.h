#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <random>
#include <fstream>

#include <chrono>

using std::vector;
using std::string;
using std::ifstream;
using std::cout;
using std::cin;
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

std::random_device rd;
std::uniform_int_distribution<int> dist(1, 10);