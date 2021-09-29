#include "Route.hpp"

//constructs a new route
Route::Route(Country* source, Country* destination, int hours) {
	this->hours = hours;
	this->source = source;
	this->destination = destination;

}

//returns the source country
Country* Route::getSource() const{
    return source;
}

//returns the destination country
Country* Route::getDestination() const{
    return destination;
}

//returns the length of the flight
int Route::getHours() const{
    return hours;
}

Route::~Route(){
}
