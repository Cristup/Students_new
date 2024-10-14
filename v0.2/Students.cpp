#include "Mylib.h"
#include "Stud.h"
#include "Util.h"

int main()
{
    //All variables inside main()
    vector<Stud> Students;              //-Vector for storing students data.
    vector<Stud> Students_Under;        //-Vector for storing students data with final result Under 5.
    vector<Stud> Students_Over;         //-Vector for storing students data with final result 5 and Over.
    Stud        Temp_stud;              //-Temporary value for storing student data.
    string      main_input,             //-User command.
                key,                    //-Key for sorting functions.
                filename;               //-Name of a file to read.
    int number_of_students;             //-Number of students in case of manual input.
    enum program_branch { Test, Read, Manual } branch;  //-Program branches.
    selection print_by;                 //-Result values to print.
    vector<File_info> files;            //-Files data {Name, Size} to create.
    vector<string> testFiles;           //-File names to test.
    stringstream functions;             //Information for user
    functions << "Input functions:\n" <<
        "'Test'    - selecting files for testing;\n" <<
        "'Create   - creating test data files;\n" <<
        "'Open'    - reading Students data;\n" <<
        "'Show'    - show available '.txt' files;\n" <<
        "'End'     - to stop application;\n" <<
        "`Info'    - to list commands'\n" <<
        "*integer* - number of students for manual input of data.\n";
    cout << functions.str();            //Printing functions at the begining

    //Choosing function
    while (true) {
        //Input
        cout << "Input function << ";
        cin >> main_input;
        //transforming to lower case for small user input mistakes
        transform(main_input.begin(), main_input.end(), main_input.begin(), ::tolower);

        //Test case
        if (main_input.substr(0, 3) == "tes") {
            branch = program_branch::Test;
            break;
        }
        //Case of reading existing file
        else if (main_input.substr(0, 3) == "ope") {
            branch = program_branch::Read;
            break;
        }
        //Ending programs work
        else if (main_input.substr(0, 3) == "end") {
            system("pause");
            return 1;
        }
        //Printing the list of functions
        else if (main_input.substr(0, 3) == "inf") {
            cout << functions.str();
            continue;
        }
        //Printing list of available .txt files
        else if (main_input.substr(0, 3) == "sho") {
            cout << "\nAvailable '.txt' files:\n";
            system("dir *.txt /B");

            continue;
        }
        //Creating of test data files
        else if (main_input.substr(0, 3) == "cre") {
            create_file_selection(files);
            create_multiple_files(files);
            continue;
        }
        //Cases for manual input and bad inputs
        else {
            try {
                number_of_students = stoi(main_input);
            }
            catch (const exception&) {
                cout << "Unknown command! Please try again.\n";
                continue;
            }
            branch = program_branch::Manual;
            break;
        }
    }

    //Key and result values selection
    print_by = print_selection();
    key = sort_selection(print_by);

    switch (branch)
    {
    case Test:
        file_selection(testFiles);  //Selecting file names for testing
        test_multiple_files(testFiles, print_by, key);  //Testing
        //Ending work
        cout << "\nResults are in files: 'Stiprus.txt' & 'Silpni.txt'." << endl;
        return 1;
        break;
    case Read:
        cout << "Select file from this list:\n";
        system("dir  *.txt /B"); //Printing list for choosing .txt file
        while (true) {
            //input
            cout << "\nInput name << ";
            cin >> filename;
            //Opening file for testing
            ifstream file;
            try {
                file.open(filename);
                if (!file) {
                    throw runtime_error("File not found!");
                }
                break;
            }
            catch (const exception& e) {
                cerr << e.what() << endl;
            }
        }
        Input_from_file(Students, filename);    //Reading the file
        break;
    case Manual:
        //Manual input
        Students.reserve(number_of_students);
        for (int i = 0; i < number_of_students; i++) {
            input(Temp_stud);
            Students.push_back(Temp_stud);
            clean(Temp_stud);
        }
        break;
    default:
        break;
    }
    
    sort_students(Students, key);   //Sorting data by users choosen key
    sort_to_categories(Students, Students_Under, Students_Over);    //Spliting data to categories
    output_to_file(Students_Over, "Stiprus.txt", print_by);         //Outputing to files
    output_to_file(Students_Under, "Silpni.txt", print_by);         //Outputing to files
    cout << "Results are in files: 'Stiprus.txt' & 'Silpni.txt'." << endl;

    system("pause");
}