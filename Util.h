#pragma once

#include "Mylib.h"

void Sort(vector<int>& vec)
{
	int temp;
	for (int i = 0; i < vec.size() - 1; i++) {
		for (int j = i + 1; j < vec.size(); j++) {
			if (vec[j] < vec[i]) {
				temp = vec[j];
				vec[j] = vec[i];
				vec[i] = temp;
			}
		}
	}
}

double Average(vector<int> nd)
{
	int sum = 0;
	for (int i = 0; i < nd.size(); i++){
		sum += nd[i];
	}
	return (double) sum / nd.size();
}

double Median(vector<int> nd)
{
	int n = nd.size(); //vector length
	Sort(nd);
	if (n % 2 != 0) {
		return nd[n / 2];
	}
	else {
		return (double) (nd[n / 2 - 1] + nd[n / 2]) / 2;
	}
}

double Result(int egz, double avg)
{
	return 0.4 * avg + 0.6 * egz;
}