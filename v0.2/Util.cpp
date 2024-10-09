#include "Util.h"

/*
		RANDOM NUMBER GENERATOR
*/

random_device rd;	//-Random number generator
//-Interval for random value of results
uniform_int_distribution<int> interval(1, 10);
mutex file_mutex;
const int part_size = 10000;
const int num_threads = thread::hardware_concurrency();

double Average(const vector<int>& nd)
{
	return accumulate(nd.begin(), nd.end(), 0.0) / nd.size();
}

double Mean(const vector<double>& vec)
{
	return accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
}

double Median(vector<int> nd)
{
	int n = nd.size();
	sort(nd.begin(), nd.end());
	if (n % 2 != 0) {
		return nd.at(n / 2);
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
			ofstream file(filename, ios::app);
			if (file.is_open()) {
				file << buffer.str();
				file.close();
			}
			
			buffer.str("");
			buffer.clear();
		}
	}

	lock_guard<mutex> lock(file_mutex);
	ofstream file(filename, ios::app);
	if (file.is_open()) {
		file << buffer.str();
		file.close();
	}
}

void create_data(const string& filename, const int& size) {
	vector<thread> threads;
	threads.reserve(num_threads);
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

void test_multiple_files()
{

	for (int i = 0; i < 5; i++) {
		size_t size = 1000 * std::pow(10, i);
		stringstream filename;
		filename << size << ".txt";
		string fname = filename.str();

		vector<Stud> container;
		vector<Stud> under;
		vector<Stud> over;

		double reading = 0;
		double spliting = 0;
		double sorting = 0;
		double output = 0;
		double total = 0;
		double create_total = 0;

		cout << "Testing a file of size: " << size << ".\n" << endl;

		for (int j = 0; j < 5; j++) {
			ofstream file(fname, std::ios::trunc);
			file.close();

			//Creating
			auto start_create = high_resolution_clock::now();
			create_data(fname, size);
			auto end_create = high_resolution_clock::now();
			duration<double> duration = end_create - start_create;
			cout << "Creating of the file of size " << size << " took: " << duration.count() << endl;
			create_total += duration.count();

			//Reading
			auto start_read = high_resolution_clock::now();
			Input_from_file(container, fname);
			auto end_read = high_resolution_clock::now();
			duration = end_read - start_read;
			reading += duration.count();

			//Sorting
			auto start_sort = high_resolution_clock::now();
			//sorting_in_threads(under, over);
			sort(container.begin(), container.end(), nam );
			auto end_sort = high_resolution_clock::now();
			duration = end_sort - start_sort;
			sorting += duration.count();

			//Spliting
			auto start_split = high_resolution_clock::now();
			sort_to_categories(container, under, over);
			auto end_split = high_resolution_clock::now();
			duration = end_split - start_split;
			spliting += duration.count();

			//Output
			auto start_out = high_resolution_clock::now();
			output_with_multithreading(under, over);
			auto end_out = high_resolution_clock::now();
			duration = end_out - start_out;
			output += duration.count();

			duration = end_out - start_read;
			total += duration.count();
		}

		cout << "On average creating the files of size " << size << " took: " <<
			fixed << setprecision(4) << create_total / 5 << endl;

		cout << endl << "Reading the file of size " << size << " took:      " <<
			fixed << setprecision(4) << reading / 5 << endl;

		cout << "Sorting the file of size " << size << " took:      " <<
			fixed << setprecision(4) << sorting / 5 << endl;

		cout << "Categorising the file of size " << size << " took: " <<
			fixed << setprecision(4) << spliting / 5 << endl;

		cout << "Outputing the file of size " << size << " took:    " <<
			fixed << setprecision(4) << output / 5 << endl;

		cout << endl << "Total duration:  " << fixed << setprecision(4) << total / 5 << endl;

		system("pause");
		cout << endl;
	}
}

void find_keys(string& line, vector<string>& keys)
{
	stringstream input(line);
	string key;
	keys.resize(2);
	for (int i = 0; i < 2; i++) {
		input >> key;			
		transform(key.begin(), key.end(), key.begin(), ::tolower);
			keys.at(i) = key;
	}
}