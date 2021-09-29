#include "Human.hpp"

//class constructor for humans
Human::Human(const std::string &name) {
	Name = name;
}

//returns the name of the human
std::string Human::getName() const {
    return Name;
}

Human::~Human() {
}
