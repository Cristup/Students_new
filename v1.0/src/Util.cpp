#include "Util.h"

/*
		RANDOM NUMBER GENERATOR
*/

random_device rd;	//-Random number generator
std::mt19937 gen(rd());
//-Interval for random value of results
uniform_int_distribution<int> interval(1, 10);

Test_data test_results;

void update_info(stringstream& info, const enum container_types& type)
{
	info.str("");
	stringstream functions;
	//-Information of commands for a user
	functions << "\nInput functions:\n" <<
		"'Test'    - selecting files for testing;\n" <<
		"'Create   - creating test data files;\n" <<
		"'Open'    - reading Students data;\n" <<
		"'Show'    - show available '.txt' files;\n" <<
		"'Check'   - show currently used Conteiner\n" <<
		"'End'     - to stop application;\n" <<
		"`Info'    - to list commands;\n" <<
		"`Change`  - to change container type;\n" <<
		"`Strategy`- change data splitting strategy;\n" <<
		"`Results` - print results of all tests;\n" <<
		"*integer* - number of students for manual input of data.\n" <<
		"Program currently is using container type:";
	info << functions.str();
	(type == container_types::Vector) ? info << "VECTOR.\n\n" : info << "LIST.\n\n";
}

void progress_clock(const size_t& lines)
{
	const size_t parts = 50;
	int progress = 0;
	const int duration = lines / parts * 5;
	for (int i = 0; i < parts; i++) {
		cout << "Progress: " << "\033[" << 31 << "m" << progress  << "%"  << "\033[" << 97 << "m" << "\r";
		progress += 100 / parts;
		std::this_thread::sleep_for(std::chrono::microseconds(duration));
	}
	//NOTES
	// //cout << "\033[" << 31 << "m";
	//cout << "\033[" << 92 << "m"; //92 for bright green, 97 for bright white
	//cout << "\033[0m";
}

void update_files(vector<Directory_files>& files)
{
	files.clear();
	stringstream buf;
	Directory_files temp_info;
	int id = 0;
	string filename;
	ofstream file("lists / list_of_txt.txt");
	file.close();
	system("dir *txt /B > lists/list_of_txt.txt");
	ifstream inFile("lists/list_of_txt.txt");
	buf << inFile.rdbuf();
	inFile.close();
	while (buf >> filename) {
		id++;
		temp_info.id = id;
		temp_info.name = filename;
		(is_data_file(filename)) ? temp_info.type = Directory_files::Data : temp_info.type = Directory_files::Results;
		files.push_back(temp_info);
	}
}

void table(const vector<Directory_files> files)
{
	cout << "\nID |File_name           |Content\n" <<
		"---+--------------------+--------\n";
	for (const auto& file : files) {
		cout << setw(3) << left << file.id << "|" <<
			setw(20) << left << file.name << "|";
		(file.type == Directory_files::Data) ?
			cout << "Data\n" :
			cout << "Results\n";
	}
	cout << endl;
}

bool is_data_file(const string& filename)
{
	string head;
	ifstream file(filename);
	getline(file, head);
	return head.find("ND", 0) != string::npos;
}

void get_type(const enum container_types& type)
{
	(type == container_types::Vector) ?
		cout << "Program currently is using container type: VECTOR.\n" :
		cout << "Program currently is using container type: LIST.\n";
}

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

double Result(const int& egz, const double& value)
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
	buffer.str().reserve(size * 190);
	int index;
	buffer << setw(20) << left << "Vardas" <<
		setw(21) << left << "Pavarde";
	for (int i = 0; i < 15; i++) {
		buffer << "ND" << setw(8) << i + 1;
	}
	buffer << "Egz.\n";

	for (int i = 1; i <= size; i++) {
		index = i;
		buffer << "Vardas" << setw(14) << left << index <<
			"Pavarde" << setw(14) << left << index;
		for (int j = 0; j < 15; j++) {
			buffer << setw(10) << interval(gen);
		}
		buffer << interval(gen) << "\n";
	}
	ofstream file(filename);
	file << buffer.str();
	buffer.str("");
	buffer.clear();
	file.close();
}

void create_multiple_files(vector<File_info>& files)
{
	double time;
	for (auto& file : files) {
		std::thread clock(progress_clock, std::ref(file.size));
		Timer timer;
		generate_file(file.name, file.size);
		time = timer.elapsed();
		clock.join();
		cout << "Progress:" << "\033[" << 92 << "m" << " 100%" << "\033[" << 97 << "m" << endl;
		cout << "Creating file of size " << setw(8) << file.size << " took: " << time << endl;
		test_results.fg_durations[file.name] = time;
	}
	cout << "All files created.\n\n";
	files.clear();
}

void markdown_table()
{
	//File generation
	printf("FILE GENERATION\n| Size | Duration |\n|:-------|-------:|\n");
	for (const auto& record : test_results.fg_durations) {
		printf("| %s | `%f` |\n", record.first.substr(0, record.first.size() - 4), record.second);
	}
	cout << endl;

	//File reading
	printf("DATA READING\n| Size | Vector | List |\n|:-------|:------:|:-------:|\n");
	for (const auto& test : test_results.vec_test) {
		string filename = test.first;

		Record rec1 = test.second;
		Record rec2;

		if (test_results.list_test.find(filename) != test_results.list_test.end()) {
			rec2 = test_results.list_test[filename];
		}

		string size = filename.substr(0, filename.size() - 4);
		printf("| %s | `%f` | `%f` |\n", size, rec1.input / rec1.count, rec2.input / rec2.count);
	}
	cout << endl;

	//File sorting
	printf("DATA SORTING\n| Size | Vector | List |\n|:-------|:------:|:-------:|\n");
	for (const auto& test : test_results.vec_test) {
		string filename = test.first;

		Record rec1 = test.second;
		Record rec2;

		if (test_results.list_test.find(filename) != test_results.list_test.end()) {
			rec2 = test_results.list_test[filename];
		}

		string size = filename.substr(0, filename.size() - 4);
		printf("| %s | `%f` | `%f` |\n", size, rec1.sorting / rec1.count, rec2.sorting / rec2.count);
	}
	cout << endl;

	//File categorising
	printf("DATA CATEGORISING\n| Size | Vector | List |\n|:-------|:------:|:-------:|\n");
	for (const auto& test : test_results.vec_test) {
		string filename = test.first;

		Record rec1 = test.second;
		Record rec2;

		if (test_results.list_test.find(filename) != test_results.list_test.end()) {
			rec2 = test_results.list_test[filename];
		}

		string size = filename.substr(0, filename.size() - 4);
		printf("| %s | `%f` | `%f` |\n", size, rec1.categorising / rec1.count, rec2.categorising / rec2.count);
	}
	cout << endl;

	//File output
	printf("DATA OUTPUT\n| Size | Vector | List |\n|:-------|:------:|:-------:|\n");
	for (const auto& test : test_results.vec_test) {
		string filename = test.first;

		Record rec1 = test.second;
		Record rec2;

		if (test_results.list_test.find(filename) != test_results.list_test.end()) {
			rec2 = test_results.list_test[filename];
		}

		string size = filename.substr(0, filename.size() - 4);
		printf("| %s | `%f` | `%f` |\n", size, rec1.output / rec1.count, rec2.output / rec2.count);
	}
	cout << endl;

	//Total
	printf("TOTAL DURATION\n| Size | Vector | List |\n|:-------|:------:|:-------:|\n");
	for (const auto& test : test_results.vec_test) {
		string filename = test.first;

		Record rec1 = test.second;
		Record rec2;

		if (test_results.list_test.find(filename) != test_results.list_test.end()) {
			rec2 = test_results.list_test[filename];
		}

		string size = filename.substr(0, filename.size() - 4);
		printf("| %s | `%f` | `%f` |\n", size, rec1.total / rec1.count, rec2.total / rec2.count);
	}
	cout << endl;
}

void test_multiple_files(const vector<string>& files, const enum selection& print_by,
	const string& key, const enum container_types& c_type, const enum strategy& strat)
{
	for (auto& f : files) {

		vector<Stud> container_vector;
		vector<Stud> under_vector;
		vector<Stud> over_vector;
		list<Stud> container_list;
		list<Stud> under_list;
		list<Stud> over_list;

		cout << "Testing " << f;
		if (c_type == container_types::Vector) {
			cout << " using Vector ";
			test_results.vec_test[f].count++;
		}
		else {
			cout << " using List ";
			test_results.list_test[f].count++;
		}
		cout << "& split strategy nr: " << strat << "\n\n";
		//Reading
		Timer total;
		Timer t;
		double time = 0.0;
		(c_type == container_types::Vector) ?
			Input_from_file(container_vector, f) :
			Input_from_file(container_list, f);

		time = t.elapsed();
		(c_type == container_types::Vector) ?
			test_results.vec_test[f].input += time :
			test_results.list_test[f].input += time;
		cout << endl << "Reading " << f << " took:      " <<
			fixed << setprecision(4) << time << endl;

		//Sorting
		t.reset();
		(c_type == container_types::Vector) ?
			sort_students(container_vector, key) :
			sort_students(container_list, key);

		time = t.elapsed();
		(c_type == container_types::Vector) ?
			test_results.vec_test[f].sorting += time :
			test_results.list_test[f].sorting += time;
		cout << "Sorting " << f << " took:      " <<
			fixed << setprecision(4) << time << endl;

		//Spliting
		//##STRATEGY #1
		if (strat == strategy::s1) {
			t.reset();
			(c_type == container_types::Vector) ?
				sort_to_categories(container_vector, under_vector, over_vector) :
				sort_to_categories(container_list, under_list, over_list);
			time = t.elapsed();
		/*| Size | Vector	  |   List     |
		| 100000 | `0.017287` | `0.036902` |*/
		}
		//##STRATEGY #2
		else if (strat == strategy::s2) {
			if (c_type == container_types::Vector) {
				over_vector = container_vector;
				t.reset();
				sort_to_categories2(over_vector, under_vector);
			}
			else {
				over_list = container_list;
				t.reset();
				sort_to_categories2(over_list, under_list);
			}
			time = t.elapsed();
		/*| Size | Vector	   | List       |
		| 100000 | `29.783065` | `0.009906` |*/
		}
		//##STRATEGY #3
		else if (strat == strategy::s3) {
			if (c_type == container_types::Vector) {
				t.reset();
				sort_to_categories3(container_vector, over_vector, under_vector);
				time = t.elapsed();
			}
			else {
				t.reset();
				sort_to_categories3(over_list, under_list, container_list);
				time = t.elapsed();
				over_list = container_list;
			}
		/*| Size   | Vector	    | List       |
		| 100000 | `0.017976` | `0.009157` |*/
		}
		
		(c_type == container_types::Vector) ?
			test_results.vec_test[f].categorising += time :
			test_results.list_test[f].categorising += time;
		cout << "Categorising " << f << " took: " <<
			fixed << setprecision(4) << time << endl;

		//Output
		t.reset();
		if (c_type == container_types::Vector) {
			concurrency::parallel_invoke(
				[&]() { output_to_file(over_vector, f, print_by); },
				[&]() { output_to_file(under_vector, f, print_by); }
			);
		}
		else
		{
			concurrency::parallel_invoke(
				[&]() { output_to_file(over_list, f, print_by); },
				[&]() { output_to_file(under_list, f, print_by); }
			);
		}

		time = t.elapsed();
		(c_type == container_types::Vector) ?
			test_results.vec_test[f].output += time :
			test_results.list_test[f].output += time;
		cout << "Outputing " << f << " took:    " <<
			fixed << setprecision(4) << time << endl;

		time = total.elapsed();
		(c_type == container_types::Vector) ?
			test_results.vec_test[f].total += time :
			test_results.list_test[f].total += time;
		cout << endl << "Total duration:  " << fixed << setprecision(4) << time << endl;

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
	while (input >> key && n_keys < 2) {
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
		else if (line.empty())
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
	vector<Directory_files> directory;
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
				cout << setw(20) << left << "Name" << "|" << "Size\n--------------------+--------------------\n";
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
			update_files(directory);
			table(directory);
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
	vector<Directory_files> directory;
	int empty_count = 0,
		file_ID;
	string input;
	cout << "\nSelect files from this list by entering file ID:\n";
	update_files(directory);
	table(directory);
	cout << "Press ENTER twice to finish.\n";
	while (true) {
		cout << "\nInput ID << ";
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
			try {
				file_ID = stoi(input);
			}
			catch (exception& e) {
				cerr << "Invalid ID! Try again.\n";
				continue;
			}
			if (file_ID <= 0 || file_ID > directory.size()) {
				cout << "Id not found!\n";
				continue;
			}
			else if (directory.at(file_ID - 1).type == Directory_files::Results) {
				cout << "You must choose data file and not results!\n";
				continue;
			}
			else {
				//Opening file for testing
				ifstream file;
				try {
					file.open(directory.at(file_ID - 1).name);
					if (!file) {
						throw runtime_error("File not found!");
					}
					file.close();
					files.push_back(directory.at(file_ID - 1).name);
					cout << "Added " << files.back() << " to the list.\n";
					continue;
				}
				catch (const exception& e) {
					cerr << e.what() << endl;
					continue;
				}
			}
		}
	}
}

enum strategy cycle_strat(enum strategy& strat) {
	if (strat == strategy::s1) {
		cout << "Strategy is set to 2" << "\n\n";
		return strategy::s2;
	}
	else if (strat == strategy::s2) {
		cout << "Strategy is set to 3" << "\n\n";
		return strategy::s3;
	}
	else {
		cout << "Strategy is set to 1" << "\n\n";
		return strategy::s1;
	}
}