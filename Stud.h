#pragma once

#include "Mylib.h"
#include "Util.h"

struct Stud {
	string vardas, pavarde;
	vector<int> nd;
	int egz;
	double vid, med;
};

void clean(Stud& local)
{
	local.vardas.clear();
	local.pavarde.clear();
	local.nd.clear();
}

void Automatic_input(Stud& local)
{
	local.egz = dist(rd);
	cout << "Generated egzam result: " << local.egz << endl;
	int amount = dist1(rd);
	for (int i = 0; i < amount; i++) {
		local.nd.push_back(dist(rd));
		cout << "Generated home work result " << i + 1 << ": " << local.nd[i] << endl;
	}
}

void Manual_input(Stud& local)
{
	int Temp_nd, nd_count = 1;
	int empty_count = 0;
	string value;
	getline(cin, value); // line to delete left empty space
	while (true) {
		cout << "Enter home work number " << nd_count << " result: ";
		getline(cin, value);
		if (value.empty()) {
			empty_count++;
			if (nd_count == 1) {
				cout << "You must enter at least one home work!" << endl;
			}
			else if (empty_count == 2) {
				break;
			}
		}
		else if (!is_digits(value)) {
			cout << "Invalid input! Try again." << endl;
		}
		else if (stoi(value) > 0 && stoi(value) <= 10 ) {
			empty_count = 0;
			Temp_nd = stoi(value);
			local.nd.push_back(Temp_nd);
			nd_count++;
		}
		else {
			cout << "Value must be in the interval [1;10]!" << endl;
		}
	}
}

void input(Stud& local)
{
	string line;
	//Single values: name, surname, egzam result
	cout << "Name, Surname: ";
	cin >> local.vardas >> local.pavarde;
	while (true) {
		cout << "Enter egzam result or write 'auto' to generate egzam and home work results: ";
		cin >> line;
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		//Automatic input
		if (line.substr(0, 2) == "au") {
			Automatic_input(local);
			break;
		}
		//Manual input
		else {
			int exam_result;
			try {
				exam_result = stoi(line);
				if (exam_result < 1 || exam_result >= 10) {
					throw std::out_of_range("Value out of range!");
				}
				local.egz = exam_result;
				cout << "Enter home work results (Press enter twice to finish)." << endl;
				Manual_input(local);
				break;
			}
			catch (const std::invalid_argument&) {
				cout << "Invalid input! Try again." << endl;
			}
			catch (const std::out_of_range&) {
				cout << "Number out of range! Try again." << endl;
			}
		}
	}
	//Other values
	local.vid = Average(local.nd);
	local.med = Median(local.nd);
}

void output(vector<Stud> local)
{
	cout << "Name        |Surname     |Final result(Avg) |Final result(Med)" << endl;
	cout << "------------+------------+------------------+-----------------" << endl;
	for (int i = 0; i < local.size(); i++) {
		cout << setw(12) << left << local[i].vardas << '|' <<
			setw(12) << left << local[i].pavarde << '|' <<
			setw(18) << fixed << setprecision(2) << Result(local[i].egz, local[i].vid) << "|" <<
			fixed << setprecision(2) << Result(local[i].egz, local[i].med) << endl;
	}
}

void output_to_file(vector<Stud> local)
{
	ofstream outFile;
	outFile.open("Result.txt");

	outFile.close();
}

void Input_from_file(vector<Stud>& local, string filename)
{
	Stud Temp_stud;
	int n = 0, //Number of homeworks
		Temp_nd, Temp_egzam;
	string Temp_value,
		name, surname;

	ifstream inFile;
	inFile.open(filename);
	//Cheking file structure
	inFile >> Temp_value >> Temp_value; //Ignoring two strings
	inFile >> Temp_value;
	while (Temp_value.substr(0, 2) == "ND") {
		n++;
		inFile >> Temp_value;
	}
	//Reading data
	while (inFile >> name >> surname) {
		//name and surname
		Temp_stud.vardas = name;
		Temp_stud.pavarde = surname;
		//home works
		for (int i = 0; i < n; i++) {
			inFile >> Temp_nd;
			Temp_stud.nd.push_back(Temp_nd);
		}
		//egzam
		inFile >> Temp_egzam;
		Temp_stud.egz = Temp_egzam;
		//average and median values
		Temp_stud.vid = Average(Temp_stud.nd);
		Temp_stud.med = Median(Temp_stud.nd);
		//saving to local vector
		local.push_back(Temp_stud);
		clean(Temp_stud);
	}
	inFile.close();
}