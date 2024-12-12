#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include "person.h"
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <random>
#include <list>
#include <map>
#include <type_traits>
#include <ppl.h>
#include <iomanip>
#include <sstream>

/**
 @class Student
 @brief A simple student class with basic data variables.
 
The `student` class extends the `person` class and contains methods for calculating the final result
of a student based on their homework marks and exam result, as well as sorting students by different criteria.
*/
class student : public person{

private:

	/**
	@brief Homework marks.

	This vector stores the results of homeworks for the student.
	*/
	std::vector<int> homeworks_;

	/**
	 @brief Exam result.
	 
	 This variable stores the result of the students exam.
	 */
	int exam_;

	/**
	@brief Final result using average value of homeworks.

	@note Average value of homeworks * 0.4 + exam * 0.6.
	*/
	double final_average_;

	/**
	@brief Final result using median value of homeworks.

	@note Median value of homeworks * 0.4 + exam * 0.6.
	*/
	double final_median_;

	/**
	@brief Calculates final result by average value.
	 
	@param[in] homeworks The homework marks.
	@param[in] exam The exam reuslt.
	@return The final result.
	 
	@note Result formula is average value of homeworks * 0.4 + exam * 0.6.
	*/
	double final_ave(std::vector<int> homeworks, int exam);

	/**
	@brief Calculates final result by average value.
	 
	@param[in] homeworks The homework marks.
	@param[in] exam The exam reuslt.
	@return The final result.
	 
	@note Result formula is median value of homeworks * 0.4 + exam * 0.6.
	*/
	double final_med(std::vector<int> homeworks, int exam);
public:

	/**
	 @brief Overloaded output operator.
	 
	 This operator prints the student's data in the following order:
	 Name, Surname, final average, and final median.
	 
	 @param[out] os The output stream.
	 @param[in] s The student object.
	 
	 @note Uses `std::setw(18)` for the width and left alignment for output formatting.
	 */
	friend std::ostream& operator<<(std::ostream& os, const student& s);

	/**
	 @brief Overloaded input operator.
	 
	 This operator reads the student's data from an input stream, such as `std::cin`.
	 
	 @param[in] is The input stream.
	 @param[out] s The student object.
	 
	 @note When the input stream is `std::cin`, it provides terminal instructions for the user.
	 */
	friend std::istream& operator>>(std::istream& is, student& s);

	/**
	@brief Default constructor.
	
	Initializes a student object with default values.
	*/
	student();

	/**
	@brief Full constructor.

	Initializes a student object with a given name, surname, homework marks, and exam result.

	@param[in] name The student's name.
	@param[in] surname The student's surname.
	@param[in] homeworks The student's homework marks.
	@param[in] exam The student's exam result.
	*/
	student(std::string name, std::string surname, std::vector<int> homeworks, int exam);

	/**
	@brief Constructor with only name and surname.

	Initializes a student object with a given name and surname and
	generates random results for the student.

	@param[in] name The student's name.
	@param[in] surname The student's surname.
	*/
	student(std::string name, std::string surname);

	/**
	@brief Copy constructor.

	Initializes a student object as a copy of another student.

	@param[in] other The student object to copy from.
	*/
	student(const student& other);

	/**
	@brief Destructor.

	Destroys the student object.
	*/
	~student();


	/**
	 * @brief Sets the student's name.
	 *
	 * @param[in] name The student's name.
	 */
	inline void setName(const std::string& name) { name_ = name; }

	/**
	 * @brief Sets the student's surname.
	 *
	 * @param[in] surname The student's surname.
	 */
	inline void setSurname(const std::string& surname) { surname_ = surname; }

	/**
	 * @brief Sets the student's homework marks.
	 *
	 * @param[in] homework The student's homework marks.
	 */
	inline void setHomework(const std::vector<int>& homework) { homeworks_ = homework; }

	/**
	 * @brief Sets the student's exam result.
	 *
	 * @param[in] exam The student's exam result.
	 */
	inline void setExam(const int& exam) { exam_ = exam; }

	/**
	 * @brief Gets the student's name.
	 *
	 * @return The student's name.
	 */
	inline std::string name() const override { return name_; }

	/**
	 * @brief Gets the student's surname.
	 *
	 * @return The student's surname.
	 */
	inline std::string surname() const  override { return surname_; }

	/**
	 * @brief Gets the student's homework marks.
	 *
	 * @return A vector of the student's homework marks.
	 */
	inline std::vector<int> homeworks() const { return homeworks_; }

	/**
	 * @brief Gets the student's exam result.
	 *
	 * @return The student's exam result.
	 */
	inline int exam() const { return exam_; }

	/**
	 * @brief Gets the final average result.
	 *
	 * @return The final average result.
	 */
	inline double final_average() const { return final_average_; }

	/**
	 * @brief Gets the final median result.
	 *
	 * @return The final median result.
	 */
	inline double final_median() const { return final_median_; }


	/**
	 * @brief Assignment operator.
	 *
	 * Assigns the values of one student object to another.
	 *
	 * @param[in] other The student object to copy from.
	 *
	 * @return The current student object.
	 */
	student& operator=(const student& other);

};

/*
	COMPARATORS
*/

/**
 * @brief Comparator function for sorting students by name and surname.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by name and surname.
 */
int nam_sur(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by name and average result.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by name and average result.
 */
int nam_ave(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by name and median result.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by name and median result.
 */
int nam_med(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by surname and name.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by surname and name.
 */
int sur_nam(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by surname and average result.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by surname and average result.
 */
int sur_ave(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by surname and median result.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by surname and median result.
 */
int sur_med(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by average result and name.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by average result and name.
 */
int ave_nam(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by average result and surname.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by average result and surname.
 */
int ave_sur(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by average result and median result.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by average result and median result.
 */
int ave_med(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by median result and name.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by median result and name.
 */
int med_nam(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by median result and surname.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by median result and surname.
 */
int med_sur(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by median result and average result.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by median result and average result.
 */
int med_ave(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by name.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by name.
 */
int nam(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by surname.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by surname.
 */
int sur(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by average result.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by average result.
 */
int ave(const student& a, const student& b);

/**
 * @brief Comparator function for sorting students by median result.
 *
 * @param[in] a The first student.
 * @param[in] b The second student.
 *
 * @return A comparison result for sorting students by median result.
 */
int med(const student& a, const student& b);

/**
 * @brief Sorts a collection of students by a specified key.
 *
 * This function sorts students based on a given key, such as name, surname, average result, or median result.
 *
 * @tparam T The container type (e.g., vector or list).
 * @param[in/out] Students The container of students to sort.
 * @param[in] key The key used to determine the sorting order.
 */
template<typename T>
void sort_students(T& Students, const std::string& key);
template void sort_students<std::vector<student>>(std::vector<student>& Students, const std::string& key);
template void sort_students<std::list<student>>(std::list<student>& Students, const std::string& key);

#endif