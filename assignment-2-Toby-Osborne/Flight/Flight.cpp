#include "Flight.hpp"
#include <iostream>
using namespace std;
#define MAXHOURS 8

//the final boss of Assignment 2

//constructs a flight, and checks if its long or short
Flight::Flight(Route *route, Airplane* airplane) {
	this->route = route;
	this->airplane = airplane;
	//for a flight, initializes the remaining seats based on the plane
	remainingSeats = airplane->getCapacity();
	if (route->getHours() < MAXHOURS) {
		duration = SHORT;
		remainingSeats -= 3;
	} else {
		duration = LONG;
		remainingSeats -= 8;
	}
	if (remainingSeats < 0) {
		remainingSeats = 0;
	}
}

//returns the remaining seats on the flight
int Flight::getAvailableSeats() const {
    return remainingSeats;
}



//I originally had my own implementation of this, but then I realized this function definition was here
bool Flight::bookTicket(int quantity) {
	//tries to book the seats if it can
	if (remainingSeats >= quantity) {
		remainingSeats -= quantity;
		return true;
	}
    return false;
}


//attempts to assign a pilot crew to the flight
bool Flight::setPilots(vector<Pilot*> pilots) {
	//
	if (pilotsAssigned) {
		return false;
	}
    int PILOTS;
    int COPILOTS;
    //assigns some counter variables based on the duration
	if (duration == LONG) {
    	PILOTS = 2;
    	COPILOTS = 2;
    } else {
    	PILOTS = 1;
    	COPILOTS = 1;
    }
	//for every pilot in the list
	for (unsigned int i = 0; i < pilots.size() ; i++) {
		//decrements the correct counter variable
		if (pilots[i]->getLevel() == Pilot::CAPTAIN) {
			PILOTS--;
		} else {
			COPILOTS--;
		}
	}
	//if the crew has the correct number of pilots and co-pilots, these should both be zero
	//so set pilots and return true.
	if ((PILOTS == 0) && (COPILOTS == 0)) {
		this->pilots = pilots;
		pilotsAssigned = true;
		return true;
	}
	//else return false
	return false;
}

//lord help us
//attempts to assign a flight attendant team to the flight object
bool Flight::setFlightAttendants(vector<FlightAttendant*> flightAttendants) {
	if (flightAttendantsAssigned) {
		return false;
	}
	//creates a variable representing how many flight attendants are required
	//this saves a lot of checks
	unsigned int FLIGHTATTENDANTS;
	//if long flight, 6 needed, else 3
	if (duration == LONG) {
    	FLIGHTATTENDANTS = 6;
    } else {
    	FLIGHTATTENDANTS = 3;
    }
	//if the flight team is the correct size (saves a lot of time).
	if (FLIGHTATTENDANTS == flightAttendants.size()) {
		//if there are 6 attendants
			//calls helper function
			if(flightCheck(flightAttendants)) {
				this->flightAttendants = flightAttendants;
				flightAttendantsAssigned = true;
				return true;
			}
	}
    return false;
}

//turn back now if you have a passion for elegant code
//note:  this could be contained within the setFlightAttendants method, but for readability and to make it
//easier for me to update, I have separated it into another method.
bool Flight::flightCheck(vector<FlightAttendant*>flightAttendants) {
	//it is much easier to initialize a 6x6 array on the stack of this function than to have a conditionally
	//initialized array of either 3x3 or 6x6 on the heap.  I did try that, but I couldn't get it to work, so
	//I stuck with this.
	int languageVsAttendant[6][6] = {0};

	//it is useful to have this number without calling a method
	int numAttendants = flightAttendants.size();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//EXPLAINATION OF METHOD:  Fills an either 3 by 3 or 6 by 6 array with 1's or 0's.  The rows are languages
	//						   That need to be filled, the columns are flight attendants.  a 1 means an attendant
	//						   speaks that language, a 0 means they do not.  The algorithm attempts to path
	//						   the matrix from top to bottom, looking for a combination where every column is
	//						   used only once, and all rows are filled.  This indicates that there is 1 attendant
	//						   for every language, exactly.
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//the first 3 rows (language slots) need to be filled regardless
	for (int j = 0;j<numAttendants;j++) {
		if (flightAttendants[j]->canSpeak(Country::ENGLISH)) {
			languageVsAttendant[0][j] = 1;
		}
		if (flightAttendants[j]->canSpeak((route->getDestination())->getLanguage())) {
			languageVsAttendant[1][j] = 1;
		}
		if (flightAttendants[j]->canSpeak((route->getSource())->getLanguage())) {
			languageVsAttendant[2][j] = 1;
		}
	}
	//if there are 6 attendants, then the next 3 rows need to be filled.  In both cases, columns are filled
	//based on numAttendants.
	if (numAttendants == 6) {
		for (int j = 0;j<6;j++) {
			if (flightAttendants[j]->canSpeak(Country::ENGLISH)) {
				languageVsAttendant[3][j] = 1;
			}
			if (flightAttendants[j]->canSpeak((route->getDestination())->getLanguage())) {
				languageVsAttendant[4][j] = 1;
			}
			if (flightAttendants[j]->canSpeak((route->getSource())->getLanguage())) {
				languageVsAttendant[5][j] = 1;
			}
		}
	}

	//by only going up to numAttendants, and returning true if numAttendants == 3, this will treat the 6,6 array
	//as 3,3 or 6,6.
	//it should only execute the code to check the next language if the previous language was correct, which
	//is somewhat efficient.  I am sure there are better ways to do this, but I cannot figure them out.

	//checks first language slot
	for (int j = 0;j<numAttendants;j++) {
		if (languageVsAttendant[0][j] == 1) {
			//checks second language slot
			for (int k = 0;k < numAttendants;k++) {
				if ((languageVsAttendant[1][k] == 1) && (k!=j)){
					//checks third language slot
					for(int l = 0;l<numAttendants;l++){
						if((languageVsAttendant[2][l] == 1)&&(l!=k)&&(l!=j)){
							//if it gets to this point, it means that it has filled 3 slots with 3 attendants.
							//If there is only 3 attendants, its a valid combination.
							if (numAttendants == 3) {
								return true;
							} else {
								//checks 4th language slot
								for(int m = 0;m<numAttendants;m++) {
									if((languageVsAttendant[3][m]==1)&&(m!=l)&&(m!=k)&&(m!=j)) {
										//checks 5th language slot
										for(int n = 0;n<numAttendants;n++) {
											if((languageVsAttendant[4][n]==1)&&(n!=m)&&(n!=l)&&(n!=k)&&(n!=j)){
												//checks 6th language slot
												for(int o = 0;o<numAttendants;o++) {
													//the additional && statements check that the column does not
													//math one already being used in this combination
													if((languageVsAttendant[5][o]==1)&&(o!=n)&&(o!=m)&&(o!=l)&&
															(o!=k)&&(o!=j)) {
														return true;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//if no combination is found, return false
	return false;
}

//returns the flight's route
Route* Flight::getRoute() const {
    return route;
}

//returns the flight's airplane
Airplane* Flight::getAirplane() const {
   return airplane;
}

//returns the vector of pilots, if they've been assigned, else returns an empty vector (pilots is empty if
//unassigned)
vector<Pilot*> Flight::getPilots() const {
	return pilots;
}

//returns the vector of flight attendants if assigned, else returns an empty vector
vector<FlightAttendant *> Flight::getFlightAttendants() const {
	return flightAttendants;
}

Flight::~Flight() {
}
