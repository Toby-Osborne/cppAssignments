
#ifndef FLIGHTATTENDANT_HPP
#define FLIGHTATTENDANT_HPP

#include "Employee.hpp"
#include "Country.hpp"
#include <vector>

class FlightAttendant : public Employee {
private:
	FlightAttendant& operator=(const FlightAttendant& other);
	FlightAttendant(const FlightAttendant& other);
	std::vector<Country::Language> LanguagesSpoken;
public:
    FlightAttendant(const std::string &name, int ID);
    void addLanguage(Country::Language language);
    void removeLanguage(Country::Language language);
    bool canSpeak(Country::Language language) const;
};

#endif
