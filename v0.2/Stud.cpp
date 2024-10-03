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
	cout << "Generated egzam result: " << local.egz << endl;

	//Generate number of homeworks
	int amount = Amount_interval(rd_generator);

	//Generate and print homework marks
	for (int i = 0; i < amount; i++) {
		local.nd.push_back(Results_interval(rd_generator));
		cout << "Generated home work result " << i + 1 << ": " << local.nd[i] << endl;
	}
}

void Manual_input(Stud& local)
{
	int Temp_nd,		//-Temporary place for storing a value
		nd_count	= 1,//-Total number and index of homeworks
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
				cout << "You must enter at least one home work!" << endl;
			}
			else if (empty_count == 2) {
				break;
			}
		}
		//Not positive integer input case
		else if (!is_digits(value)) {
			cout << "Invalid input! Try again." << endl;
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
			cout << "Value must be in the interval [1;10]!" << endl;
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
				cout << "Enter home work results (Press enter twice to finish)." << endl;
				Manual_input(local);
				break;
			}
			catch (const invalid_argument&) {
				cout << "Invalid input! Try again." << endl;
			}
			catch (const out_of_range&) {
				cout << "Number out of range! Try again." << endl;
			}
		}
	}
	//Other values
	local.vid = Average(local.nd);
	local.med = Median(local.nd);
	if (Result(local.egz, local.vid) < 5) {
		local.cat = Stud::category::Under;
	}
	else {
		local.cat = Stud::category::Over;
	}
}

void Input_from_file(vector<Stud>& local, string filename)
{
	Stud Temp_stud;			//Temporary value for storing single students data.
	int n = 0,				//Number of homeworks.
		Line_number = 0;	//For counting lines in the file.
	string	Temp_nd,		//Temporary value for storing homework mark.
			Temp_egzam,		//Temporary value for storing exam result.
			Temp_value,		//Temporary value for working with headline.
			name,			//Temporary value for student name.
			surname;		//Temporary value for student surname.

	//Opening file
	ifstream inFile; //-Data file
	inFile.open(filename);

	//Cheking file structure
	inFile >> Temp_value >> Temp_value; //Ignoring two strings
	inFile >> Temp_value;				//Third headline string which is first homework

	//Counting homeworks
	while (Temp_value.substr(0, 2) == "ND") {
		n++;
		inFile >> Temp_value;
	}

	//Reading data
	while (inFile >> name >> surname) {
		Line_number++;
		//Name & Surname
		Temp_stud.vardas = name;
		Temp_stud.pavarde = surname;
		//Homework marks
		try {
			for (int i = 0; i < n; i++) {
				inFile >> Temp_nd;
				Temp_stud.nd.push_back(stoi(Temp_nd));
			}
		}
		catch (const exception& ) {
			cout << "Invalid argument on line " << Line_number << "!" << endl;
			cout << "Data was skipped!" << endl;
			system("pause");
			//Ignore all characters ubtil '\n'
			inFile.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		//Egzam result
		try {
			inFile >> Temp_egzam;
			Temp_stud.egz = stoi(Temp_egzam);
		}
		catch (const exception&) {
			cout << "Invalid argument on line " << Line_number << "!" << endl;
			cout << "Data was skipped!" << endl;
			system("pause");
			//Ignore all characters ubtil '\n'
			inFile.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		//Average, Median values and category
		Temp_stud.vid = Average(Temp_stud.nd);
		Temp_stud.med = Median(Temp_stud.nd);
		if (Result(Temp_stud.egz, Temp_stud.vid) < 5) {
			Temp_stud.cat = Stud::category::Under;
		}
		else {
			Temp_stud.cat = Stud::category::Over;
		}

		//Saving to local vector
		local.push_back(Temp_stud);
		//Cleaning temporary value for next input
		clean(Temp_stud);
	}
	//Closing file
	inFile.close();
}

/*
		DATA OUTPUT FUNCTIONS
*/

void output(vector<Stud> local)
{
	//Table headline
	cout << "Name              |Surname           |Final result(Avg) |Final result(Med)" << endl;
	cout << "------------------+------------------+------------------+-----------------" << endl;
	//Data
	for (int i = 0; i < local.size(); i++) {
		cout << setw(18) << left << local[i].vardas << '|' <<
			setw(18) << left << local[i].pavarde << '|' <<
			setw(18) << fixed << setprecision(2) << Result(local[i].egz, local[i].vid) << "|" <<
			fixed << setprecision(2) << Result(local[i].egz, local[i].med) << endl;
	}
}

void output_to_file(const vector<Stud>& local, const string& filename)
{
	//Opening file
	ofstream outFile;	//-Results file
	outFile.open(filename);	//File name

	//Writing Headline
	outFile << "Name              Surname           Final result(Avg) Final result(Med)\n";
	outFile << "-----------------------------------------------------------------------\n";

	//Writing data
	for (int i = 0; i < local.size(); i++) {
		outFile << setw(18) << left << local[i].vardas <<
			setw(18) << left << local[i].pavarde <<
			setw(18) << fixed << setprecision(2) << Result(local[i].egz, local[i].vid) <<
			fixed << setprecision(2) << Result(local[i].egz, local[i].med) << "\n";
	}
	//Closing file
	outFile.close();
}

/*
		OTHER FUNCTIONS
*/

void sort_students(vector<Stud>& local) {
	//labda function for sorting by two keys of Stud structure
	sort(local.begin(), local.end(), [](const Stud& a, const Stud& b) {
		if (a.vardas == b.vardas) {
			//comparing surnames in case if names are the same
			return a.pavarde < b.pavarde;
		}
		//comparing names
		return a.vardas < b.vardas;
		});
}

void clean(Stud& local)
{
	local.vardas.clear();
	local.pavarde.clear();
	local.nd.clear();
}

void sort_to_categories(vector<Stud>& local, vector<Stud>& Under, vector<Stud>& Over)
{
	for (auto i : local) {
		if (i.cat == Stud::category::Under) {
			Under.push_back(i);
			clean(i);
		}
		else {
			Over.push_back(i);
			clean(i);
		}
	}
	local.clear();
}

void sorting_in_threads(vector<Stud>& local1, vector<Stud>& local2)
{
	vector<thread> threads;

	threads.push_back(thread(sort_students, ref(local1)));
	threads.push_back(thread(sort_students, ref(local2)));

	for (auto& th : threads) {
		th.join();
	}

}

void output_with_multithreading(vector<Stud>& Over, vector<Stud>& Under)
{
	vector<thread> threads;

	threads.push_back(thread(output_to_file, ref(Over), string("Stiprus.txt")));
	threads.push_back(thread(output_to_file, ref(Under), string("Silpni.txt")));

	for (auto& th : threads) {
		th.join();
	}
}