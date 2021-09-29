#include "Pilot.hpp"

//constructs a new pilot
Pilot::Pilot(const std::string &name, int ID) : Employee(name, ID) {
}

//returns a pilots level
Pilot::Level Pilot::getLevel() const {
    return level;
}

//attempts to promote a co-pilot
bool Pilot::promote() {
	if (level == CO_PILOT) {
		level = CAPTAIN;
		return true;
	}
    return false;
}

//attempts to demote a captain
bool Pilot::demote() {
	if (level == CAPTAIN) {
		level = CO_PILOT;
		return true;
	}
    return false;
}
