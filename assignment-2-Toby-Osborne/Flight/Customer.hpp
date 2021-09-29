#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include "Human.hpp"

class Customer : public Human {
private:
    Customer& operator=(const Customer& other);
    Customer(const Customer& other);
    int LoyaltyPoints = 0;

    std::string PassportNumber;
public:
    Customer(const std::string &name, const std::string &passportNumber);
    int getLoyaltyPoints() const;
    void addLoyaltyPoints(int points);
    void decreaseLoyaltyPoints(int points);
    std::string getPassportNumber() const;
};

#endif
