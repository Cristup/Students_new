# Students

## Table of Contents
- [Description](#description)
- [Data Structure](#data-structure)
- [Usage](#usage)
- [Efficiency](#efficiency)

## Description
The **Students** application is designed to help working with student data.

## Data Structure
### Struct: `Stud`
- `string vardas`: Student's first name.
- `string pavarde`: Student's last name.
- `vector<int> nd`: Vector to store homework results.
- `int egz`: Exam result.
- `double vid`: Average of homework results.
- `double med`: Median of homework results.

## Usage
To use the application, run the program and follow the prompts to input either student data or file name. If you input data inside terminal, then you can choose between automatic generation of results or manual input.

After input using terminal, sorted student names and surnames together with final results will be printed both in terminal and results file. And if data was read from file, then results will be printed only to file.

## Efficiency

Program bulds and runs in **9.568 seconds**.

### Sorting Function
The `sort_students` function implements **std::sort** with lambda function for sorting by two keys: **name** and **surname**. The asymptotic speed of **std::sort** is `O(n log n)` where `n` is number of students in a vector. Lmabda function campares two strings which involves cheking each cahracter in a string. Thus, for each comparison, the time complexity is `O(m)` where `m` is the average length of the strings involved.

Therefore, the overall time complexity of the sort_students function is: `O(n m log n)`

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

### Statistical Functions
This program utilizes two statistical functions:
1. **Average**: Calculates the average value of a vector.
2. **Median**: Computes the median value of a vector.

For the same vector of size **1070**:
- The **Average** function executed in **0.0000537 seconds**.
- The **Median** function executed in **0.0247537 seconds**.

```cpp
double Average(vector<int> nd)
{
	int sum = 0;
	for (int i = 0; i < nd.size(); i++) {
		sum += nd[i];
	}
	return (double)sum / nd.size();
}

double Median(vector<int> nd)
{
	int n = nd.size();
	sort(nd.begin(), nd.end());
	if (n % 2 != 0) {
		return nd[n / 2];
	}
	else {
		return (double)(nd[n / 2 - 1] + nd[n / 2]) / 2;
	}
}
```

**Average** funtion uses for cycle, which reapeats for the same number of times as size of a vector. Therfor speed of **average** function is O(n).

**Median** function uses std::sort with asymptotic speed O(n log n), where n is once again size of the vector.

### Data reading
Files of sizes **10000**, **1000000**  and **1000000** were used for mesuring program speed.

Reading data from file for each file:
1. For file with **10000** lines program took **0.26533 seconds**.
2. For file with **100000** lines program took **3.24163 seconds**.
3. For file with **1000000** lines program took **18.8752 seconds**.

Sorting data for each file:
1. For file with **10000** lines program took **0.130148 seconds**.
2. For file with **100000** lines program took **1.64338 seconds**.
3. For file with **1000000** lines program took **20.9452 seconds**.

Writing to results file for each file:
1. For file with **10000** lines program took **0.121206 seconds**.
2. For file with **100000** lines program took **1.19328 seconds**.
3. For file with **1000000** lines program took **12.2562 seconds**.

In total:
1. For file with **10000** lines program took **0.525315 seconds**.
2. For file with **100000** lines program took **6.25026 seconds**.
3. For file with **1000000** lines program took **50.3132 seconds**.

### Code for Measuring Execution Time
The following code snippet demonstrates how execution time is measured:

```cpp
auto start = std::chrono::high_resolution_clock::now();
// Function call
auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> duration = end - start;
std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
```