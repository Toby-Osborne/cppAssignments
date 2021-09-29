#include "FlightManagementSystem.hpp"

#include <vector>
#include <string>
#include <iostream>
using namespace std;

//constructor
FlightManagementSystem::FlightManagementSystem(){
}

//author
string FlightManagementSystem::author() {
    return "tosb789";
}

//looks up customer object by passport
Customer* FlightManagementSystem::lookUpCustomer(const string &passportNumber) const{
	//for every customer pointer in customers
	for(unsigned int i = 0;i < customers.size() ; i++) {
		//if passport numbers match, return that customer pointer
		if(customers[i]->getPassportNumber() == passportNumber) {
			return customers[i];
		}
	}
	//if no customer is found, returns a null pointer instead of a customer pointer
	return NULL;
}

//attempts to book a quantity of tickets with specified route, time, for a customer with given passport number.
//will also update the loyalty points of the customer
bool FlightManagementSystem::bookTicket(Route* route, Date *time, const string &passportNumber, int quantity) {
	Customer* customer = lookUpCustomer(passportNumber);
	//nested if statements perform all required checks
	//if customer was found
	if(customer != NULL){
		//for every flight in flights
		for(unsigned int i = 0;i<flights.size();i++) {
			//checks that the origin points match
			if(flights[i]->getRoute()->getSource() == route->getSource()) {
				//checks that the destinations match
				if (flights[i]->getRoute()->getDestination() == route->getDestination()) {
					//dates and flights should match up/are always allocated together
					if((dates[i]->getDay() == time->getDay())&&(dates[i]->getHour() == time->getHour())){
						//this function returns true if there are enough available seats, and also
						//books the tickets if there are
						if(flights[i]->bookTicket(quantity)) {
							//adjusts the loyalty points based on booked tickets
							customer->addLoyaltyPoints(quantity*(flights[i]->getRoute()->getHours()));
							return true;
						} else {
							return false;
						}
					}
				}
			}
		}
	}
    return false;
}

//attempts to find the capacity of a given flight
int FlightManagementSystem::getCapacity(const Route* route, const Date *time) const {
	//for every element in flights vector
	for (unsigned int i = 0; i< flights.size() ; i++) {
		//checks sources match
		if(flights[i]->getRoute()->getSource() == route->getSource()) {
			//checks destinations match
			if (flights[i]->getRoute()->getDestination() == route->getDestination()) {
				//checks dates match
				if((dates[i]->getDay() == time->getDay())&&(dates[i]->getHour() == time->getHour())){
					//returns the capacity of that flight
					return flights[i]->getAvailableSeats();
				}
			}
		}
	}
	//return if not found
	return -1;
}

//looks up a customer using their passport number
int FlightManagementSystem::getCustomerPoints(const string &passportNumber) const {
	//finds the customer
	Customer* customer = lookUpCustomer(passportNumber);
	//if customer was found
	if(customer != NULL) {
		//return the customers loyalty points
		return customer->getLoyaltyPoints();
	}
	//if not found, return -1
	return -1;
}

//adds a customer to the customer vector
bool FlightManagementSystem::addCustomer(Customer *customer) {
	//saves the passport number to a variable on the stack for convenience
	std::string passportnumber = customer->getPassportNumber();
	//checks the passport number against all passport numbers currently stored
	for (unsigned int i = 0 ; i < customers.size() ; i++) {
		if(customers[i]->getPassportNumber() == passportnumber) {
			//if customer already added, return false
			return false;
		}
	}
	//customer not added, add them and return true
    customers.push_back(customer);
    return true;
}

//adds a flight to the flight vectors.
//no checks are performed, as we can consider every flight time as valid
void FlightManagementSystem::addFlight(Flight* flight, Date* time) {
	flights.push_back(flight);
	dates.push_back(time);
}

//returns the vector of pointers to flights
vector<Flight *> FlightManagementSystem::getFlights() const {
    return flights;
}

//this function is not used, but because the getFlights only returns the flights themselves,
//it follows that if you called this function for some reason, you would also require the dates
//those flights were on.
vector<Date *> FlightManagementSystem::getDates() const {
	return dates;
}

//returns the vector of pointers to customers
vector<Customer *> FlightManagementSystem::getCustomers() const {
	return customers;
}


FlightManagementSystem::~FlightManagementSystem() {
}

