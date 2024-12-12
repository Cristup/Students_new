#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include "../include/libs.h"

struct Record {

	double input = 0.0;
	double sorting = 0.0;
	double categorising = 0.0;
	double output = 0.0;
	double total = 0.0;
	int	   count = 0;
};

bool is_digits(const string& str)
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

#endif