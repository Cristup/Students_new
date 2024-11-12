#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <random>

class student {
private:
	std::string name_;
	std::string surname_;
	std::vector<int> homeworks_;
	int exam_;
	double final_average_;
	double final_median_;

	double final_ave(std::vector<int> homeworks, int exam);
	double final_med(std::vector<int> homeworks, int exam);

public:
	student(std::string name, std::string surname, std::vector<int> homeworks, int exam);
	student(std::string name, std::string surname);
	inline std::string name() const { return name_; }
	inline std::string surname() const { return surname_; }
	inline double final_average() const { return final_average_; }
	inline double final_median() const { return final_median_; }

	/*
	COMPARATORS
*/

	int nam_sur(const student& a, const student& b);

	int nam_ave(const student& a, const student& b);

	int nam_med(const student& a, const student& b);

	int sur_nam(const student& a, const student& b);

	int sur_ave(const student& a, const student& b);

	int sur_med(const student& a, const student& b);

	int ave_nam(const student& a, const student& b);

	int ave_sur(const student& a, const student& b);

	int ave_med(const student& a, const student& b);

	int med_nam(const student& a, const student& b);

	int med_sur(const student& a, const student& b);

	int med_ave(const student& a, const student& b);

	int nam(const student& a, const student& b);

	int sur(const student& a, const student& b);

	int ave(const student& a, const student& b);

	int med(const student& a, const student& b);
};

#endif