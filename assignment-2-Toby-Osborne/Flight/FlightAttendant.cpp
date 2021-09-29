#include "FlightAttendant.hpp"
//constructs a new flight attendant with a name and id
FlightAttendant::FlightAttendant(const string &name, int ID) : Employee(name,ID) {
}

//checks if a flight attendant can speak a specific language
bool FlightAttendant::canSpeak(Country::Language language) const {
    for (unsigned int i = 0;i<LanguagesSpoken.size();i++) {
    	if (LanguagesSpoken[i] == language) {
    		return true;
    	}
    }
	return false;
}

//adds a language if its not currently spoken
void FlightAttendant::addLanguage(Country::Language language) {
	//if flight attendant doesn't currently speak that language
	if (!(this->canSpeak(language))) {
		//add the langnuage
		LanguagesSpoken.push_back(language);
	}
}

//removes a language from a flight attendants language list
//this function is for testing purposes only
void FlightAttendant::removeLanguage(Country::Language language) {
	for (unsigned int i = 0;i<LanguagesSpoken.size();i++) {
		if (LanguagesSpoken[i] == language) {
			LanguagesSpoken.erase(LanguagesSpoken.begin() + i);
			return;
		}
	}
	return;
}
