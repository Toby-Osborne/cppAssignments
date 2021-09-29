
#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include "Human.hpp"

class Employee : public Human {

protected:
    Employee(const std::string &name, int ID);
    int EmployeeNumber;
public:
    virtual int getID() const;
    ~Employee();
};

#endif
