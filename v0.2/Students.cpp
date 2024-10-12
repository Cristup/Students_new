#include "Mylib.h"
#include "Stud.h"
#include "Util.h"

int main()
{
    //All variables
    vector<Stud> Students;      //-Vector for storing students data
    vector<Stud> Students_Under;//-Vector for storing students data with final result Under 5
    vector<Stud> Students_Over; //-Vector for storing students data with final result 5 and Over
    Stud        Temp_stud;      //-Temporary value for storing student data
    string      main_input,
                key,
                filename;
    int number_of_students;
    enum program_branch { Test, Read, Manual } branch;
    selection print_by;
    vector<File_info> files;
    vector<string> testFiles;

    //Information for user
    stringstream functions;
    functions << "Input functions:\n" <<
        "'Test'    - selecting files for testing;\n" <<
        "'Create   - creating test data files;\n" <<
        "'Open'    - reading Students data;\n" <<
        "'Show'    - show available '.txt' files;\n" <<
        "'End'     - to stop application;\n" <<
        "`Info'    - to list commands'\n" <<
        "*integer* - number of students for manual input of data.\n";
    cout << functions.str();

    //Choosing function
    while (true) {
        cout << "Input function << ";
        cin >> main_input;
        transform(main_input.begin(), main_input.end(), main_input.begin(), ::tolower);

        if (main_input.substr(0, 3) == "tes") {
            branch = program_branch::Test;
            break;
        }
        else if (main_input.substr(0, 3) == "ope") {
            branch = program_branch::Read;
            break;
        }
        else if (main_input.substr(0, 3) == "end") {
            system("pause");
            return 1;
        }
        else if (main_input.substr(0, 3) == "inf") {
            cout << functions.str();
            continue;
        }
        else if (main_input.substr(0, 3) == "sho") {
            cout << "\nAvailable '.txt' files:\n";
            system("dir *.txt /B");
            continue;
        }
        else if (main_input.substr(0, 3) == "cre") {
            print_by = print_selection();
            key = sort_selection(print_by);
            create_file_selection(files);
            create_multiple_files(files);
            continue;
        }
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

    print_by = print_selection();
    key = sort_selection(print_by);
    cout << "Key is: " << key << endl;//////

    switch (branch)
    {
    case Test:
        file_selection(testFiles);
        test_multiple_files(testFiles, print_by, key);
        cout << "\nResults are in files: 'Stiprus.txt' & 'Silpni.txt'." << endl;
        return 1;
        break;
    case Read:
        cout << "Select file from this list:\n";
        system("dir *.txt /B");
        while (true) {
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
        Input_from_file(Students, filename);
        break;
    case Manual:
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
    
    sort_students(Students, key);
    sort_to_categories(Students, Students_Under, Students_Over);
    output_with_multithreading(Students_Over, Students_Under, print_by);
    cout << "Results are in files: 'Stiprus.txt' & 'Silpni.txt'." << endl;

    system("pause");
}