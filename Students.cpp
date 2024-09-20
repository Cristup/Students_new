#include "Mylib.h"
#include "Stud.h"

int main()
{
    vector<Stud> Students;
    Stud Temp_stud; //Temporary student data
    int n; //Student count
    int m; //Homework count
    //Students data input---------------------------------------------------
    cout << "How many students? "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter student number " << i + 1 << " data: " << endl;
            input(Temp_stud);
            Students.push_back(Temp_stud);
            clean(Temp_stud);
    }
    //Students data output---------------------------------------------------
    system("pause");
}
