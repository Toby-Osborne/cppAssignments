#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>

// flags to enable tests for the later parts of the assignment
#define ENABLE_T2_TESTS
#define ENABLE_T3_TESTS
#define ENABLE_T4_TESTS

// include headers for classes being tested
#include "Flight/FlightManagementSystem.hpp"
#include "Flight/Country.hpp"
#include "Flight/Airplane.hpp"
#include "Flight/Date.hpp"

#ifdef ENABLE_T2_TESTS
#include "Flight/Customer.hpp"
#include "Flight/Pilot.hpp"
#include "Flight/FlightAttendant.hpp"

#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS
#include "Flight/Flight.hpp"
#include "Flight/Route.hpp"

#endif /*ENABLE_T3_TESTS*/

using namespace std;

enum TestResult { TR_PASS, TR_FAIL };

#define ASSERT(condition);                                                        \
    if ((condition) == false) {                                                   \
        cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                \
             << "\tExpression '" << #condition << "' evaluated to false" << endl; \
        return TR_FAIL;                                                           \
    }


TestResult testUsername() {
    string upi = FlightManagementSystem::author();

    // UPIs should be at least 4 characters long
    ASSERT(upi.size() >= 4);
    // First character should be alphabetic
    ASSERT(isalpha(upi[0]));
    // Last 3 characters should be numeric
    ASSERT(isdigit(upi[upi.size() - 1]));
    ASSERT(isdigit(upi[upi.size() - 2]));
    ASSERT(isdigit(upi[upi.size() - 3]));

    // If nothing went wrong, the test passed
    return TR_PASS;
}

TestResult testCountry() {
    Country newZealand("New Zealand", Country::ENGLISH);
    ASSERT(newZealand.getLanguage() == Country::ENGLISH);
    ASSERT(newZealand.getName() == "New Zealand");

    return TR_PASS;
}

TestResult testAirplane(){
    Airplane airplane(300);
    ASSERT(airplane.getCapacity() == 300);

    return TR_PASS;
}

TestResult testTime1() {
    Date time(1, 4);
    ASSERT(time.getDay() == 1);
    ASSERT(time.getHour() == 4);

    return TR_PASS;
}

TestResult testTime2() {
    Date time(1, 4);
    time.addTime(5);
    ASSERT(time.getDay() == 1);
    ASSERT(time.getHour() == 9);

    time.addTime(24);
    ASSERT(time.getDay() == 2);
    ASSERT(time.getHour() == 9);

    time.addTime(18);
    ASSERT(time.getDay() == 3);
    ASSERT(time.getHour() == 3);

    return TR_PASS;
}

////////////
//My Tests//
////////////
TestResult dateRigorous() {
	Date time(-1,-1);
	Date time2(-100,24);
	ASSERT(time.getDay() == 1);
	ASSERT(time.getHour() == 0);
	ASSERT(time2.getDay() == 1);
	ASSERT(time2.getHour() == 23);
	time.addTime(-1000);
	ASSERT(time.getDay() == 1);
	ASSERT(time.getHour() == 0);
	time.changeDateTo(-1,-1);
	time2.changeDateTo(100,100);
	ASSERT(time.getHour() == 0);
	ASSERT(time.getDay() == 1);
	ASSERT(time2.getHour() == 23);
	ASSERT(time2.getDay() == 100);
	ASSERT(time.isLessThan(time2));
	ASSERT(!time2.isLessThan(time));

	return TR_PASS;
}

#ifdef ENABLE_T2_TESTS

/* Test the behaviour of the Customer class */
TestResult testCustomer() {

    Customer *ben = new Customer("Ben", "PW2342");
    ASSERT(ben->getPassportNumber() == "PW2342");
    ASSERT(ben->getLoyaltyPoints() == 0);
    ben->addLoyaltyPoints(340);
    ASSERT(ben->getLoyaltyPoints() == 340);
    ben->decreaseLoyaltyPoints(34);
    ASSERT(ben->getLoyaltyPoints() == 306);

    Human *benHuman = ben;
    ASSERT(benHuman->getName() == "Ben");

    delete ben;
    return TR_PASS;
}

/* Test the behaviour of the FlightAttendant class */
TestResult testFlightAttendant() {

    FlightAttendant *sara = new FlightAttendant("Sara", 123);
    ASSERT(sara->getName() == "Sara");
    ASSERT(sara->getID() == 123);
    sara->addLanguage(Country::ENGLISH);
    sara->addLanguage(Country::SPANISH);
    sara->addLanguage(Country::CHINESE);

    ASSERT( sara->canSpeak(Country::CHINESE) );
    ASSERT( sara->canSpeak(Country::ENGLISH) );
    ASSERT( sara->canSpeak(Country::SPANISH) );
    ASSERT( ! sara->canSpeak(Country::ARABIC) );
    ASSERT( ! sara->canSpeak(Country::HINDI) );

    Human *saraHuman = sara;
    ASSERT(saraHuman->getName() == "Sara");

    Employee *saraEmployee = sara;
    ASSERT(saraEmployee->getName() == "Sara");
    ASSERT(saraEmployee->getID() == 123);

    delete sara;
    return TR_PASS;
}

/* Test the behavior ofthe Pilot class */
TestResult testPilot() {

    Pilot *jenny = new Pilot("Jenny", 456);
    ASSERT(jenny->getName() == "Jenny");
    ASSERT(jenny->getID() == 456);
    ASSERT(jenny->getLevel() == Pilot::CO_PILOT);

    ASSERT(jenny->promote());
    ASSERT(jenny->getLevel() == Pilot::CAPTAIN);
    ASSERT(!jenny->promote());

    ASSERT(jenny->demote());
    ASSERT(jenny->getLevel() == Pilot::CO_PILOT);

    Human *jennyHuman = jenny;
    ASSERT(jennyHuman->getName() == "Jenny");

    Employee *jennyEmployee = jenny;
    ASSERT(jennyEmployee->getName() == "Jenny");
    ASSERT(jennyEmployee->getID() == 456);

    delete jenny;
    return TR_PASS;
}

#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS

/*
 * Checking the Route class
 */
TestResult testRoute() {
    Country *source = new Country("Auckland", Country::ENGLISH);
    Country *destination = new Country("Shanghai", Country::CHINESE);

    Route path(source, destination, 12);
    ASSERT(path.getSource()->getName() == "Auckland");
    ASSERT(path.getDestination()->getName() == "Shanghai");
    ASSERT(path.getHours() == 12);

    return TR_PASS;
}

/*
 * Check the Flight class
 */
TestResult testFlightConstructor() {
    Country *source = new Country("Auckland", Country::ENGLISH);
    Country *destination = new Country("Shanghai", Country::CHINESE);
    Route *path = new Route(source, destination, 12);
    Airplane *airplane = new Airplane(300);

    Flight flight(path, airplane);
    ASSERT(flight.getAirplane() == airplane);
    ASSERT(flight.getRoute() == path);

    // 6 seats required for flight attendants, & 2 seats for spare captain/pilot
    ASSERT(flight.getAvailableSeats() == 292);

    return TR_PASS;
}

/*
 * Check correctly adding pilots to a Flight
 */
TestResult testFlightAddPilots() {
    Country *source = new Country("London", Country::ENGLISH);
    Country *destination = new Country("Madrid", Country::SPANISH);

    Route *path = new Route(source, destination, 3);
    Airplane *airplane = new Airplane(300);
    Flight flight(path, airplane);

    //Pilots
    vector<Pilot*> pilots;
    Pilot *jack = new Pilot("Jack",123);
    Pilot *jenny = new Pilot("Jenny",10);
    pilots.push_back(jack);
    pilots.push_back(jenny);
    ASSERT(!flight.setPilots(pilots));

    jenny->promote();
    ASSERT(flight.setPilots(pilots));

    ASSERT(flight.getAvailableSeats() == 297);

    return TR_PASS;
}

TestResult testFlightAddFlightAttendants() {
	///////////////////////////////////////
	//short flight tests:  Incorrect Team//
    ///////////////////////////////////////
	//setup flight team
		vector<FlightAttendant*> flightAttendants;
		FlightAttendant *anna = new FlightAttendant("Anna", 999);
		FlightAttendant *banna = new FlightAttendant("Banna", 998);
		FlightAttendant *canna = new FlightAttendant("Canna", 997);
		anna->addLanguage(Country::ENGLISH);
		banna->addLanguage(Country::ENGLISH);
		canna->addLanguage(Country::ENGLISH);
		flightAttendants.push_back(anna);
		flightAttendants.push_back(banna);
		flightAttendants.push_back(canna);

		//setup country
	    Country *source = new Country("London", Country::ENGLISH);
	    Country *destination = new Country("Madrid", Country::SPANISH);

	    //short route
	    Route *path = new Route(source, destination, 3);
	    Airplane *airplane = new Airplane(300);
	    Flight flight(path, airplane);

		ASSERT(!flight.setFlightAttendants(flightAttendants));


	////////////////////////////////////
	//short flight tests: Correct Team//
	////////////////////////////////////

    //add the required extra language to Anna
    banna->addLanguage(Country::SPANISH);

    //this one should work
	ASSERT(flight.setFlightAttendants(flightAttendants));

	banna->removeLanguage(Country::SPANISH);
	//this one should no longer work
	ASSERT(!flight.setFlightAttendants(flightAttendants));
/////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////
	//long flight tests: Incorrect Team//
	/////////////////////////////////////

    //long route (fly in circles)
    Route *path2 = new Route(source, destination, 12);
    Flight flight2(path2, airplane);

    //extra attendants
	FlightAttendant *danna = new FlightAttendant("Danna", 996);
	FlightAttendant *eanna = new FlightAttendant("Eanna", 995);
	FlightAttendant *fanna = new FlightAttendant("Fanna", 994);

	//Add languages to the extra attendants
	danna->addLanguage(Country::ENGLISH);
	eanna->addLanguage(Country::ARABIC);
	fanna->addLanguage(Country::SPANISH);
	banna->addLanguage(Country::SPANISH);

	flightAttendants.push_back(danna);
	flightAttendants.push_back(eanna);
	flightAttendants.push_back(fanna);

	ASSERT(!flight2.setFlightAttendants(flightAttendants))

	///////////////////////////////////
	//long flight tests: Correct Team//
	///////////////////////////////////

	//add the required language to eanna
	eanna->addLanguage(Country::ENGLISH);

	ASSERT(flight2.setFlightAttendants(flightAttendants))

	//delete all objects created on the heap
	delete anna;
	delete banna;
	delete canna;
	delete danna;
	delete eanna;
	delete fanna;
	delete path;
	delete path2;
	delete source;
	delete destination;
	delete airplane;

	return TR_PASS;
}

#endif /*ENABLE_T3_TESTS*/

#ifdef ENABLE_T4_TESTS

/*
 * Check adding customers to the Flight Management System
 */
TestResult testAddCustomer() {
    FlightManagementSystem fms;

    Customer *ben = new Customer("Ben", "K43681");
    vector<Customer *> customers = fms.getCustomers();
    ASSERT(customers.size() == 0)

    ASSERT(fms.addCustomer(ben));
    customers = fms.getCustomers();
    ASSERT(customers.size() == 1)

    Customer *luke = new Customer("Luke", "M20231");
    ASSERT(fms.addCustomer(luke));
    customers = fms.getCustomers();
    ASSERT(customers.size() == 2)

    // Customer with a different name, but same passport number -- shouldn't be added
    Customer *ben2 = new Customer("Not Ben Again", "K43681");
    ASSERT(!fms.addCustomer(ben2));

    return TR_PASS;
}

/*
 * Check adding flight to the FMS
 */
TestResult testAddFlight() {
    FlightManagementSystem fms;

    Country *source = new Country("Miami", Country::ENGLISH);
    Country *destination = new Country("Lima", Country::SPANISH);
    Route *path = new Route(source, destination, 7);
    Airplane *airplane = new Airplane(300);
    Flight *flight = new Flight(path, airplane);

    Date *time = new Date(3, 2);
    fms.addFlight(flight, time);

    vector <Flight *> flights;
    flights = fms.getFlights();

    ASSERT(flights.size() == 1);

    return TR_PASS;
}

/*
 * Check booking of tickets
 */
TestResult testBookTicket() {
    FlightManagementSystem fms;

    Country *miami = new Country("Miami", Country::ENGLISH);
    Country *lima = new Country("Lima", Country::SPANISH);
    Route *pathMtoL = new Route(miami, lima, 7);
    Airplane *airplaneMtoL = new Airplane(300);
    Flight *flightMtoL  = new Flight(pathMtoL, airplaneMtoL);
    Date *timeMtoL = new Date(3, 2);
    fms.addFlight(flightMtoL, timeMtoL);

    Country *dubai = new Country("Dubai", Country::ARABIC);
    Country *auckland = new Country("Auckland", Country::ENGLISH);
    Route *pathDtoA = new Route(dubai, auckland, 15);
    Airplane *airplaneDtoA = new Airplane(500);
    Flight *flightToDtoA = new Flight(pathDtoA, airplaneDtoA);
    Date *timeDtoA = new Date(3, 2);
    fms.addFlight(flightToDtoA, timeDtoA);

    Customer *ben = new Customer("Ben", "ABC436");
    fms.addCustomer(ben);
    Customer *lucy = new Customer("Lucy", "PW23091");
    fms.addCustomer(lucy);

    ASSERT(fms.bookTicket(pathDtoA, timeDtoA, "ABC436", 20));
    ASSERT(fms.getCapacity(pathDtoA, timeDtoA) == 472);
    ASSERT(fms.getCustomerPoints("ABC436") == 300);

    return TR_PASS;
}

TestResult T4Tests() {
	//cases to test:
	//cannot add customer if already in system addCustomer
	//test getCustomers
	//test bookticket for customer that doesn't exist with bookTicket
	//loyalty points lookup on nonexistant customer with getCustomerPoints
	//look for nonexistant flight with getCapacity
	//try to book tickets when there is 0 capacity on flight

	//from previous tests
	FlightManagementSystem fms;
    Country *miami = new Country("Miami", Country::ENGLISH);
    Country *lima = new Country("Lima", Country::SPANISH);
    Route *pathMtoL = new Route(miami, lima, 7);
    Airplane *airplaneMtoL = new Airplane(300);
    Flight *flightMtoL  = new Flight(pathMtoL, airplaneMtoL);
    Date *timeMtoL = new Date(3, 2);
    fms.addFlight(flightMtoL, timeMtoL);

    Country *dubai = new Country("Dubai", Country::ARABIC);
    Country *auckland = new Country("Auckland", Country::ENGLISH);
    Route *pathDtoA = new Route(dubai, auckland, 15);
    Airplane *airplaneDtoA = new Airplane(500);
    Flight *flightToDtoA = new Flight(pathDtoA, airplaneDtoA);
    //you wouldn't believe how long I spent debugging the fact that the timeDtoA and timeMtoL had
    //the same value, and therefore getCapacity would actually work
    Date *timeDtoA = new Date(4, 2);
    fms.addFlight(flightToDtoA, timeDtoA);

    Customer *ben = new Customer("Ben", "ABC436");
    fms.addCustomer(ben);
    Customer *lucy = new Customer("Lucy", "PW23091");
    fms.addCustomer(lucy);

    //trying to add existing customer
	Customer *ben10 = new Customer("ben 10", "ABC436")
	ASSERT(!fms.addCustomer(ben10));
	//customers returns customers
	vector <Customer* > customers;
	customers.push_back(ben);
	customers.push_back(lucy);
	ASSERT(fms.getCustomers() == customers);

	//book ticket for person who doesn't exist
	ASSERT(!fms.bookTicket(pathDtoA, timeDtoA,"ELBARTO",20));

	ASSERT(!fms.bookTicket(pathDtoA, timeDtoA, "ABC436", 493));
	ASSERT(fms.bookTicket(pathDtoA, timeDtoA, "ABC436", 492));
	//lookup nonexistant customer points
	ASSERT((fms.getCustomerPoints("ABC43...7??? oh my god an imposter"))==-1);

	//look for nonexistant flight with getCapacity
	ASSERT((fms.getCapacity(pathMtoL,timeDtoA))==-1);

	delete miami;
	delete lima;
	delete pathMtoL;
	delete airplaneMtoL;
	delete flightMtoL;
	delete timeMtoL;
	delete dubai;
	delete auckland;
	delete pathDtoA;
	delete flightToDtoA;
	delete timeDtoA;
	delete ben;
	delete lucy;
	delete ben10;

	return TR_PASS;
}

#endif /*ENABLE_T4_TESTS*/

/*
This function collects up all the tests as a vector of function pointers. If you create your own
tests and want to be able to run them, make sure you add them to the `tests` vector here.
*/

vector<TestResult (*)()> generateTests() {
    vector<TestResult (*)()> tests;
    tests.push_back(&testUsername);
    tests.push_back(&testCountry);
    tests.push_back(&testTime1);
    tests.push_back(&testTime2);
    tests.push_back(&testAirplane);
    tests.push_back(&dateRigorous);

#ifdef ENABLE_T2_TESTS
    tests.push_back(&testCustomer);
    tests.push_back(&testFlightAttendant);
    tests.push_back(&testPilot);
#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS
    tests.push_back(&testRoute);
    tests.push_back(&testFlightConstructor);
    tests.push_back(&testFlightAddPilots);
    tests.push_back(&testFlightAddFlightAttendants);
#endif /*ENABLE_T3_TESTS*/

#ifdef ENABLE_T4_TESTS
    tests.push_back(&testAddCustomer);
    tests.push_back(&testAddFlight);
    tests.push_back(&testBookTicket);
    tests.push_back(&T4Tests);
#endif /*ENABLE_T4_TESTS*/

    return tests;
}

int main(int argc, char const* argv[]) {
    // If one or more test numbers are passed as command-line parameters, execute them
    vector<TestResult (*)()> tests_to_run = generateTests();
    unsigned int pass_count = 0;
    unsigned int fail_count = 0;
    unsigned int run_count = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            unsigned int test_num = atoi(argv[i]);
            if (test_num > tests_to_run.size()) {
                cout << "ERROR: unknown test case " << test_num << endl;
                continue;
            }
            // run the test
            ++run_count;
            TestResult result = tests_to_run[test_num]();
            if (result == TR_FAIL) {
                cout << "FAIL: Test " << test_num << " failed." << endl;
                ++fail_count;
            } else {
                cout << "PASS: Test " << test_num << " passed." << endl;
                ++pass_count;
            }
        }
    } else {
        // otherwise, run all tests
        // Make sure to update this section as you add more tests
        // Add the tests for the first task
        for (unsigned int t = 0; t < tests_to_run.size(); ++t) {
            ++run_count;
            TestResult result = tests_to_run[t]();
            if (result == TR_FAIL) {
                cout << "FAIL: Test " << t << " failed." << endl;
                ++fail_count;
            } else {
                cout << "PASS: Test " << t << " passed." << endl;
                ++pass_count;
            }
        }
    }
    cout << "\n-------------------------------------------------\n"
         << "Total Run: " << run_count << "\n"
         << "Total PASSED: " << pass_count << "\n"
         << "Total FAILED: " << fail_count << "\n"
         << "-------------------------------------------------\n" << endl;

    // Return 0 if everything was ok
    return 0;
}
