#include "Stud.h"

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

random_device rd_generator;	//-Random number generator
//-Interval for random value of results
uniform_int_distribution<int> Results_interval(min_result, max_result);
//-Interval for random number of homeworks
uniform_int_distribution<int> Amount_interval(min_nd, max_nd);

/*
		DATA INPUT FUNCTIONS
*/

void Automatic_input(Stud& local)
{
	//Generate exam result and print them to terminal
	local.egz = Results_interval(rd_generator);
	cout << "\nGenerated egzam result: " << local.egz << endl;

	//Generate number of homeworks
	int amount = Amount_interval(rd_generator);

	//Generate and print homework marks
	local.nd.reserve(amount);
	cout << "Generated home work result: {";
	for (int i = 0; i < amount; i++) {
		local.nd.push_back(Results_interval(rd_generator));
		cout << local.nd[i] << ", ";
	}
	cout << "}" << endl;
}

void Manual_input(Stud& local)
{
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
			local.nd.push_back(Temp_nd);
			nd_count++;
		}
		//Left over case
		else {
			cerr << "Value must be in the interval [1;10]!" << endl;
		}
	}
}


void input(Stud& local)
{
	string line;	//-User input

	//Name & Surname input
	cout << "Name, Surname: ";
	cin >> local.vardas >> local.pavarde;

	while (true) {
		//Preparing input for further cases
		cout << "Enter egzam result or write 'auto' to generate egzam and home work results: ";
		cin >> line;
		transform(line.begin(), line.end(), line.begin(), ::tolower);

		//Generate data
		if (line.substr(0, 2) == "au") {
			Automatic_input(local);
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
				local.egz = exam_result;
				cerr << "Enter home work results (Press enter twice to finish)." << endl;
				Manual_input(local);
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
	//Other values
	local.final_vid = Result(local.egz, average_int(local.nd));
	local.final_med = Result(local.egz, median(local.nd));
	local.cat = (local.final_vid < 5) ? Stud::Under : Stud::Over;
}

template<typename Container>
void Input_from_file(Container& local, const string& filename)
{
	Stud Temp_stud;			//Temporary value for storing single students data.
	int n = 0,				//Number of homeworks.
		Line_number = 0;	//For counting lines in the file.
	string	Temp_nd,		//Temporary value for storing homework mark.
		Temp_egzam,			//Temporary value for storing exam result.
		Temp_value,			//Temporary value for working with headline.
		name,				//Temporary value for student name.
		headline,			//
		surname;			//Temporary value for student surname.
	stringstream buffer;	//Buffer holding file content

	if constexpr (is_same<Container, vector<Stud>>::value) {
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
		//Name & Surname
		Temp_stud.vardas = name;
		Temp_stud.pavarde = surname;

		//Homework marks
		Temp_stud.nd.reserve(n);
		try {
			for (int i = 0; i < n; i++) {
				buffer >> Temp_nd;
				Temp_stud.nd.push_back(stoi(Temp_nd));
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
			buffer >> Temp_egzam;
			Temp_stud.egz = stoi(Temp_egzam);
		}
		catch (const exception&) {
			cerr << "Invalid argument on line " << Line_number << "!" << endl;
			cout << "Data was skipped!" << endl;
			system("pause");
			//Ignore all characters until '\n'
			buffer.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		//Average, Median values and category
		Temp_stud.final_vid = Result(Temp_stud.egz, average_int(Temp_stud.nd));
		Temp_stud.final_med = Result(Temp_stud.egz, median(Temp_stud.nd));
		Temp_stud.cat = (Temp_stud.final_vid < 5) ? Stud::Under : Stud::Over;

		//Saving to local vector
		local.push_back(Temp_stud);
		//Cleaning temporary value for next input
		clean(Temp_stud);
	}
}

/*
		DATA OUTPUT FUNCTIONS
*/

template<typename T>
void output_to_file(T& local, const string& filename, const enum selection& print_by)
{
	stringstream name_front(filename.substr(0, filename.size() - 4));
	string name_end;
	if constexpr (is_same<T, vector<Stud>>::value)
		(local[0].final_vid >= 5) ? name_end = "_stiprus.txt" : name_end = "_silpni.txt";
	else
		(local.front().final_vid >= 5) ? name_end = "_stiprus.txt" : name_end = "_silpni.txt";
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
			buffer << setw(18) << left << s.vardas <<
				setw(18) << left << s.pavarde <<
				setw(18) << fixed << setprecision(2) << s.final_vid << "\n";
		}
		break;
	case Median:
		//Writing Headline
		outFile << "Name              Surname           Final result(Med)\n";
		outFile << "-----------------------------------------------------\n";
		//Writing data
		for (auto& s : local) {
			buffer << setw(18) << left << s.vardas <<
				setw(18) << left << s.pavarde <<
				setw(18) << fixed << setprecision(2) << s.final_med << "\n";
		}
		break;
	case Both:
		//Writing Headline
		outFile << "Name              Surname           Final result(Avg) Final result(Med)\n";
		outFile << "-----------------------------------------------------------------------\n";
		//Writing data
		for (auto& s : local) {
			buffer << setw(18) << left << s.vardas <<
				setw(18) << left << s.pavarde <<
				setw(19) << fixed << setprecision(2) << s.final_vid <<
				setw(18) << fixed << setprecision(2) << s.final_med << "\n";
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

/*
		OTHER FUNCTIONS
*/

template<typename T>
void sort_students(T& Students, const string& key) {
	map<string, int(*)(const Stud&, const Stud&)> comparators = {
		{"nam_sur", nam_sur}, {"nam_ave", nam_ave}, {"nam_med", nam_med},
		{"sur_nam", sur_nam}, {"sur_ave", sur_ave}, {"sur_med", sur_med},
		{"ave_sur", ave_sur}, {"ave_nam", ave_nam}, {"ave_med", ave_med},
		{"med_nam", med_nam}, {"med_sur", med_sur}, {"med_ave", med_ave},
		{"nam", nam}, {"sur", sur}, {"ave", ave}, {"med", med}
	};
	if constexpr (is_same<T, vector<Stud>>::value) {
		concurrency::parallel_sort(Students.begin(), Students.end(), comparators[key]);
	}
	else if constexpr (is_same<T, list<Stud>>::value) {
		Students.sort(comparators[key]);
	}
}

void clean(Stud& local)
{
	local.vardas.clear();
	local.pavarde.clear();
	local.nd.clear();
	local.egz = 0;
	local.final_med = 0;
	local.final_vid = 0;
}

template<typename T>
void sort_to_categories(T& local, T& Under, T& Over)
{
	size_t size = local.size();
	if constexpr (is_same<T, vector<Stud>>::value) {
		Under.reserve(size / 1.5);
		Over.reserve(size / 1.5);
	}

	for (auto& i : local) {
		if (i.cat == Stud::Under) {
			Under.push_back(i);
			clean(i);
		}
		else {
			Over.push_back(i);
			clean(i);
		}
	}
}

template<typename T>
void sort_to_categories2(T& firstc, T& newc)
{
	size_t size = firstc.size();
	if constexpr (is_same<T, vector<Stud>>::value) {
		newc.reserve(size / 1.5);
	}

	for (auto it = firstc.begin(); it != firstc.end();) {
		if (it->cat == Stud::Under) {
			newc.emplace_back(*it);
			it = firstc.erase(it);
		}
		else {
			++it;
		}
	}
}

template<typename T>
void sort_to_categories3(T& local, T& Under, T& Over)
{
	//vector str1 duration: | `0.017287` |
	if constexpr (is_same<T, vector<Stud>>::value) {
		size_t size = local.size();
		Under.reserve(size / 1.5);
		Over.reserve(size / 1.5);

		//VECTOR #1
		/*for (auto& el : local) {
			(el.cat == Stud::Under) ?
				Under.emplace_back(el):
				Over.emplace_back(el);
		}*/
		//| `0.016177` |
		
		//VECTOR #2
		/*std::copy_if(local.begin(), local.end(), Under.begin(), [&](const Stud& a) {return a.cat == Stud::Under; });
		std::copy_if(local.begin(), local.end(), Over.begin(), [&](const Stud& a) {return a.cat == Stud::Over; });*/
		//| `0.027750` |
		
		//VECTOR #3
		/*auto it = std::stable_partition(local.begin(), local.end(), [&](const auto& a) {return a.cat == Stud::Under; });
		std::copy(local.begin(), it, Under.begin());
		std::copy(it, local.end(), Over.begin());*/
		//| `0.032659` |

		//VECTOR #4
		auto it = std::partition(local.begin(), local.end(), [&](const auto& a) {return a.cat == Stud::Under; });
		Under.assign(local.begin(), it);
		Over.assign(it, local.end());
		//| `0.024361` | 

		//VECTOR #5
		/*auto it = std::stable_partition(local.begin(), local.end(), [&](const auto& a) {return a.cat == Stud::Under; });
		Under.insert(Under.begin(), local.begin(), it);
		Over.insert(Over.begin(), it, local.end());*/
		//| `0.024805` |

		local.clear();
	}
	else {
		//LIST
		for (auto it = Over.begin(); it != Over.end();) {
			if (it->cat == Stud::Under) {
				Under.emplace_back(*it);
				it = Over.erase(it);
			}
			else {
				++it;
			}
		}
	}
}

template<typename T>
int find_in_container(const T& container, const Stud& element)
{
	int pos = 0;
	for (const auto& i : container) {
		if (i.vardas == element.vardas && i.pavarde == element.pavarde) {
			return pos;
		}
		pos++;
	}
	return -1;
}

/*
	COMPARATORS
*/

int nam_sur(const Stud& a, const Stud& b)
{
	return (a.vardas == b.vardas) ? a.pavarde < b.pavarde : a.vardas < b.vardas;
}

int nam_ave(const Stud& a, const Stud& b)
{
	return (a.vardas == b.vardas) ? a.final_vid < b.final_vid : a.vardas < b.vardas;
}

int nam_med(const Stud& a, const Stud& b)
{
	return (a.pavarde == b.pavarde) ? a.final_med < b.final_med : a.pavarde < b.pavarde;
}

int sur_nam(const Stud& a, const Stud& b)
{
	return (a.pavarde == b.pavarde) ? a.vardas < b.vardas : a.pavarde < b.pavarde;
}

int sur_ave(const Stud& a, const Stud& b)
{
	return (a.pavarde == b.pavarde) ? a.final_vid < b.final_vid : a.pavarde < b.pavarde;
}

int sur_med(const Stud& a, const Stud& b)
{
	return (a.pavarde == b.pavarde) ? a.final_med < b.final_med : a.pavarde < b.pavarde;
}

int ave_sur(const Stud& a, const Stud& b)
{
	return (a.final_vid == b.final_vid) ? a.pavarde < b.pavarde : a.final_vid < b.final_vid;
}

int ave_nam(const Stud& a, const Stud& b)
{
	return (a.final_vid == b.final_vid) ? a.vardas < b.vardas : a.final_vid < b.final_vid;
}

int ave_med(const Stud& a, const Stud& b)
{
	return (a.final_vid == b.final_vid) ? a.final_med < b.final_med : a.final_vid < b.final_vid;
}

int med_nam(const Stud& a, const Stud& b)
{
	return (a.final_med == b.final_med) ? a.vardas < b.vardas : a.final_med < b.final_med;
}

int med_sur(const Stud& a, const Stud& b)
{
	return (a.final_med == b.final_med) ? a.pavarde < b.pavarde : a.final_med < b.final_med;
}

int med_ave(const Stud& a, const Stud& b)
{
	return (a.final_med == b.final_med) ? a.final_vid < b.final_vid : a.final_med < b.final_med;
}

int nam(const Stud& a, const Stud& b)
{
	return a.vardas < b.vardas;
}

int sur(const Stud& a, const Stud& b)
{
	return a.pavarde < b.pavarde;
}

int ave(const Stud& a, const Stud& b)
{
	return a.final_vid < b.final_vid;
}

int med(const Stud& a, const Stud& b)
{
	return a.final_med < b.final_med;
}