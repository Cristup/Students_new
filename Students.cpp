#include "Mylib.h"
#include "Stud.h"
#include "Util.h"

int main()
{
    /*auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Execution time: " << duration.count() << " seconds" << endl;*/
    
    vector<Stud> Students;
    Stud Temp_stud; //Temporary student data
    int n; //Student count
    //Students data input---------------------------------------------------
    cout << "How many students? "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter student number " << i + 1 << " data: " << endl;
            input(Temp_stud);
            Students.push_back(Temp_stud);
            clean(Temp_stud);
    }
    //Students data output---------------------------------------------------
    output(Students);
    system("pause");
}