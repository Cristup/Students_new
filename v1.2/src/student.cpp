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
	name_ = name;
	surname_ = surname;
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

std::ostream& operator<<(std::ostream& os, const student& s)
{
	os << std::setw(18) << std::left << s.name_ <<
		std::setw(18) << std::left << s.surname_ <<
		std::setw(19) << std::fixed << std::setprecision(2) << s.final_average_ <<
		std::setw(18) << std::fixed << std::setprecision(2) << s.final_median_ << "\n";

	return os;
}

std::istream& operator>>(std::istream& is, student& s)
{
	//? Namu darbu skaiciaus radimas skaitant is failo
	//? Zinutes termnale
	//? Automatinis ivedimas

	//! Tipo tikrinimas: &is == &std::cin pries cout'us
	//! Isskirti namudarbu skaitymo logika skaitan is 
	// failo skaityti iki eilutes galo(std::istringstream line_stream.. ir while ciklas)
	//! Del automatinio nuskaitymo islieka pasirinkimas su cin tipu
	
	if (&is == &std::cin) {
		std::cout << "Name, Surname: ";
	}
	is >> s.name_ >> s.surname_;

	//From terminal
	if (&is == &std::cin) {
		std::cout << "Enter number of homeworks: ";
		int hw_count;
		is >> hw_count;
		s.homeworks_.resize(hw_count);
		for (int i = 0; i < hw_count; i++) {
			std::cout << "Enter homework number " << i + 1 << ": ";
			is >> s.homeworks_.at(i);
		}
		std::cout << "Enter exam result: ";
		is >> s.exam_;
	}
	//From file
	else {
		std::string line;
		std::vector<int> temp_vec;
		std::getline(is, line);
		std::stringstream ss(line);
		int grade;
		while (ss >> grade) {
			temp_vec.push_back(grade);
		}
		s.exam_ = temp_vec.back();
		temp_vec.pop_back();
		s.homeworks_ = temp_vec;
	}
	s.final_average_ = s.final_ave(s.homeworks_, s.exam_);
	s.final_median_ = s.final_med(s.homeworks_, s.exam_);
	return is;
}

template<typename T>
void sort_students(T& Students, const std::string& key) {
	std::map<std::string, int(*)(const student&, const student&)> comparators = {
		{"nam_sur", nam_sur}, {"nam_ave", nam_ave}, {"nam_med", nam_med},
		{"sur_nam", sur_nam}, {"sur_ave", sur_ave}, {"sur_med", sur_med},
		{"ave_sur", ave_sur}, {"ave_nam", ave_nam}, {"ave_med", ave_med},
		{"med_nam", med_nam}, {"med_sur", med_sur}, {"med_ave", med_ave},
		{"nam", nam}, {"sur", sur}, {"ave", ave}, {"med", med}
	};
	if constexpr (std::is_same<T, std::vector<student>>::value) {
		concurrency::parallel_sort(Students.begin(), Students.end(), comparators[key]);
	}
	else if constexpr (std::is_same<T, std::list<student>>::value) {
		Students.sort(comparators[key]);
	}
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
