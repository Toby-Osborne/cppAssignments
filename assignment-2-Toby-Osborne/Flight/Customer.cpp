#include "Customer.hpp"

//customer constructor
Customer::Customer(const std::string &name, const std::string &passportNumber) : Human(name) {
	Name = name;
	PassportNumber = passportNumber;
}

//function adds loyalty points to the customer
void Customer::addLoyaltyPoints(int points) {
	LoyaltyPoints += points;
}

//function decreases loyalty points, but not beyond zero.
void Customer::decreaseLoyaltyPoints(int points) {
	LoyaltyPoints -= points;
	if (LoyaltyPoints < 0) {
		LoyaltyPoints = 0;
	}
}

//returns loyalty points
int Customer::getLoyaltyPoints() const {
    return LoyaltyPoints;
}

//returns a customers passport number
std::string Customer::getPassportNumber() const {
    return PassportNumber;
}
