#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED
	
#include <iostream>
#include <string>

/**
 @class Person
 @brief An abstract class representing a person with basic data variables.

The `person` class serves as a base class for other entities like `student`. It defines basic variables
for storing a person's name and surname, and includes two pure virtual functions `name()` and `surname()`
to retrieve these values.
*/
class person {
protected:

	/**
	@brief Name.

	This variable stores person Name.
	*/
	std::string name_;

	/**
	@brief Surname.

	This variable stores person Surname.
	*/
	std::string surname_;

	/**
	@brief Protected constructor.
	 
	Initializes a `person` object with a name and surname.
	 
	@param[in] name The person's name.
	@param[in] surname The person's surname.
	*/
	person(const std::string& name, const std::string surname)
		: name_(name), surname_(surname) {}

public:

	/**
	 * @brief Virtual destructor.
	 *
	 * Destroys the `person` object.
	 */
	virtual ~person() = default;

	/**
	 * @brief Virtual function to get the person's name.
	 *
	 * This pure virtual function must be overridden by derived classes.
	 *
	 * @return The person's name.
	 */
	virtual std::string name() const = 0;

	/**
	 * @brief Virtual function to get the person's surname.
	 *
	 * This pure virtual function must be overridden by derived classes.
	 *
	 * @return The person's surname.
	 */
	virtual std::string surname() const = 0;

};
	
#endif
	