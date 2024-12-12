#include "libs.h"
#include "student.h"
#include "person.h"
#include "util.h"
#include "data_util.h"

int main()
{
    //All variables inside main()
    vector<student> Students,           //-Vector for storing students data.
                Students_Under,         //-Vector for storing students data with final result Under 5.
                Students_Over;          //-Vector for storing students data with final result 5 and Over.
    list<student>  Students_list,       //-List for storing students data.
                Under_list,             //-List for storing students data with final result Under 5.
                Over_list;              //-List for storing students data with final result 5 and Over.
    string      main_input,             //-User command.
                key,                    //-Key for sorting functions.
                filename,               //-Name of a file to read.
                file_ID_string;         //-User input for file selection.
    int         number_of_students,     //-Number of students in case of manual input.
                file_ID;                //int type conversion from string type user input.
    selection print_by;                 //-Result values to print.
    vector<File_info> files;            //-Files data {Name, Size} to create.
    vector<Directory_files> directory;  //-Information about .txt files in local directory.
    vector<string> testFiles;           //-File names to test.
    stringstream info;                  //-Information for user about all commands.

    container_types container_type = container_types::Vector;
    strategy strat = strategy::s3;

    //Preparation of the program
    _mkdir("lists");
    update_info(info, container_type);
    update_files(directory);
    cout << "\033[" << 33 << "m" << info.str() << "\033[" << 97 << "m";

    //Choosing function
    while (true) {
        //Input
        cout << "\033[" << 33 << "m" << "Input function << " << "\033[" << 97 << "m";
        cin >> main_input;
        //transforming to lower case for small user input mistakes
        transform(main_input.begin(), main_input.end(), main_input.begin(), ::tolower);

        //Test case
        if (main_input.substr(0, 3) == "tes") {
            print_by = print_selection();
            key = sort_selection(print_by);
            file_selection(testFiles);  //Selecting file names for testing
            test_multiple_files(testFiles, print_by, key, container_type, strat);  //Testing
            testFiles.clear();
            continue;
        }
        //Enviroment for testing
        //####################################################################################
        if (main_input.substr(0, 3) == "env")
        {
            student a, b;
            cin >> a;
            b = a;
            student c(b);
            
            cout << a << b << c;

            student d;
            stringstream file_line_example("Vardas11 Pavarde11 6 7 6 8 7 9");
            file_line_example >> d;

            ofstream test_output("Student_output.txt");
            test_output << d;
            test_output.close();

            //person a;

        }
        //####################################################################################
        //Strategy
        if (main_input.substr(0, 3) == "str") {
            strat = cycle_strat(strat);
            continue;
        }
        //change container type
        else if (main_input.substr(0, 3) == "cha") {
            (container_type == container_types::Vector) ?
                container_type = container_types::List :
                container_type = container_types::Vector;
            update_info(info, container_type);
            get_type(container_type);
            continue;
        }
        //Print test results
        else if (main_input.substr(0, 3) == "res") {
            markdown_table();
            continue;
        }
        //Check container type
        else if (main_input.substr(0, 3) == "che") {
            get_type(container_type);
            cout << "Current strategy number is " << strat << "\n\n";
            continue;
        }
        //Case of reading existing file
        else if (main_input.substr(0, 3) == "ope") {
            print_by = print_selection();
            key = sort_selection(print_by);
            cout << "Select file from this by entering file ID.\n";
            //Printing list for choosing .txt file
            update_files(directory);
            table(directory);
            while (true) {
                //input
                cout << "\nInput ID << ";
                try {
                    cin >> file_ID_string;
                    file_ID = stoi(file_ID_string);
                }
                catch (exception& e) {
                    cerr << "Invalid ID! Try again.\n";
                    continue;
                }
                if (file_ID <= 0 || file_ID > directory.size()) {
                    cout << "Id not found!\n";
                    continue;
                }
                else if (directory.at(file_ID - 1).type == Directory_files::Results) {
                    cout << "You must choose data file and not results!\n";
                    continue;
                }
                else {
                    //Opening file for testing
                    ifstream file;
                    try {
                        file.open(directory.at(file_ID - 1).name);
                        if (!file) {
                            throw runtime_error("File not found!");
                        }
                        file.close();
                        break;
                    }
                    catch (const exception& e) {
                        cerr << e.what() << endl;
                        continue;
                    }
                }
            }
            filename = directory.at(file_ID - 1).name;
            printf("Reading %s\n", filename);
            //Reading data form a file
            (container_type == container_types::Vector) ? Input_from_file(Students, filename) : Input_from_file(Students_list, filename);
            printf("Sorting %s\n", filename);
            //Sorting data by users choosen key
            (container_type == container_types::Vector) ? sort_students(Students, key) : sort_students(Students_list, key);
            //Spliting data to categories
            (container_type == container_types::Vector) ?
                sort_to_categories(Students, Students_Under, Students_Over) :
                sort_to_categories(Students_list, Under_list, Over_list);
            printf("Printing %s\n", filename);
            //Outputing to files
            if (container_type == container_types::Vector) {
                concurrency::parallel_invoke(
                    [&]() {output_to_file(Students_Over, "Data.txt", print_by); },
                    [&]() {output_to_file(Students_Under, "Data.txt", print_by); }
                );
            }
            else {
                concurrency::parallel_invoke(
                    [&]() {output_to_file(Over_list, "Data.txt", print_by); },
                    [&]() {output_to_file(Under_list, "Data.txt", print_by); }
                );
            }
            string name_front = filename.substr(0, filename.size() - 4);
            cout << "Results are in files: '" << name_front + "_stiprus.txt' & '" << name_front + "_silpni.txt'." << endl;
            continue;
        }
        //Ending programs work
        else if (main_input.substr(0, 3) == "end") {
            system("pause");
            return 0;
        }
        //Printing the list of functions
        else if (main_input.substr(0, 3) == "inf") {
            cout << "\033[" << 33 << "m" << info.str() << "\033[" << 97 << "m";
            continue;
        }
        //Printing list of available .txt files
        else if (main_input.substr(0, 3) == "sho") {
            cout << "\nAvailable '.txt' files:\n";
            update_files(directory);
            table(directory);
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
            //Key and result values selection
            print_by = print_selection();
            key = sort_selection(print_by);
            //Manual input
            if (container_type == container_types::Vector) {
                
                for (int i = 0; i < number_of_students; i++) {
                    manual_input(Students);
                }
            }
            else {
                for (int i = 0; i < number_of_students; i++) {
                    manual_input(Students_list);
                }
            }
            //Sorting data by users choosen key
            if (container_type == container_types::Vector) {
                printf("Sorting vector.\n");
                sort_students(Students, key);
                //Spliting data to categories
                sort_to_categories(Students, Students_Under, Students_Over);

                output_to_screen(Students);
                printf("Printing vector.\n");
                //Outputing to files
                if (!Students_Over.empty() && !Students_Under.empty()) {
                    concurrency::parallel_invoke(
                        [&]() {output_to_file(Students_Over, "Data.txt", print_by); },
                        [&]() {output_to_file(Students_Under, "Data.txt", print_by); });
                }
                else if (!Students_Over.empty()) output_to_file(Students_Over, "Data.txt", print_by);
                else if (!Students_Under.empty())output_to_file(Students_Under, "Data.txt", print_by);
            }
            else {
                printf("Sorting list.\n");
                sort_students(Students_list, key);
                //Spliting data to categories
                sort_to_categories(Students_list, Under_list, Over_list);

                output_to_screen(Students_list);
                //Outputing to files
                printf("Printing list.\n");
                concurrency::parallel_invoke(
                    [&]() {output_to_file(Over_list, "Data.txt", print_by); },
                    [&]() {output_to_file(Under_list, "Data.txt", print_by); }
                );
            }
            cout << "Results are in files: 'Data_stiprus.txt' & 'Data_silpni.txt'." << endl;
            continue;
        }
    }
}