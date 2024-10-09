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
         cout << "Enter either file name, number of students or 'Test' to create test file: ";
         cin >> User_input;         //-First input for task branching
         string original = User_input;     //-Original input
         
         //Transforming strings for a wider range of user misinputs
         transform(User_input.begin(), User_input.end(), User_input.begin(), ::tolower);

         if (is_digits(User_input)) {
             break;
         }
         else if (User_input.substr(0, 3) == "tes") {
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
                 cerr << "Exeption: " << e.what() << endl;
                 continue;
             }
         }
         cerr << "Invalid input! Try again.\n";
     }

    //Students data input in terminal in case first input is integer
    if (is_digits(User_input)) {

        //converting string to intger
        n = stoi(User_input);

        //reserving space
        Students.reserve(n);
        
        //Dat input for n number of students
        for (int i = 0; i < n; i++) {
            cout << "Enter student number " << i + 1 << " data: " << endl;
            input(Temp_stud);               //Writing
            Students.push_back(Temp_stud);  //Saving in vector
            clean(Temp_stud);               //Preparing temporary value for next input
        }
    }
    //Creating test file
    else if (CreateTestFile) {
        test_multiple_files();
        return 1;
    }
    //Students data input from file
    else {
        //Reading file
        Input_from_file(Students, User_input);
        //buffer_read(User_input, Students);
    }

    //Students data sorting & output
    //Choosing key
    string choices;
    vector<string> keys;
    cin.ignore();
    while (true) {
        cout << "Select keys for sorting {name, surname, result}: ";
        getline(cin, choices);
        find_keys(choices, keys);

        //Choosing comparator
        if (keys.at(0).substr(0, 3) == "nam" && keys.at(1).substr(0, 3) == "sur") {
            sort(Students.begin(), Students.end(), nam_sur);
            break;
        }
        else if (keys.at(0).substr(0, 3) == "nam" && keys.at(1).substr(0, 3) == "res") {
            sort(Students.begin(), Students.end(), nam_res);
            break;
        }
        else if (keys.at(0).substr(0, 3) == "sur" && keys.at(1).substr(0, 3) == "nam") {
            sort(Students.begin(), Students.end(), sur_nam);
            break;
        }
        else if (keys.at(0).substr(0, 3) == "sur" && keys.at(1).substr(0, 3) == "res") {
            sort(Students.begin(), Students.end(), sur_res);
            break;
        }
        else if (keys.at(0).substr(0, 3) == "res" && keys.at(1).substr(0, 3) == "nam") {
            sort(Students.begin(), Students.end(), res_nam);
            break;
        }
        else if (keys.at(0).substr(0, 3) == "res" && keys.at(1).substr(0, 3) == "sur") {
            sort(Students.begin(), Students.end(), res_sur);
            break;
        }
        else if (keys.at(0).substr(0, 3) == "nam") {
            sort(Students.begin(), Students.end(), nam);
            break;
        }
        else if (keys.at(0).substr(0, 3) == "sur") {
            sort(Students.begin(), Students.end(), sur);
            break;
        }
        else if (keys.at(0).substr(0, 3) == "res") {
            sort(Students.begin(), Students.end(), res);
            break;
        }
        else {
            cout << "Try again!" << endl;
        }
    }

    sort_to_categories(Students, Students_Under, Students_Over);
    output_with_multithreading(Students_Over, Students_Under);

    cout << "Results are in files: 'Stiprus.txt' & 'Silpni.txt'." << endl;
    system("pause");
}