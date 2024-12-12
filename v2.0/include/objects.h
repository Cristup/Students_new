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

class person {
protected:
	std::string name_;
	std::string surname_;

	person(const std::string& name, const std::string surname)
		: name_(name), surname_(surname) {}

public:

	virtual ~person() = default;

	virtual std::string name() const = 0;
	virtual std::string surname() const = 0;

};

class student : public person {

private:
	std::vector<int> homeworks_;
	int exam_;
	double final_average_;
	double final_median_;
	double final_ave(std::vector<int> homeworks, int exam);
	double final_med(std::vector<int> homeworks, int exam);
public:
	student();
	student(std::string name, std::string surname, std::vector<int> homeworks, int exam);
	student(const student& other);
	~student();

	inline void setName(const std::string& name) { name_ = name; }
	inline void setSurname(const std::string& surname) { surname_ = surname; }
	inline void setHomework(const std::vector<int>& homework) { homeworks_ = homework; }
	inline void setExam(const int& exam) { exam_ = exam; }

	inline std::string name() const override { return name_; }
	inline std::string surname() const  override { return surname_; }
	inline std::vector<int> homeworks() const { return homeworks_; }
	inline int exam() const { return exam_; }
	inline double final_average() const { return final_average_; }
	inline double final_median() const { return final_median_; }

	student& operator=(const student& other);

};

student::student() :
	person("", ""),
	homeworks_({}),
	exam_(0),
	final_average_(0),
	final_median_(0)
{}

student::student(std::string name, std::string surname, std::vector<int> homeworks, int exam) :
	person(name, surname),
	homeworks_(homeworks),
	exam_(exam),
	final_average_(final_ave(homeworks, exam)),
	final_median_(final_med(homeworks, exam))
{}

student::student(const student& other) :
	person(other),
	homeworks_(other.homeworks_),
	exam_(other.exam_),
	final_average_(other.final_average_),
	final_median_(other.final_median_)
{
	//std::cout << "Copy constructor!\n";
}

student::~student() {
	homeworks_.clear();
}

student& student::operator=(const student& other)
{
	//std::cout << "Operator = was called!\n";
	if (this == &other) return *this;
	name_ = other.name_;
	surname_ = other.surname_;
	homeworks_ = other.homeworks_;
	exam_ = other.exam_;
	final_average_ = other.final_average_;
	final_median_ = other.final_median_;
	return *this;
}

double student::final_ave(std::vector<int> homeworks, int exam)
{
	return (std::accumulate(homeworks.begin(), homeworks.end(), 0.0) / homeworks.size()) * 0.4 + exam * 0.6;
}

double student::final_med(std::vector<int> homeworks, int exam)
{
	double median;
	int n = homeworks.size();
	std::sort(homeworks.begin(), homeworks.end());
	if (n % 2 != 0) {
		median = homeworks.at(n / 2);
	}
	else {
		median = (double)(homeworks.at(n / 2 - 1) + homeworks.at(n / 2)) / 2;
	}
	return median * 0.4 + exam * 0.6;
}

#endif