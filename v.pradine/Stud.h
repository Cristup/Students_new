#pragma once

#include "Mylib.h"
#include "Util.h"

struct Stud {
	string vardas, pavarde;
	vector<int> nd;
	int egz;
	double vid, med;
};

void Automatic_input(Stud& local)
{
	local.egz = dist(rd);
	cout << "Generated egzam result: " << local.egz << endl;
	int amount = dist(rd);
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
	while (true) {
		cout << "Enter home work number " << nd_count << " result: ";
		getline(cin, value);
		if (value.empty()) {
			empty_count++;
			if (empty_count == 2) {
				break;
			}
		}
		else {
			empty_count = 0;
			Temp_nd = stoi(value);
			local.nd.push_back(Temp_nd);
			nd_count++;
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
			try {
				int exam_result = stoi(line);
				local.egz = stoi(line);
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
	string type;
	double value;
	cout << "Choose what value to use for counting final result:" << endl;
	//Selecting value for counting of final result with input check
	while (true) {
		cout << "Average(Avg) or Median(Med): "; cin >> type;
		transform(type.begin(), type.end(), type.begin(), ::tolower);
		if (type.substr(0,2) == "av") {
			type = "Avg";
			break;
		}
		else if (type.substr(0, 2) == "me") {
			type = "Med";
			break;
		}
		else {
			cout << "Wrong value type! Try again." << endl;
		}
	}
	//Table printing
	cout << "Name        |Surname     |Final result(" << type << ")" << endl;
	cout << "------------+------------+-----------------" << endl;
	for (int i = 0; i < local.size(); i++) {
		//Choosing preferred value
		if (type == "Avg")
			value = local[i].vid;
		else
			value = local[i].med;
		//Printing
		cout << setw(12) << left << local[i].vardas << '|' <<
			setw(12) << left << local[i].pavarde << '|' <<
			fixed << setprecision(2) << Result(local[i].egz, value) << endl;
	}
}

void clean(Stud& local)
{
	local.vardas.clear();
	local.pavarde.clear();
	local.nd.clear();
}