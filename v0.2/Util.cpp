#include "Util.h"

/*
		RANDOM NUMBER GENERATOR
*/

random_device rd;	//-Random number generator
//-Interval for random value of results
uniform_int_distribution<int> interval(1, 10);

double average_int(const vector<int>& nd)
{
	return accumulate(nd.begin(), nd.end(), 0.0) / nd.size();
}

double median(vector<int> nd)
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

void generate_file(const string& filename, const int& size)
{
	stringstream buffer;
	int index;
	buffer << setw(20) << left << "Vardas" <<
		setw(21) << left << "Pavarde";
	for (int i = 0; i < 15; i++) {
		buffer << "ND" << setw(8) << i + 1;
	}
	buffer << "Egz.\n";

	for (int i = 1;  i <= size; i++) {
		index = i;
		buffer << "Vardas" << setw(14) << left << index <<
			"Pavarde" << setw(14) << left << index;
		for (int j = 0; j < 15; j++) {
			buffer << setw(10) << interval(rd);
		}
		buffer << interval(rd) << "\n";
	}
	ofstream file(filename);
	file << buffer.str();
	buffer.str("");
	buffer.clear();
	file.close();
}

void create_multiple_files(const vector<File_info>& files)
{
	for (auto& file : files) {
		Timer timer;
		generate_file(file.name, file.size);
		cout << "Creating file of size " << setw(8) << file.size << " took: " << timer.elapsed() << endl;
	}
	cout << "All files created.\n\n";
}

void test_multiple_files(const vector<string>& files, const enum selection& print_by, const string& key)
{
	for (auto& f : files) {

		vector<Stud> container;
		vector<Stud> under;
		vector<Stud> over;

		cout << "Testing " << f << ".\n" << endl;

		//Reading
		Timer total;
		Timer t;
		Input_from_file(container, f);
		cout << endl << "Reading " << f << " took:      " <<
			fixed << setprecision(4) << t.elapsed() << endl;
		//Sorting
		t.reset();
		sort_students(container, key);
		cout << "Sorting " << f << " took:      " <<
			fixed << setprecision(4) << t.elapsed() << endl;
		//Spliting
		t.reset();
		sort_to_categories(container, under, over);
		cout << "Categorising " << f << " took: " <<
			fixed << setprecision(4) << t.elapsed() << endl;
		//Output
		t.reset();
		output_to_file(over, "Stiprus.txt", print_by);
		output_to_file(under, "Silpni.txt", print_by);
		cout << "Outputing " << f << " took:    " <<
			fixed << setprecision(4) << t.elapsed() << endl;

		cout << endl << "Total duration:  " << fixed << setprecision(4) << total.elapsed() << endl;

		system("pause");
		cout << endl;
	}
}

void find_keys(string& line, const enum selection& print_by, size_t& n_keys, vector<string>& keys)
{
	stringstream input(line),
				output;
	string key;
	bool name_used = false,
		surname_used = false,
		median_used = false,
		average_used = false;
	while(input >> key && n_keys < 2) {
		transform(key.begin(), key.end(), key.begin(), ::tolower);
		if (!name_used && key.substr(0, 3) == "nam") {
			output << "nam_";
			keys.push_back("Name");
			name_used = true;
			n_keys++;
		}
		else if (!surname_used && key.substr(0, 3) == "sur") {
			output << "sur_";
			keys.push_back("Surname");
			surname_used = true;
			n_keys++;
		}
		else if (!median_used && key.substr(0, 3) == "med" && (print_by == selection::Both || print_by == selection::Median)) {
			output << "med_";
			keys.push_back("Median");
			median_used = true;
			n_keys++;
		}
		else if (!average_used && key.substr(0, 3) == "ave" && (print_by == selection::Both || print_by == selection::Average)) {
			output << "ave_";
			keys.push_back("Average");
			average_used = true;
			n_keys++;
		}
		else continue;
	}
	line = output.str();
	line = line.substr(0, line.size() - 1);
}

enum selection print_selection()
{
	string input;
	cout << "\nInput:\n" <<
		"Average - to print result by average value;\n" <<
		"Median  - to print result by median value;\n" <<
		"Both    - to print result by both values.\n";
	while (true) {
		cout << "\nInput selection << ";
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input.substr(0, 2) == "av") {
			cout << "Results will be printed using Average value.\n";
			return selection::Average;
		}
		else if (input.substr(0, 2) == "me") {
			cout << "Results will be printed using Median value.\n";
			return selection::Median;
		}
		else if (input.substr(0, 2) == "bo") {
			cout << "Results will be printed using Both values.\n";
			return selection::Both;
		}
		else {
			cout << "Try again!\n";
			continue;
		}
	}
}

string sort_selection(const enum selection& print_by)
{
	string line,
		key_output;
	size_t n_keys;
	vector<string> keys;
	bool input_happend = false;
	keys.reserve(2);
	cout << "\nInput a maximum of 2 keys from this list:\n";
	if (print_by == selection::Both)
		cout << "{Name, Surname, Average, Median}\n";
	else (print_by == selection::Average) ? cout << "{Name, Surname, Average}\n" : cout << "{Name, Surname, Median}\n";
	cin.ignore();
	while (true) {
		cout << "\nInput keys << ";
		getline(cin, line);
		if (line.empty() && input_happend)
			return key_output;
		else if(line.empty())
		{
			cout << "Enter at least one key.\n";
			continue;
		}
		n_keys = 0;
		keys.clear();
		find_keys(line, print_by, n_keys, keys);
		key_output = line;
		if (keys.size() > 0 && keys.size() <= 2) {
			input_happend = true;
		}
		else {
			cout << "No keys found! Try again.\n";
			continue;
		}
		cout << "Selected key: ";
		for (auto& k : keys) cout << k << " ";
		cout << "\nPress Enter to procceed or input keys again: ";
	}
}

void create_file_selection(vector<File_info>& files)
{
	string line;
	int empty_count = 0,
		temp_size;
	File_info temp;
	cout << "\nEnter files to create data(Name & Size).\n" <<
		"When finised press ENTER twice.\n" <<
		"To get a list of existing files write 'Info'\n";
	cin.ignore();
	while (true) {
		cout << "\nInput name << ";
		getline(cin, line);
		if (line.empty()) {
			empty_count++;
			if (files.size() > 0 && empty_count >= 2) {
				cout << "Files:\n";
				cout << setw(20) <<left << "Name" << "|" << "Size\n--------------------+--------------------\n";
				for (auto& f : files) {
					cout << setw(20) << left << f.name << "|" << f.size << endl;
				}
				cout << endl;
				break;
			}
			else if (files.size() == 0) {
				cout << "Provide atleat one file name!\n";
				continue;
			}
		}
		else if (line == "Info" || line == "info") {
			empty_count = 0;
			cout << "\nAvailable '.txt' files:\n";
			system("dir *.txt /B");
		}
		else {
			empty_count = 0;
			if (line.length() >= 4 && line.substr(line.length() - 4, 4) != ".txt") line += ".txt";
			temp.name = line;
			cout << "Enter size for file " << line << endl;
			while (true) {
				cout << "\nInput size << ";
				try {
					cin >> line;
					temp_size = stoi(line);
				}
				catch (const exception&) {
					cout << "Invalid input, try agian.\n";
					continue;
				}
				if (temp_size > 0 && temp_size <= 10000000) {
					temp.size = temp_size;
					break;
				}
				else {
					cout << "Number out of range!\n";
					continue;
				}
			}
			files.push_back(temp);
			cin.ignore();
		}
	}

}

void file_selection(vector<string>& files)
{
	int empty_count = 0;
	string input;
	cout << "\nSelect files from this list:\n";
	system("dir *.txt /B");
	cout << "Press ENTER twice to finish.\n";
	while (true) {
		cout << "\nInput filename << ";
		getline(cin, input);
		if (input.empty()) {
			empty_count++;
			if (files.size() >= 0 && empty_count >= 2) {
				break;
			}
			else if (files.size() == 0) {
				cout << "Input at least one file!\n";
			}
		}
		else {
			empty_count = 0;
			if (input.length() > 4 && input.substr(input.length() - 4, 4) != ".txt") input += ".txt";
			//Opening file for testing
			ifstream file;
			try {
				file.open(input);
				if (!file) {
					throw runtime_error("File not found!");
				}
				files.push_back(input);
				continue;
			}
			catch (const exception& e) {
				cerr << e.what() << endl;
			}
		}
	}
}