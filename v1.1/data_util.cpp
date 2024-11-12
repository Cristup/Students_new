#include "data_util.h"

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

random_device rd;	//-Random number generator

std::mt19937 gen(rd());
//-Interval for random value of results
uniform_int_distribution<int> interval(1, 10);

Test_data test_results;

template<typename Container>
void Input_from_file(Container& local, const string& filename)
{
	int n = 0,				//Number of homeworks.
		Line_number = 0;	//For counting lines in the file.
	string	Temp_nd,		//Temporary value for storing homework mark.
		Temp_exam,			//Temporary value for storing exam result.
		Temp_value,			//Temporary value for working with headline.
		name,				//Temporary value for student name.
		headline,			//
		surname;			//Temporary value for student surname.
	stringstream buffer;	//Buffer holding file content
	vector<int> temp_homeworks;

	if constexpr (is_same<Container, vector<student>>::value) {
		//Check file size
		ifstream File;
		File.open(filename, std::ios::ate);
		std::streamsize fileSize = File.tellg();
		File.seekg(ios::beg);
		string firstline;
		getline(File, firstline);
		File.close();
		int lineSize = firstline.size();
		//cout << "File size: " << fileSize << " Bytes\n";
		//cout << "Line size: " << lineSize << " Bytes\n";

		//Guess number of lines
		int numberOfLines = fileSize / lineSize;
		int adjust_size = (int)log10(numberOfLines) - 1;
		numberOfLines += pow(10, adjust_size);
		//cout << "Aprox. number of lines: " << numberOfLines << endl;
		local.reserve(numberOfLines);
	}

	//Opening file
	ifstream inFile; //-Data file
	inFile.open(filename);
	//Reading whole file to buffer
	buffer << inFile.rdbuf();
	inFile.close();

	//Cheking number of homeworks
	getline(buffer, headline);
	n = count(headline.begin(), headline.end(), 'N');

	//Reading data
	while (buffer >> name >> surname) {
		Line_number++;

		//Homework marks
		temp_homeworks.reserve(n);
		try {
			for (int i = 0; i < n; i++) {
				buffer >> Temp_nd;
				temp_homeworks.push_back(stoi(Temp_nd));
			}
		}
		catch (const exception&) {
			cerr << "Invalid argument on line " << Line_number << "!" << endl;
			cout << "Data was skipped!" << endl;
			system("pause");
			//Ignore all characters ubtil '\n'
			buffer.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		//Egzam result
		try {
			buffer >> Temp_exam;
			stoi(Temp_exam);
		}
		catch (const exception&) {
			cerr << "Invalid argument on line " << Line_number << "!" << endl;
			cout << "Data was skipped!" << endl;
			system("pause");
			//Ignore all characters until '\n'
			buffer.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		//Saving to local vector
		local.push_back(student(name, surname, temp_homeworks, stoi(Temp_exam) ));
	}
}

template<typename T>
void output_to_file(T& local, const string& filename, const enum selection& print_by)
{
	stringstream name_front(filename.substr(0, filename.size() - 4));
	string name_end;
	if constexpr (is_same<T, vector<student>>::value)
		(local.at(0).final_average() >= 5) ? name_end = "_stiprus.txt" : name_end = "_silpni.txt";
	else
		(local.front().final_average() >= 5) ? name_end = "_stiprus.txt" : name_end = "_silpni.txt";
	string fname = name_front.str() + name_end;
	//Opening file
	ofstream outFile;	//-Results file
	outFile.open(fname);	//File name
	stringstream buffer;
	switch (print_by)
	{
	case Average:
		//Writing Headline
		outFile << "Name              Surname           Final result(Avg)\n";
		outFile << "-----------------------------------------------------\n";
		//Writing data
		for (auto& s : local) {
			buffer << setw(18) << left << s.name() <<
				setw(18) << left << s.surname() <<
				setw(18) << fixed << setprecision(2) << s.final_average() << "\n";
		}
		break;
	case Median:
		//Writing Headline
		outFile << "Name              Surname           Final result(Med)\n";
		outFile << "-----------------------------------------------------\n";
		//Writing data
		for (auto& s : local) {
			buffer << setw(18) << left << s.name() <<
				setw(18) << left << s.surname() <<
				setw(18) << fixed << setprecision(2) << s.final_median() << "\n";
		}
		break;
	case Both:
		//Writing Headline
		outFile << "Name              Surname           Final result(Avg) Final result(Med)\n";
		outFile << "-----------------------------------------------------------------------\n";
		//Writing data
		for (auto& s : local) {
			buffer << setw(18) << left << s.name() <<
				setw(18) << left << s.surname() <<
				setw(19) << fixed << setprecision(2) << s.final_average() <<
				setw(18) << fixed << setprecision(2) << s.final_median() << "\n";
		}
		break;
	default:
		break;
	}
	outFile << buffer.str();
	//Closing file
	outFile.close();
	local.clear();
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