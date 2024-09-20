#pragma once

#include "Mylib.h"
#include "Util.h"

struct Stud {
	std::string vardas, pavarde;
	std::vector<int> nd;
	int egz;
	double vid, med;
};

void input(Stud& local)
{
	int Temp_nd;
	int m;
	cout << "Name, Surname, Egzam result: ";
	cin >> local.vardas >> local.pavarde >> local.egz;
	cout << "How many homework marks?"; cin >> m;
	for (int j = 0; j < m; j++) {
		cout << "Enter homework number " << j + 1 << " result: "; cin >> Temp_nd;
		local.nd.push_back(Temp_nd);
	}
	local.vid = Average(local.nd);
	local.med = Median(local.nd);
}

void output(vector<Stud> local)
{
	cout << "Name        |Surname     |Final result(Avg)" << endl;
	cout << "------------+------------+-----------------" << endl;
	for (int i = 0; i < local.size(); i++) {
		cout << setw(12) << left << local[i].vardas << '|' <<
			setw(12) << left << local[i].pavarde << '|' <<
			fixed << setprecision(2) << Result(local[i].egz, local[i].vid) << endl;
	}
}

void clean(Stud& local)
{
	local.vardas.clear();
	local.pavarde.clear();
	local.nd.clear();
}