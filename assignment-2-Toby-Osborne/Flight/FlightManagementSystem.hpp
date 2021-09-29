#ifndef FLIGHTMANAGEMENTSYSTEM_HPP
#define FLIGHTMANAGEMENTSYSTEM_HPP

#include <vector>
#include <string>

#include "Flight.hpp"
#include "Customer.hpp"




class FlightManagementSystem {
private:
	vector<Customer* > customers;
	vector<Flight* > flights;
	vector<Date* > dates;
	Customer* lookUpCustomer(const string &passportNumber) const;
public:
    FlightManagementSystem();

    static string author();
    bool bookTicket(Route* route, Date *time, const string &passportNumber, int quantity);
    bool addCustomer(Customer *customer);

    int getCapacity(const Route* route, const Date* time) const;
    void addFlight(Flight* flight, Date* time);
    int getCustomerPoints(const string &passportNumber) const;

    std::vector<Flight *> getFlights() const;
    std::vector<Date *> getDates() const;
    std::vector<Customer *> getCustomers() const;

    ~FlightManagementSystem();
};

#endif
