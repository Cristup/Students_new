#include "Util.h"

/*
		RANDOM NUMBER GENERATOR
*/

random_device rd;	//-Random number generator
//-Interval for random value of results
uniform_int_distribution<int> interval(1, 10);
mutex file_mutex;
const int num_threads = 4;
const int part_size = 10000;

double Average(const vector<int>& nd)
{
	return accumulate(nd.begin(), nd.end(), 0.0) / nd.size();
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

double Result(const int& egz,const double& value)
{
	return 0.4 * value + 0.6 * egz;
}

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

//void create_test_file(string filename, int size) {
//	ostringstream line;		//-Line to be writen into the file
//	string index;
//
//	//Creating headline
//	line << setw(20) << left << "Vardas" <<
//		setw(21) << left << "Pavarde";
//	for (int i = 0; i < 15; i++) {
//		line << "ND" << setw(8) << i + 1;
//	}
//	line << "Egz.\n";
//
//	//Opening file
//	ofstream file;
//	file.open(filename);
//
//	//Creting and writing data
//	for (int i = 0; i < size; i++) {
//
//		if (i % part_size == 0 && i > 0) {
//			file << line.rdbuf();
//			line.str("");
//			line.clear();
//		}
//
//		index = i + 1;
//		line << "Vardas" << setw(14) << index <<
//			"Pavarde"<< setw(14) << index;
//		for (int j = 0; j < 15; j++) {
//			line << setw(10) << interval(rd);
//		}
//		line << interval(rd) << "\n";
//	}
//
//	file << line.rdbuf();
//
//	//Closing file
//	file.close();
//}

void create_data_chuncked(const string& filename, const int& start, const int& stop) {
	ostringstream buffer;
	int index;
	
	for (int i = start - 1; i < stop; i++) {
		index = i + 1;
		buffer << "Vardas" << setw(14) << left << index <<
			"Pavarde" << setw(14) << left << index;
		for (int j = 0; j < 15; j++) {
			buffer << setw(10) << interval(rd);
		}
		buffer << interval(rd) << "\n";

		if (i % part_size == 0 && i > 0) {
			lock_guard<mutex> lock(file_mutex);
			ofstream file(filename, ios::app | ios::binary);
			if (file.is_open()) {
				file << buffer.str();
				file.close();
			}
			
			buffer.str("");
			buffer.clear();
		}
	}

	lock_guard<mutex> lock(file_mutex);
	ofstream file(filename, ios::app | ios::binary);
	if (file.is_open()) {
		file << buffer.str();
		file.close();
	}
}

void create_data(const string& filename, const int& size) {
	vector<thread> threads;
	ostringstream line;
	ofstream file;

	line << setw(20) << left << "Vardas" <<
		setw(21) << left << "Pavarde";
	for (int i = 0; i < 15; i++) {
		line << "ND" << setw(8) << i + 1;
	}
	line << "Egz.\n";

	file.open(filename);
	file << line.str();
	file.close();

	int range_size = size / num_threads;

	for (int i = 0; i < num_threads; i++) {
		int start = i * range_size + 1;
		int stop = (i + 1) * range_size;

		threads.push_back(thread(create_data_chuncked, filename, start, stop));
	}

	for (auto& th : threads) {
		th.join();
	}
	
}