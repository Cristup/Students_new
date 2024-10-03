# Students

## Table of Contents
- [Description](#description)
- [Data Structure](#data-structure)
- [Usage](#usage)
- [Efficiency](#efficiency)

## Description
The **Students** application is designed to help working with students data. Mainly for writing and reading data and quickly finding final results of student.

## Data Structure
### Struct: `Stud`
- `string vardas`: Student's first name.
- `string pavarde`: Student's last name.
- `vector<int> nd`: Vector to store homework results.
- `int egz`: Exam result.
- `double vid`: Average of homework results.
- `double med`: Median of homework results.
- `category cat`: Categories: Under if result < 5 and Over if result >= 5

## Usage
To use the application, run the program and follow the prompts to input either student data, file name or choose to generate large test file. If you input data inside terminal, then you can choose between automatic generation of results or manual input.

After input using terminal, sorted student names and surnames together with final results will be printed in two result files, one for students with **final score Under 5** and one with **score 5 and higher**.

## Efficiency

### Sorting Function
The `sort_students` function implements **std::sort** with lambda function for sorting by two keys: **name** and **surname**. The asymptotic speed of **std::sort** is `O(n log n)` where `n` is number of students in a vector. Lmabda function campares two strings which involves cheking each cahracter in a string. Thus, for each comparison, the time complexity is `O(m)` where `m` is the average length of the strings involved.

Therefore, the overall time complexity of the `sort_students` function is: `O(n m log n)`.

Furthermore `sort_students` function is implemented in `sorting_in_threads` function, which splits sorting into separate threads for even faster results. 

**sort_students** funtion:
```cpp
void sort_students(vector<Stud>& local) {
	//labda function for sorting by two keys from Stud structure
	sort(local.begin(), local.end(), [](const Stud& a, const Stud& b) {
		if (a.vardas == b.vardas) {
			//comparing surnames in case if names are the same
			return a.pavarde < b.pavarde;
		}
		//comparing names
		return a.vardas < b.vardas;
		});
}
```
**sort_in_threads** function:
```cpp
void sorting_in_threads(vector<Stud>& local1, vector<Stud>& local2)
{
	vector<thread> threads;

	threads.push_back(thread(sort_students, ref(local1)));
	threads.push_back(thread(sort_students, ref(local2)));

	for (auto& th : threads) {
		th.join();
	}

}
```

### Speed measurements
Velocity was mesured using files of size `1 000`, `10 000`, `100 000`, `1 000 000` and `10 000 000`. Each speed result is an average of 5 tests. 

### File generation
For file of size `1 000`: **0.033 seconds**;

For file of size `10 000`: **0.293 seconds**;

For file of size `100 000`: **2.913 seconds**;

For file of size `1 000 000`: **29.629 seconds**;

For file of size `10 000 000`: **333.289 seconds (5 min 33 s)**.

### Data reading
For file of size `1 000`: **0.031 seconds**;

For file of size `10 000`: **0.303 seconds**;

For file of size `100 000`: **3.056 seconds**;

For file of size `1 000 000`: **29.237 seconds**;

For file of size `10 000 000`: **296.279 seconds (4 min 56 s)**.

### Data sorting and categorising
For file of size `1 000`: **0.017 seconds**;

For file of size `10 000`: **0.214 seconds**;

For file of size `100 000`: **2.414 seconds**;

For file of size `1 000 000`: **29.075 seconds**;

For file of size `10 000 000`: **330.778 seconds (5 min 30 s)**.

### Data writing to file
For file of size `1 000`: **0.008 seconds**;

For file of size `10 000`: **0.076 seconds**;

For file of size `100 000`: **0.714 seconds**;

For file of size `1 000 000`: **7.428 seconds**;

For file of size `10 000 000`: **27.385 seconds**.

### Total duration
For file of size `1 000`: **0.089 seconds**;

For file of size `10 000`: **0.885 seconds**;

For file of size `100 000`: **9.097 seconds**;

For file of size `1 000 000`: **95.369 seconds (1 min 35 s)**;

For file of size `10 000 000`: **987.731 seconds (16 min 27 s)**.

### Code for Measuring Execution Time
The following code snippet demonstrates how execution time is measured:

```cpp
auto start = std::chrono::high_resolution_clock::now();
// Function call
auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> duration = end - start;
std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
```
