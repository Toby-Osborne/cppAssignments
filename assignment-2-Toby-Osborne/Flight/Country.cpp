
#include "Country.hpp"

//country constructor
Country::Country(const string &name,Language language) {
	Name = name;
	this->language = language;
}

//returns the countries language
Country::Language Country::getLanguage() const {
    return this->language;
}

//returns the countries name
std::string Country::getName() const {
    return Name;
}
