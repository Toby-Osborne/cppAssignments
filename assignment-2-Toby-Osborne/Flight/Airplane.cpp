#include "Airplane.hpp"

//constructor creates airplane with Capacity capacity
Airplane::Airplane(int capacity) {
	if (capacity > 0) {
		Capacity = capacity;
	} else {
		Capacity = 0;
	}
}

//gets an airplanes capacity
int Airplane::getCapacity() const{
    return Capacity;
}
