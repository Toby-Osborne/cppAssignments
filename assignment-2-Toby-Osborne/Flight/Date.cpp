#include "Date.hpp"
//constructs a date object with day and hour saturated inside the range
Date::Date(int day, int hour) {
	changeSaturate(day,hour);
}

//returns the hour
int Date::getHour() const {
    return Hour;
}

//returns the day
int Date::getDay() const {
    return Day;
}

//I wrote this so I wouldn't be repeating code
//sets the date and hour to the passed in values, saturated within the range
//day and hour passed by reference
void Date::changeSaturate(int &day, int &hour) {
	if(hour > 23) {
		Hour = 23;
	} else if (hour < 0) {
		Hour = 0;
	} else {
		Hour = hour;
	}
	if (day < 1) {
		Day = 1;
	} else {
		Day = day;
	}
}

//changes the date to the given day
void Date::changeDateTo(int day, int hour) {
	changeSaturate(day,hour);
}

//adds some number of hours to the time
void Date::addTime(int count) {
	//I could have reassigned count to itself to save a variable, but I have not done so.  Why?  To promote chaos.
	//I spent good money on my memory, and I will use it how I please.
	int Total = count + 24*Day + Hour;
	//I looked everywhere and I couldn't find anything on what to do if the time was negative, so
	//I set it to the minimum of the range
	if (Total/24 > 0) {
		Day = Total/24;
		Hour = Total%24;
	} else {
		Day = 1;
		Hour = 0;
	}
}

//checks if the date object this function is called on is less than the other date object
bool Date::isLessThan(const Date &other) const {
	//evaluates it as a number of hours for simplicity
    return (((other.Day)*24+other.Hour)>((Day)*24+Hour));
}
