#include "util.h"

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
		"`Enviroment` - run a test enviroment;\n" <<
		"*integer* - number of students for manual input of data.\n" <<
		"Program currently is using container type:";
	info << functions.str();
	(type == container_types::Vector) ? info << "VECTOR.\n\n" : info << "LIST.\n\n";
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

void progress_clock(const size_t& lines)
{
	//OLD VERSION
	/*const size_t parts = 50;
	int progress = 0;
	const int duration = lines / parts * 5;
	for (int i = 0; i < parts; i++) {
		cout << "Progress: " << "\033[" << 31 << "m" << progress << "%" << "\033[" << 97 << "m" << "\r";
		progress += 100 / parts;
		std::this_thread::sleep_for(std::chrono::microseconds(duration));
	}*/

	//NOTES
	// //cout << "\033[" << 31 << "m";
	//cout << "\033[" << 92 << "m"; //92 for bright green, 97 for bright white
	//cout << "\033[0m";

	//NEW VERSION
	const size_t parts = 50;
	const int duration = lines / parts * 5;
	stringstream bar("");

	for (int i = 0; i < parts; i++) {
		cout << "Progress: " << "\033[" << 31 << "m" <<
			 "[" << bar.str() << "]"
			 << "\033[" << 97 << "m" << "\r";
		for (int j = 0; j < 50 / 50; j++) {
			bar.clear();
			bar << "=";
		}

		std::this_thread::sleep_for(std::chrono::microseconds(duration));
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