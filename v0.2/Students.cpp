#include "Mylib.h"
#include "Stud.h"
#include "Util.h"

int main()
{
    /*auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Execution time: " << duration.count() << " seconds" << endl;*/
    
    vector<Stud> Students;      //-Vector for storing students data
    vector<Stud> Students_Under;//-Vector for storing students data with final result Under 5
    vector<Stud> Students_Over; //-Vector for storing students data with final result 5 and Over
    Stud Temp_stud;             //-Temporary value for storing student data
    int n;                      //-Number of students
    string User_input;          //-Input that determine method of further input method
    bool CreateTestFile = false;//-User disision to create test file

     //Reapeating until good input
     while (true) {
         //First input
         cout << "Enter either file name, number of students or 'Generate' to create test file: ";
         cin >> User_input;         //-First input for task branching
         string original = User_input;     //-Original input
         
         //Transforming strings for a possible range of user misinputs
         transform(User_input.begin(), User_input.end(), User_input.begin(), ::tolower);

         if (is_digits(User_input)) {
             break;
         }
         else if (User_input.substr(0, 3) == "gen") {
             CreateTestFile = true;
             break;
         }
         else {
             //Opening file for testing
             ifstream file;
             try {
                 file.open(original);
                 if (!file) {
                     throw runtime_error("File not found!");
                 }
                 User_input = original;
                 break;
             }
             catch (const exception& e) {
                 cout << "Exeption: " << e.what() << endl;
                 continue;
             }
         }
         cout << "Invalid input! Try again.\n";
     }

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
    //Creating test file
    else if (CreateTestFile) {
        int number_of_lines;    //-Test data size
        string test_file_name;  //-Test data name
        string temp;            //-Temporary string

        //Getting valid input for creating data
        while (true) {
            cout << "Enter name for test data file: ";
            cin >> test_file_name;
            if (test_file_name.size() >= 5 && test_file_name.substr(test_file_name.size() - 4, 4) == ".txt") {
                break;
            }
            cout << "File name must end with '.txt'\n";
        }
        while (true) {
            cout << "Enter test file size: ";
            try {
                cin >> temp;
                number_of_lines = stoi(temp);
                if (number_of_lines < 100 || number_of_lines >= 10000000) {
                    throw out_of_range("Value out of range!");
                }
                break;
            }
            catch (const invalid_argument&) {
                cout << "Invalid input! Try again." << endl;
                continue;
            }
            catch (const out_of_range& e) {
                cout << "Exception: " << e.what() << endl;
                cout << "Number must be in range [1, 10 000 000]" << endl;
                continue;
            }
        }
        //creating data and reading for procesing
        create_data(test_file_name, number_of_lines);
        Input_from_file(Students, test_file_name);
    }
    //Students data input from file
    else {
        //Reading file
        Input_from_file(Students, User_input);
    }

    //Students data sorting & output
    sort_to_categories(Students, Students_Under, Students_Over);
    sorting_in_threads(Students_Under, Students_Over);
    output_with_multithreading(Students_Over, Students_Under);

    cout << "Results are in files: 'Stiprus.txt' & 'Silpni.txt'." << endl;
    system("pause");
}