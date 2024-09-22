#pragma once

#include "Mylib.h"

void Sort(vector<int>& vec)
{
	for (int i = 0; i < vec.size() - 1; i++) {
		for (int j = i + 1; j < vec.size(); j++) {
			if (vec[j] < vec[i]) {
				swap(vec[j], vec[i]);
			}
		}
	}
}

double Average(vector<int> nd)
{
	if (nd.empty()) {
		throw std::invalid_argument("Vector is empty");
	}
	int sum = 0;
	for (int i = 0; i < nd.size(); i++){
		sum += nd[i];
	}
	return (double) sum / nd.size();
}

double Median(vector<int> nd)
{
	if (nd.empty()) {
		throw std::invalid_argument("Vector is empty");
	}
	int n = nd.size(); //vector length
	Sort(nd);
	if (n % 2 != 0) {
		return nd[n / 2];
	}
	else {
		return (double) (nd[n / 2 - 1] + nd[n / 2]) / 2;
	}
}

double Result(int egz, double value)
{
	return 0.4 * value + 0.6 * egz;
}

bool is_digits(string str)
{
	for (char ch : str) {
		int value = ch;
		if (!(ch >= 48 && ch <= 57)) {
			return false;
		}
	}
	return true;
}