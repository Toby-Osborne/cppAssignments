#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include "Pilot.hpp"
#include "Route.hpp"
#include "FlightAttendant.hpp"
#include "Airplane.hpp"
#include "Date.hpp"


class Flight{
private:
    Flight& operator=(const Flight& other);
    Flight(const Flight& other);
    Route* route;
	Airplane* airplane;
	int remainingSeats;
	vector<Pilot*> pilots;
	vector<FlightAttendant*> flightAttendants;
	bool pilotsAssigned = false;
	bool flightAttendantsAssigned = false;
	bool flightCheck(vector<FlightAttendant*>flightAttendants);
public:
    Flight(Route *route, Airplane* airplane);
	enum Duration {LONG, SHORT};
    bool setFlightAttendants(vector<FlightAttendant*> flightAttendants);
    bool setPilots(vector<Pilot*> pilots);
    bool bookTicket(int quantity);
    int getAvailableSeats() const;
    Route* getRoute() const;
    Airplane* getAirplane() const;
    vector<Pilot *> getPilots() const;
    vector<FlightAttendant *> getFlightAttendants() const;

    ~Flight();
private:
	Duration duration;

};

#endif
