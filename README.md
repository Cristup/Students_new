# Students

## Table of Contents
- [Description](#description)
- [Efficiency](#efficiency)
- [Future Analysis](#future-analysis)
- [Data Structure](#data-structure)
- [Usage](#usage)

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
To use the application, run the program and follow the prompts to input student data. Choose between automatic generation of results or manual input.

## Efficiency
The program initializes and runs in under 3 seconds.

### Sorting Function
The `Sort` function implements a basic selection sort algorithm to sort a vector of integers in ascending order. For a vector of size **1070**, the sorting operation executed in **0.0168174 seconds**.

### Statistical Functions
This program utilizes two statistical functions:
1. **Average**: Calculates the average value of a vector.
2. **Median**: Computes the median value of a vector.

For the same vector of size **1070**:
- The **Average** function executed in **0.0000537 seconds**.
- The **Median** function executed in **0.0247537 seconds**.

## Future Analysis
Further efficiency analysis will be conducted in version **v0.1** of this program, focusing on input and output performance using files of varying sizes.

### Code for Measuring Execution Time
The following code snippet demonstrates how execution time is measured:

```cpp
auto start = std::chrono::high_resolution_clock::now();
// Function call
auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> duration = end - start;
std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;