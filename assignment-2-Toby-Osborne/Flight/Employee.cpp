#include "Employee.hpp"

//constructs a new employee object with given arguments
Employee::Employee(const std::string &name, int ID): Human(name) {
	this->Name = name;
	this->EmployeeNumber = ID;
}

//returns the employee's id number
int Employee::getID() const {
	return this->EmployeeNumber;
}

Employee::~Employee() {
}
