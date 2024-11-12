#include "util.h"

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
	const size_t parts = 50;
	int progress = 0;
	const int duration = lines / parts * 5;
	for (int i = 0; i < parts; i++) {
		cout << "Progress: " << "\033[" << 31 << "m" << progress << "%" << "\033[" << 97 << "m" << "\r";
		progress += 100 / parts;
		std::this_thread::sleep_for(std::chrono::microseconds(duration));
	}
	//NOTES
	// //cout << "\033[" << 31 << "m";
	//cout << "\033[" << 92 << "m"; //92 for bright green, 97 for bright white
	//cout << "\033[0m";
}