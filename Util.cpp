#include "Util.h"

double Average(vector<int> nd)
{
	int sum = 0;
	for (int i = 0; i < nd.size(); i++) {
		sum += nd[i];
	}
	return (double)sum / nd.size();
}

double Median(vector<int> nd)
{
	int n = nd.size();
	sort(nd.begin(), nd.end());
	if (n % 2 != 0) {
		return nd[n / 2];
	}
	else {
		return (double)(nd[n / 2 - 1] + nd[n / 2]) / 2;
	}
}

double Result(int egz, double value)
{
	return 0.4 * value + 0.6 * egz;
}

bool is_digits(string str)
{
	for (char ch : str) {
		//converting to number
		int value = ch;
		//checking if symbols isn't a number
		if (!(ch >= 48 && ch <= 57)) {
			return false;
		}
	}
	return true;
}