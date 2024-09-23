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
    string User_input; //Input that determine method of input
     cout << "Enter either file name or number of students: ";
     cin >> User_input;        
    //Students data input in terminal
    if (is_digits(User_input)) {
        n = stoi(User_input);
        
        for (int i = 0; i < n; i++) {
            cout << "Enter student number " << i + 1 << " data: " << endl;
            input(Temp_stud);
            Students.push_back(Temp_stud);
            clean(Temp_stud);
        }
    }
    //Students data input from file
    else {
        ifstream file;
        try {
            file.open(User_input);
            if (!file) {
                throw std::runtime_error("File not found!");
            }
        }
        catch (const std::exception& e) {
            cout << "Exeption " << e.what() << endl;
        }
        Input_from_file(Students, User_input);
    }
    //Students data output
    output(Students);
    system("pause");
}