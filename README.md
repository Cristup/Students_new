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
- `double final_vid`: Result using average value of homeworks.
- `double final_med`: Result using median value of homeworks.
- `category cat`: Categories: Under if result < 5 and Over if result >= 5.

## Usage
To use the application, run the program and follow the prompts to input one of the listed commands.

## Efficiency

### Sorting Function
For sorting **std::sort** was used with comparator function for sorting by diffrent keys. The asymptotic speed of **std::sort** is `O(n log n)` where `n` is number of students in a vector. Comparator function in some cases campares two strings which involves cheking each cahracter in a string. Thus, for each comparison, the time complexity is `O(m)` where `m` is the average length of the strings involved.

Therfore, overall asymptotic speed of sorting is `O(m*n log(n))`.

### Speed measurements
Velocity was mesured using files of size `1 000`, `10 000`, `100 000`, `1 000 000` and `10 000 000`. Each speed result is an average of 5 tests. 

### File generation
Time of file generation was mesuered seperatly(not included in total time).

For file of size `1 000`: **0.010 seconds**;

For file of size `10 000`: **0.068 seconds**;

For file of size `100 000`: **0.644 seconds**;

For file of size `1 000 000`: **6.317 seconds**;

For file of size `10 000 000`: **68.644 seconds (1 min 9 s)**.

### Data reading
For file of size `1 000`: **0.005 seconds**;

For file of size `10 000`: **0.043 seconds**;

For file of size `100 000`: **0.419 seconds**;

For file of size `1 000 000`: **4.124 seconds**;

For file of size `10 000 000`: **40.746 seconds**.

### Data sorting
For file of size `1 000`: **0.0002 seconds**;

For file of size `10 000`: **0.003 seconds**;

For file of size `100 000`: **0.034 seconds**;

For file of size `1 000 000`: **0.430 seconds**;

For file of size `10 000 000`: **6.433 seconds**.

### Categorising
For file of size `1 000`: **0.0003 seconds**;

For file of size `10 000`: **0.003 seconds**;

For file of size `100 000`: **0.028 seconds**;

For file of size `1 000 000`: **0.178 seconds**;

For file of size `10 000 000`: **1.802 seconds**.

### Data output to file
For file of size `1 000`: **0.061 seconds**;

For file of size `10 000`: **0.008 seconds**;

For file of size `100 000`: **0.074 seconds**;

For file of size `1 000 000`: **0.786 seconds**;

For file of size `10 000 000`: **7.293 seconds**.

### Total duration
For file of size `1 000`: **0.0087 seconds**;

For file of size `10 000`: **0.078 seconds**;

For file of size `100 000`: **0.728 seconds**;

For file of size `1 000 000`: **7.679 seconds**;

For file of size `10 000 000`: **56.274 seconds**.