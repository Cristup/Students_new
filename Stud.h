#pragma once

#include "Mylib.h"

struct Stud {
	std::string vardas, pavarde;
	std::vector<int> nd;
	int egz;
	double rez, vid, med;
};

void input(Stud& local)
{
	int Temp_nd;
	cout << "Name, Surname, Egzam result: ";
	cin >> local.vardas >> local.pavarde >> local.egz;
	cout << "How many homework marks?"; cin >> m;
	for (int j = 0; j < m; j++) {
		cout << "Enter homework number " << j + 1 << " result: "; cin >> Temp_nd;
		local.nd.push_back(Temp_nd);
	}
}

void output(Stud local)
{

}

void clean(Stud& local)
{
	local.vardas.clear();
	local.pavarde.clear();
	local.nd.clear();
}