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
		local.emplace_back(student(name, surname, temp_homeworks, stoi(Temp_exam) ));
		temp_homeworks.clear();
	}
}

template<typename T>
void manual_input(T& container)
{
	string line;	//-User input
	string temp_name,
		temp_surname;
	vector<int> temp_hw;

	//Name & Surname input
	cout << "Name, Surname: ";
	cin >> temp_name >> temp_surname;

	while (true) {
		//Preparing input for further cases
		cout << "Enter egzam result or write 'auto' to generate egzam and home work results: ";
		cin >> line;
		transform(line.begin(), line.end(), line.begin(), ::tolower);

		//Generate data
		if (line.substr(0, 2) == "au") {
			container.emplace_back(student(temp_name, temp_surname));
			break;
		}

		//Manual input and user input handling
		else {
			int exam_result; //-temporary value for storing exam result.
			try {
				exam_result = stoi(line);
				if (exam_result < min_result || exam_result > max_result) {
					throw out_of_range("Value out of range!");
				}
				homework_input(temp_hw);
				container.emplace_back(student(temp_name, temp_surname, temp_hw, exam_result));
				temp_hw.clear();
				cout << "In-memory address of this student: " << &container.back() << "\n\n";
				break;
			}
			catch (const invalid_argument&) {
				cerr << "Invalid input! Try again." << endl;
			}
			catch (const out_of_range&) {
				cerr << "Number out of range! Try again." << endl;
			}
		}
	}
}

void homework_input(vector<int>& homework) {
	cerr << "Enter home work results (Press enter twice to finish)." << endl;
	int Temp_nd,		//-Temporary place for storing a value
		nd_count = 1,//-Total number and index of homeworks
		empty_count = 0;//-Number of times when user pressed Enter
	string value;		//-User input

	//Delete left over empty space after "cin >>"
	getline(cin, value);

	//Data input until break(Enter press twice)
	while (true) {
		//Input
		cout << "Enter home work number " << nd_count << " result: ";
		getline(cin, value);

		//Empty input cases
		if (value.empty()) {
			empty_count++;
			if (nd_count == 1) {
				cerr << "You must enter at least one home work!" << endl;
			}
			else if (empty_count == 2) {
				break;
			}
		}
		//Not positive integer input case
		else if (!is_digits(value)) {
			cerr << "Invalid input! Try again." << endl;
		}
		//In range input case
		else if (stoi(value) >= min_result && stoi(value) <= max_result) {
			empty_count = 0;
			Temp_nd = stoi(value);
			homework.push_back(Temp_nd);
			nd_count++;
		}
		//Left over case
		else {
			cerr << "Value must be in the interval [1;10]!" << endl;
		}
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
			buffer << s;
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

template<typename T>
void output_to_screen(T& local)
{
	cout << "\nName              Surname           Final result(Avg) Final result(Med)\n";
	cout << "-----------------------------------------------------------------------\n\n";
	for (auto& s : local) {cout << s;}
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
		cout << "Progress:" << "\033[" << 92 << "m" << "[==================================================]" << "\033[" << 97 << "m" << endl;
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

	//VECTOR
	printf("VECTOR\n| Size | Reading | Sorting | Categorising | Output | Total |\n|:-------|:------:|:-------:|:-------:|:-------:|:-------:|\n");
	for (const auto& test : test_results.vec_test) {
		string filename = test.first;
		Record rec = test.second;
		int n = rec.count;

		string size = filename.substr(0, filename.size() - 4);
		printf("| **%s** | %f | %f | %f | %f | %f |\n", size, rec.input/n, rec.sorting/n, rec.categorising/n, rec.output/n, rec.total/n);
	}

	//LIST
	printf("LIST\n| Size | Reading | Sorting | Categorising | Output | Total |\n|:-------|:------:|:-------:|:-------:|:-------:|:-------:|\n");
	for (const auto& test : test_results.list_test) {
		string filename = test.first;
		Record rec = test.second;
		int n = rec.count;

		string size = filename.substr(0, filename.size() - 4);
		printf("| **%s** | %f | %f | %f | %f | %f |\n", size, rec.input / n, rec.sorting / n, rec.categorising / n, rec.output / n, rec.total / n);
	}
}

template<typename T>
void sort_to_categories(T& local, T& Under, T& Over)
{
	size_t size = local.size();
	if constexpr (is_same<T, vector<student> >::value) {
		Under.reserve(size / 1.5);
		Over.reserve(size / 1.5);
	}

	for (auto& i : local) {
		if (i.final_average() < 5) {
			Under.push_back(i);
			//clean(i);
		}
		else {
			Over.push_back(i);
			//clean(i);
		}
	}
}

template<typename T>
void sort_to_categories2(T& firstc, T& newc)
{
	size_t size = firstc.size();
	if constexpr (is_same<T, vector<student>>::value) {
		newc.reserve(size / 1.5);
	}

	sort_students(firstc, "ave");

	for (auto it = firstc.rbegin(); it != firstc.rend();) {
		if (it->final_average() >= 5) {
			newc.emplace_back(*it);
			it = decltype(it)(firstc.erase(std::next(it).base()));
		}
		else {
			++it;
		}
	}
}

template<typename T>
void sort_to_categories3(T& local, T& over)
{
	//vector str1 duration: | `0.017287` |

	size_t size = local.size();
	if constexpr (is_same<T, vector<student>>::value) {
		over.reserve(size / 1.5);
	}

	auto pivot = std::partition(local.begin(), local.end(), [](student& a) { return a.final_average() < 5; });

	for (auto it = local.rbegin(); it != local.rend();) {
		if (it->final_average() >= 5) {
			over.emplace_back(*it);
			it = decltype(it)(local.erase(std::next(it).base()));
		}
		else {
			++it;
		}
	}
}

void test_multiple_files(const vector<string>& files, const enum selection& print_by,
	const string& key, const enum container_types& c_type, const enum strategy& strat)
{
	for (auto& f : files) {

		vector<student> container_vector;
		vector<student> under_vector;
		vector<student> over_vector;
		list<student> container_list;
		list<student> under_list;
		list<student> over_list;

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
			| 100000 | `0.010542` | `0.017855` |*/
		}
		//##STRATEGY #3
		else if (strat == strategy::s3) {
			if (c_type == container_types::Vector) {
				t.reset();
				sort_to_categories3(container_vector, under_vector);
				time = t.elapsed();
				over_vector = container_vector;
			}
			else {
				t.reset();
				sort_to_categories3(container_list, under_list);
				time = t.elapsed();
				over_list = container_list;
			}
			/*| Size   | Vector	    | List       |
			//| 100000 | `0.015857` | `0.036290` |*/
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