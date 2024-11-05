# Students

## Table of Contents
- [Description](#description)
- [Usage](#how-to-use-the-program)
- [Installation](#installation)
- [Releases](#releases)
- [Efficiency](#efficiency)

## Description
The **Students** application is designed to help work with students' data. Mainly for writing and reading 
data and quickly finding students' final results. Also, it is equipped with functions for programs' various speed measurements. 

## How to use the program
After running the program you will see the list of commands. Commands can be categorized into three categories: working with data, testing programs, and other additional commands.

### Working with data

* `Open` - After running the command, the user is asked to make [these](#printing-and-sorting-key-selection) selections. The user will be provided with a similar table:   
<img src="Table_OF_txts.png" alt="Table of available .txt files" style="height: 140px;"/>   
Then user just needs to enter the ID of the files it wants to open.

* **Integer input** - After running the command, the user is asked to make [these](#printing-and-sorting-key-selection) selections. The integer he enters is the number of students, which data will have to be entered manually by the user. Every student's name and surname will have to be entered manually. Then there will be a couple of choices:
* 1. Enter the exam result and then the homework marks, and in the end, press ENTER twice.
* 2. Or enter `Auto` to generate exam results and a random number of homework marks. (Results are generated using Uniform Distribution.)

Here's a snippet of the code for data generating for one student:
```cpp
void Automatic_input(Stud& local)
{
	//Generate exam result and print them to terminal
	local.egz = Results_interval(rd_generator);
	cout << "\nGenerated egzam result: " << local.egz << endl;
	//Generate number of homeworks
	int amount = Amount_interval(rd_generator);
	//Generate and print homework marks
	local.nd.reserve(amount);
	cout << "Generated home work result: {";
	for (int i = 0; i < amount; i++) {
		local.nd.push_back(Results_interval(rd_generator));
		cout << local.nd[i] << ", ";}
	cout << "}" << endl;
}
```

### Testing the program

Here are the commands for measuring program efficiency, meant for optimizing the program.

* `Test` - This is the main command for testing the program's speed. After running the command, the user is asked to make [these](#printing-and-sorting-key-selection) selections. Then the user is provided with the same table of available **.txt** files. Then user needs to enter the IDs of files to be tested, also user can enter the same ID a few times and later get average value durations from all tests with that file.     
<img src="Testing.png" alt="Testing" style="height: 380px;"/>   

* `Create` - This command is for creating test data. Users can create multiple files by writing the file name and size for each data file they want to create.      
<img src="Generating.png" alt="File Generation" style="height: 220px;"/> 

* `Change`- This command lets the user change the container type (either **vector** or **list**) that will be used for storing students' data during processing.

* `Strategy` - This command lets the user choose one of 3 available strategies for categorizing students by their final result. [Here](#strategies) are the strategies.

* `Results` - This command prints tables in markdown format of testing data that was gathered since the start of running the program. Data is accumulated in these structures:

* Record
	- double **input**
	- double **sorting**
	- double **categorising**
	- double **output**
	- double **total**
	- int **count**

* Test_data
	- map<string, Record> **vec_test**
	- map<string, Record> **list_test**
	- map<string, double> **fg_durations**

### Additional commands

* `Info` - This command lists all commands for working with the program.

* `Show` - This command creates the table of available .txt files in the local directory. (**Debug** folder in version **v1.0**)

* `Check` - Prints currently used container type for storing data and strategy number for categorising students.

* `End` - For closing programs work.

### Printing and sorting key selection
For printing results to file, the user can choose one out of three options.

1. `Average` - to print the final result calculated using the average value of homework marks.
2. `Median` - to print the final result calculated using the median value of homework marks.
3. `Both` - to print both **1.** and **2.** options.    

<img src = "Print.png" alt = "Print Selection" style = "height: 130px;"/> 

For sorting data user can choose up to two keys from four available:
* Name
* Surname
* Average
* Median
     
<img src = "Keys.png" alt = "Print Selection" style = "height: 90px;"/> 

Here is the code for how sorting was implemented (key selection from user input and comparator selector):

```cpp
void find_keys(string& line, const enum selection& print_by, size_t& n_keys, vector<string>& keys)
{
	stringstream input(line),
		output;
	string key;
	bool name_used = false,
		surname_used = false,
		median_used = false,
		average_used = false;
	while (input >> key && n_keys < 2) {
		transform(key.begin(), key.end(), key.begin(), ::tolower);
		if (!name_used && key.substr(0, 3) == "nam") {
			output << "nam_";
			keys.push_back("Name");
			name_used = true;
			n_keys++;}
		else if (!surname_used && key.substr(0, 3) == "sur") {
			output << "sur_";
			keys.push_back("Surname");
			surname_used = true;
			n_keys++;}
		//<...>
		else continue;}
	line = output.str();
	line = line.substr(0, line.size() - 1);
}

template<typename T>
void sort_students(T& Students, const string& key) {
	map<string, int(*)(const Stud&, const Stud&)> comparators = {
		{"nam_sur", nam_sur}, {"nam_ave", nam_ave}
        /*<...>*/, {"med", med}};
	if constexpr (is_same<T, vector<Stud>>::value) {
		concurrency::parallel_sort(Students.begin(), Students.end(), comparators[key]);}
	else if constexpr (is_same<T, list<Stud>>::value) {
		Students.sort(comparators[key]);}
}
```

### Strategies

The program implements three strategies for categorizing students into two groups by their final results.

Here are the duration with data files of size `10 000` and `100 000` using diffrent strategies. Results are an average of 5 tests whith each file.

DATA CATEGORISING
| Size | Vector #1 | List #1 | Vector #2 | List #2 | Vector #3 | List #3 |
|:-------|:------:|:-------:|:------:|:-------:|:------:|:-------:|
| 10000 | **0.002231** | `0.002769` | **0.289413** | `0.000692` | **0.001754** | `0.000843` |
| 100000 | **0.018695** | `0.037012` | **41.425276** | `0.008061` | **0.027830** | `0.009392` |

1. Creating two new containers and copying data from the main container to those containers by checking the users' category.
```cpp
template<typename T>
void sort_to_categories1(T& local, T& Under, T& Over)
{
	//<...>
	for (auto& i : local) {
		if (i.cat == Stud::Under) {
			Under.push_back(i);
			clean(i);}
		else {
			Over.push_back(i);
			clean(i);}
    }
}
```

2. Creating only one container and leaving one category of students in the first container and those that need to are copied to the new container and erased from the first one.
```cpp
template<typename T>
void sort_to_categories2(T& firstc, T& newc)
{
	//<...>
	for (auto it = firstc.begin(); it != firstc.end();) {
		if (it->cat == Stud::Under) {
			newc.emplace_back(*it);
			it = firstc.erase(it);}
		else {
			++it;}
	}
}
```

3. This strategy implements both previous strategies based on container type with some "improvements".
```cpp
template<typename T>
void sort_to_categories3(T& local, T& Under, T& Over)
{
	if constexpr (is_same<T, vector<Stud>>::value) {
		//<...>
		auto it = std::partition(local.begin(), local.end(), [&](const auto& a) {return a.cat == Stud::Under; });
		Under.assign(local.begin(), it);
		Over.assign(it, local.end());
		local.clear();}
	else {
		for (auto it = Over.begin(); it != Over.end();) {
			if (it->cat == Stud::Under) {
				Under.emplace_back(*it);
				it = Over.erase(it);}
			else {
				++it;}
		}
	}
}
```

## Installation

Here are the steps to install and run the program:
1. Download release **v1.0** by going to releases, then release `v1.0` and press on `Source code (zip)`.
2. **Unzip** the file `Students-1.0.zip`.
3. Run the `run.bat` file.
4. Follow the instructions on the screen or read [instructions](#how-to-use-the-program) on how to use the program.

If everything is done right program should run immediately. To run the program again, next time you can run the `Students_App.exe` file found in the `Debug` folder or create **shortcut** by right-clicking on file `Students_App.exe` and there you should find an option **Create shortcut**, which can be moved to any convenient location from where then you'll be able to run the program.


## Efficiency

### System Specifications

* Processor (CPU)
    - **Model:** Intel(R) Core(TM) i3-1005G1
    - **Frequency:** 1.20 GHz (base)
    - **Number of Cores:** 2
    - **Number of Threads:** 4

* Memory (RAM)
    - **Capacity:** 20.0 GB
    - **Type:** DDR4

* Hard Drive (SSD)
    - **Type:** SSD (Solid State Drive)
    - **Capacity:** 224GB
    - **Read Speed:** Up to 520 MB/s
    - **Write Speed:** Up to 450 MB/s

### Speed measurements
Velocity was mesured using files of size `1 000`, `10 000`, `100 000`, `1 000 000` and `10 000 000`, using third strategie for categorising ,printing both final results and sorting by Average.
Each speed result is an average of 5 tests for both containers (**list** and **vector**).

### FILE GENERATION
| Size | Duration |
|:-------|-------:|
| 1000 | `0.005834` |
| 10000 | `0.053410` |
| 100000 | `0.523120` |
| 1000000 | `4.970607` |
| 10000000 | `51.500582` |

### Vector
| Size | Reading | Sorting | Categorising | Output | Total |
|:-------|:------:|:------:|:------------:|:------:|:------:|
| 1000 | `0.004975` | `0.000365` | `0.000144` | `0.002364` | `0.010166` |
| 10000 | `0.043517` | `0.001200` | `0.001762` | `0.015905` | `0.065391` |
| 100000 | `0.429476` | `0.008845` | `0.027861` | `0.137622` | `0.605705` |
| 1000000 | `4.133885` | `0.108026` | `0.301896` | `1.295788` | `5.840783` |
| 10000000 | `42.031892` | `1.118212` | `4.533231` | `13.469708` | `61.154339` |

### List
| Size   | Reading | Sorting | Categorising | Output | Total |
|:-------|:-------:|:-------:|:------------:|:------:|:------:|
| 1000 | `0.005205` | `0.000100` | `0.000120` | `0.002364` | `0.010360` |
| 10000 | `0.045749` | `0.001301` | `0.001229` | `0.014730` | `0.067156` |
| 100000 | `0.438405` | `0.029920` | `0.021619` | `0.139788` | `0.648227` |
| 1000000 | `4.338644` | `0.593802` | `0.257161` | `1.361221` | `6.741938` |
| 10000000 | `44.318183` | `9.359349` | `2.916692` | `14.062739` | `73.233081` |

## Releases
Here are brief descriptions of all releases, what has been added in each release, and performance changes.

#
### Pre-release
The base for the program. In this version structure for students data was created, which was later improved and some parts changed. The program accepted only manual input with a possibility to generate random results and printed results to terminal. All data was stored only in vector.

#
### v0.1
This version was focused on working with files and handling user mic inputs.

What's new:
1. Reading from file.
2. Writing to file.
3. Exception handling.

#
### v0.2
This version was meant for optimizing and doing different speed measurements. Also, implemented some new features.

What's new:
1. File testing.
2. Categorising.
3. Sorting key selection.
4. Test data generation.
5. Commands for working with the program.

#
### v0.3
Further optimization and new features.

What's new:
1. List.
2. Testing improvements.
3. Remake of working with the program.
4. Table of files in directory.
5. Results in Markdown format tables.

#
### v1.0
More testing and the possibility to install programs on any OS.

What's new:
1. Categorization strategies.
2. Progress bar for file generation.
3. Installation with CMake.