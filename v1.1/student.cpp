#include "student.h"

/*
		CONSTANTS
*/

const int max_result = 10;		//- Maximum result value
const int min_result = 1;		//- Minimum result value
const int max_nd = 15;			//- Maximum number of homeworks
const int min_nd = 5;			//- Minimum number of homeworks

/*
		RANDOM NUMBER GENERATOR
*/

std::random_device rd_generator;	//-Random number generator
//-Interval for random value of results
std::uniform_int_distribution<int> Results_interval(min_result, max_result);
//-Interval for random number of homeworks
std::uniform_int_distribution<int> Amount_interval(min_nd, max_nd);

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
		median = (double) (homeworks.at(n / 2 - 1) + homeworks.at(n / 2)) / 2;
	}
	return median * 0.4 + exam * 0.6;
}

student::student(std::string name, std::string surname, std::vector<int> homeworks, int exam)
{
	name_ = name;
	surname_ = surname;
	homeworks_ = homeworks;
	exam_ = exam;
	final_average_ = student::final_ave(homeworks, exam);
	final_median_ = student::final_med(homeworks, exam);
}

student::student(std::string name, std::string surname)
{
	exam_ = Results_interval(rd_generator);
	std::cout << "\nGenerated egzam result: " << exam_ << std::endl;
	int amount = Amount_interval(rd_generator);
	homeworks_.reserve(amount);
	std::cout << "Generated home work result: {";
	for (int i = 0; i < amount; i++) {
		homeworks_.push_back(Results_interval(rd_generator));
		std::cout << homeworks_.at(i) << ", ";
	}
	std::cout << "}" << std::endl;
	final_average_ = student::final_ave(homeworks_, exam_);
	final_median_ = student::final_med(homeworks_, exam_);
}

int nam_sur(const student& a, const student& b)
{
	return (a.name() == b.name()) ? a.surname() < b.surname() : a.name() < b.name();
}

int nam_ave(const student& a, const student& b)
{
	return (a.name() == b.name()) ? a.final_average() < b.final_average() : a.name() < b.name();
}

int nam_med(const student& a, const student& b)
{
	return (a.name() == b.name()) ? a.final_median() < b.final_median() : a.name() < b.name();
}

int sur_nam(const student& a, const student& b)
{
	return (a.surname() == b.surname()) ? a.name() < b.name() : a.surname() < b.surname();
}
int sur_ave(const student& a, const student& b)
{
	return (a.surname() == b.surname()) ? a.final_average() < b.final_average() : a.surname() < b.surname();
}

int sur_med(const student& a, const student& b)
{
	return (a.surname() == b.surname()) ? a.final_median() < b.final_median() : a.surname() < b.surname();
}

int ave_nam(const student& a, const student& b)
{
	return (a.final_average() == b.final_average()) ? a.name() < b.name() : a.final_average() < b.final_average();
}

int ave_sur(const student& a, const student& b)
{
	return (a.final_average() == b.final_average()) ? a.surname() < b.surname() : a.final_average() < b.final_average();
}

int ave_med(const student& a, const student& b)
{
	return (a.final_average() == b.final_average()) ? a.final_median() < b.final_median() : a.final_average() < b.final_average();
}

int med_nam(const student& a, const student& b)
{
	return (a.final_median() == b.final_median()) ? a.name() < b.name() : a.final_median() < b.final_median();
}

int med_sur(const student& a, const student& b)
{
	return (a.final_median() == b.final_median()) ? a.surname() < b.surname() : a.final_median() < b.final_median();
}

int med_ave(const student& a, const student& b)
{
	return (a.final_median() == b.final_median()) ? a.final_average() < b.final_average() : a.final_median() < b.final_median();
}

int nam(const student& a, const student& b)
{
	return a.name() < b.name();
}

int sur(const student& a, const student& b)
{
	return a.surname() < b.surname();
}

int ave(const student& a, const student& b)
{
	return a.final_average() < b.final_average();
}

int med(const student& a, const student& b)
{
	return a.final_median() < b.final_median();
}
