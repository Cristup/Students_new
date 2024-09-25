#include "Mylib.h"
#include "Stud.h"
#include "Util.h"

int main()
{
    /*auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Execution time: " << duration.count() << " seconds" << endl;*/
    
    vector<Stud> Students;  //-Vector for storing students data
    Stud Temp_stud;         //-Temporary value for storing student data
    int n;                  //-Number of students
    string User_input;      //-Input that determine method of further input method

    //First input
     cout << "Enter either file name or number of students: ";
     cin >> User_input;

    //Students data input in terminal in case first input is integer
    if (is_digits(User_input)) {

        //converting string to intger
        n = stoi(User_input);
        
        //Dat input for n number of students
        for (int i = 0; i < n; i++) {
            cout << "Enter student number " << i + 1 << " data: " << endl;
            input(Temp_stud);               //Writing
            Students.push_back(Temp_stud);  //Saving in vector
            clean(Temp_stud);               //Preparing temporary value for next input
        }
        //Outputing data in terminal
        output(Students);
    }
    //Students data input from file
    else {
        //Opening file for testing
        ifstream file;
        try {
            file.open(User_input);
            if (!file) {
                throw std::runtime_error("File not found!");
            }
        }
        catch (const std::exception& e) {
            cout << "Exeption " << e.what() << endl;
            system("pause");
            return 1;
        }
        //Reading file in case it exists
        Input_from_file(Students, User_input);
    }
    //Students data sorting & output
    sort_students(Students);
    output_to_file(Students);

    cout << "Results are in file: 'Result.txt'." << endl;
    system("pause");
}