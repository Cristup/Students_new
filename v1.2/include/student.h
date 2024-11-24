#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <random>
#include <list>
#include <map>
#include <type_traits>
#include <ppl.h>
#include <iomanip>

class student {

	friend std::ostream& operator<<(std::ostream& os, const student& s);

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
	student() : name_(""), surname_(""), homeworks_({}), exam_(0), final_average_(0), final_median_(0) {}
	student(const student& other) : name_(other.name_), surname_(other.surname_),
		homeworks_(other.homeworks_), exam_(other.exam_), final_average_(other.final_average_), final_median_(other.final_median_) {}
	~student() {
		homeworks_.clear();
	};

	inline void setName(const std::string& name) { name_ = name; }
	inline void setSurname(const std::string& surname) { surname_ = surname; }
	inline void setHomework(const std::vector<int>& homework) { homeworks_ = homework; }
	inline void setExam(const int& exam) { exam_ = exam; }

	inline std::string name() const { return name_; }
	inline std::string surname() const { return surname_; }
	inline std::vector<int> homeworks() const { return homeworks_; }
	inline int exam() const { return exam_; }
	inline double final_average() const { return final_average_; }
	inline double final_median() const { return final_median_; }

	student& operator=(const student& other) {
		if (this == &other) return *this;
		name_ = other.name_;
		surname_ = other.surname_;
		homeworks_ = other.homeworks_;
		exam_ = other.exam_;
		final_average_ = other.final_average_;
		final_median_ = other.final_median_;
		return *this;
	}

};

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

template<typename T>
void sort_students(T& Students, const std::string& key);
template void sort_students<std::vector<student>>(std::vector<student>& Students, const std::string& key);
template void sort_students<std::list<student>>(std::list<student>& Students, const std::string& key);

#endif