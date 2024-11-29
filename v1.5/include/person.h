#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED
	
#include <iostream>
#include <string>
	
class person {
protected:
	std::string name_;
	std::string surname_;

	person(const std::string& name, const std::string surname)
		: name_(name), surname_(surname) {}

public:

	virtual ~person() = default;

	virtual inline std::string name() const { return name_; }
	virtual inline std::string surname() const { return surname_; }

};
	
#endif
	