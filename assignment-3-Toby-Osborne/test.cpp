#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>

// flags to enable tests for the later parts of the assignment
#define ENABLE_VEHICLE_TESTS
#define ENABLE_T1_TESTS
#define ENABLE_T2_TESTS
#define ENABLE_CUSTOM_TESTS

// include headers for classes being tested
#include "Traffic/Vehicle.hpp"
#ifdef ENABLE_T1_TESTS
#include "Traffic/Lane.hpp"
#include "Traffic/SimpleLane.hpp"
#include "Traffic/ExpressLane.hpp"
#endif /*ENABLE_T1_TESTS*/
#ifdef ENABLE_T2_TESTS
#include "Traffic/Lane.hpp"
#include "Traffic/SimpleLane.hpp"
#include "Traffic/ExpressLane.hpp"
#include "Traffic/Intersection.hpp"
#endif /*ENABLE_T2_TESTS*/

using namespace std;

// This sigma value is the acceptable range of error for floating point (double) calculations
//const double SIGMA = 0.001; // LH commented
#define SIGMA 0.001

/*
The outcome of each test case is described by this enum, which should make the result more obvious
than if a boolean value was used in its place.
*/
enum TestResult { TR_PASS, TR_FAIL };

/*
Helper macro to eliminate a lot of of code repetition. Macros aren't the best, but this is an easy
way to get what we want.
*/

#define ASSERT(condition)                                                         \
    if ((condition) == false) {                                                   \
        cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                \
             << "\tExpression '" << #condition << "' evaluated to false" << endl; \
        return TR_FAIL;                                                           \
    }

#define ASSERT_EQUALS(actual, expected)                                               \
    if (actual != expected) {                                                         \
        cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                    \
             << "\tExpected '" << expected << "' but was '" << actual << "'" << endl; \
        return TR_FAIL;                                                               \
    }   

#define ASSERT_EQUALS_APPROX(actual, expected)                                        \
    if (fabs(actual - expected) > 0.001) {                                            \
        cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                    \
             << "\tExpected '" << expected << "' but was '" << actual << "'" << endl; \
        return TR_FAIL;                                                               \
    }   

/*
Helper macro to simplify the checking of double values against expected results. Directly comparing
values would result in brittle tests, so we have to instead check if the value we got is acceptably
close to the expected value.
*/
#define EXPECT_SIGMA(value, expected)                                                                            \
    {                                                                                                            \
        double value_eval = value;                                                                               \
        double expected_eval = expected;                                                                         \
        if (value_eval <= (expected_eval - SIGMA) || value_eval > (expected_eval + SIGMA)) {                     \
            cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                                           \
                 << "\tFloating-point value " << value_eval << " differed from expected value " << expected_eval \
                 << " by more than " << SIGMA << endl;                                                           \
            return TR_FAIL;                                                                                      \
        }                                                                                                        \
    }

#ifdef ENABLE_CUSTOM_TESTS
TestResult test_SimpleLane() {
    Vehicle *v1 = new Vehicle(Vehicle::VT_CAR,5);
    Vehicle *v2 = new Vehicle(Vehicle::VT_CAR,5);
    Vehicle *v3 = new Vehicle(Vehicle::VT_CAR,5);
    Vehicle *v4 = new Vehicle(Vehicle::VT_CAR,5);
    Vehicle *m1 = new Vehicle(Vehicle::VT_MOTORCYCLE,2);
    Vehicle *m2 = new Vehicle(Vehicle::VT_MOTORCYCLE,2);

    SimpleLane lane;

    lane.enqueue(v1);
    ASSERT_EQUALS(!lane.empty(),true);
    ASSERT_EQUALS(lane.front(),v1);
    ASSERT_EQUALS(lane.back(),v1);
    ASSERT_EQUALS(lane.count(),1);
    ASSERT_EQUALS(lane.dequeue(),v1)

    ASSERT(lane.empty());
    ASSERT_EQUALS(lane.front(),0);
    ASSERT_EQUALS(lane.back(),0);
    ASSERT_EQUALS(lane.count(),0);
    ASSERT_EQUALS(lane.dequeue(),0)

    lane.enqueue(v1);
    lane.enqueue(v2);
    lane.enqueue(v3);
    lane.enqueue(v4);

    ASSERT(!lane.empty());


    lane.enqueue(m1);
    lane.enqueue(m2);

    ASSERT_EQUALS(lane.count(),6);
    ASSERT_EQUALS(lane.front(),v1);
    ASSERT_EQUALS(lane.back(),m2);

    ASSERT_EQUALS(lane.dequeue(),v1);
    ASSERT_EQUALS(lane.count(),5);
    ASSERT_EQUALS(lane.front(),v2);
    ASSERT_EQUALS(lane.back(),m2);

    lane.enqueue(v1);

    ASSERT_EQUALS(lane.dequeue(),v2);
    ASSERT_EQUALS(lane.count(),5);
    ASSERT_EQUALS(lane.front(),v3);
    ASSERT_EQUALS(lane.back(),v1);

    ASSERT_EQUALS(lane.dequeue(),v3);
    ASSERT_EQUALS(lane.count(),4);
    ASSERT_EQUALS(lane.front(),v4);
    ASSERT_EQUALS(lane.back(),v1);

    ASSERT_EQUALS(lane.dequeue(),v4);
    ASSERT_EQUALS(lane.count(),3);
    ASSERT_EQUALS(lane.front(),m1);
    ASSERT_EQUALS(lane.back(),v1);

    ASSERT_EQUALS(lane.dequeue(),m1);
    ASSERT_EQUALS(lane.count(),2);
    ASSERT_EQUALS(lane.front(),m2);
    ASSERT_EQUALS(lane.back(),v1);

    ASSERT_EQUALS(lane.dequeue(),m2);
    ASSERT_EQUALS(lane.count(),1);
    ASSERT_EQUALS(lane.front(),v1);
    ASSERT_EQUALS(lane.back(),v1);
    ASSERT_EQUALS(lane.dequeue(),v1);


    ASSERT_EQUALS(lane.front(), 0);
    ASSERT_EQUALS(lane.back(), 0);
    ASSERT_EQUALS(lane.dequeue(), 0);
    ASSERT_EQUALS(lane.empty(), true);
    ASSERT_EQUALS(lane.count(), 0);

    lane.enqueue(m2);
    lane.enqueue(m1);
    lane.enqueue(v4);
    lane.enqueue(v3);
    lane.enqueue(v2);
    lane.enqueue(v1);

    ASSERT_EQUALS(lane.count(),6);
    ASSERT_EQUALS(lane.front(),m2);
    ASSERT_EQUALS(lane.back(),v1);

    // :(((((((((((((((((((
    //lane.print();

    return TR_PASS;
}

TestResult test_ExpressLane() {
    Vehicle *v1 = new Vehicle(Vehicle::VT_CAR,5);
    Vehicle *v2 = new Vehicle(Vehicle::VT_CAR,5);
    Vehicle *v3 = new Vehicle(Vehicle::VT_CAR,5);
    Vehicle *v4 = new Vehicle(Vehicle::VT_CAR,5);
    Vehicle *m1 = new Vehicle(Vehicle::VT_MOTORCYCLE,2);
    Vehicle *m2 = new Vehicle(Vehicle::VT_MOTORCYCLE,2);

    ExpressLane lane;

    lane.enqueue(v1);
    ASSERT_EQUALS(!lane.empty(),true);
    ASSERT_EQUALS(lane.front(),v1);
    ASSERT_EQUALS(lane.back(),v1);
    ASSERT_EQUALS(lane.count(),1);
    ASSERT_EQUALS(lane.dequeue(),v1)

    lane.enqueue(v1);
    lane.enqueue(v2);
    lane.enqueue(m1);
    lane.enqueue(v3);
    lane.enqueue(v4);
    lane.enqueue(m2);

    ASSERT_EQUALS(lane.count(),6);
    ASSERT_EQUALS(lane.front(),m1);
    ASSERT_EQUALS(lane.back(),v4);

    ASSERT_EQUALS(lane.dequeue(),m1);
    ASSERT_EQUALS(lane.count(),5);
    ASSERT_EQUALS(lane.front(),m2);
    ASSERT_EQUALS(lane.back(),v4);

    ASSERT_EQUALS(lane.dequeue(),m2);
    ASSERT_EQUALS(lane.count(),4);
    ASSERT_EQUALS(lane.front(),v1);
    ASSERT_EQUALS(lane.back(),v4);

    ASSERT_EQUALS(lane.dequeue(),v1);
    ASSERT_EQUALS(lane.count(),3);
    ASSERT_EQUALS(lane.front(),v2);
    ASSERT_EQUALS(lane.back(),v4);

    ASSERT_EQUALS(lane.dequeue(),v2);
    ASSERT_EQUALS(lane.count(),2);
    ASSERT_EQUALS(lane.front(),v3);
    ASSERT_EQUALS(lane.back(),v4);

    ASSERT_EQUALS(lane.dequeue(),v3);
    ASSERT_EQUALS(lane.count(),1);
    ASSERT_EQUALS(lane.front(),v4);
    ASSERT_EQUALS(lane.back(),v4);

    ASSERT_EQUALS(lane.dequeue(),v4);

    ASSERT_EQUALS(lane.front(), 0);
    ASSERT_EQUALS(lane.back(), 0);
    ASSERT_EQUALS(lane.dequeue(), 0);
    ASSERT_EQUALS(lane.empty(), true);
    ASSERT_EQUALS(lane.count(), 0);

    lane.enqueue(v1);
    lane.enqueue(v2);
    lane.enqueue(v3);
    lane.enqueue(v4);
    lane.enqueue(m1);
    lane.enqueue(m2);

    ASSERT_EQUALS(lane.count(),6);
    ASSERT_EQUALS(lane.front(),m1);
    ASSERT_EQUALS(lane.back(),v4);

    //lane.print();

    return TR_PASS;
}

TestResult test_Intersection_Rigorous() {
    //Test 1 incoming lane
    Lane *laneEast = new SimpleLane();
    Lane *laneNorth = new SimpleLane();
    Lane *laneWest = new SimpleLane();
    Lane *laneSouth = new SimpleLane();

    Vehicle *v1 = new Vehicle(Vehicle::VT_BUS,30);
    Vehicle *v2 = new Vehicle(Vehicle::VT_MOTORCYCLE,2);
    Vehicle *v3 = new Vehicle(Vehicle::VT_CAR,4);

    v1->turnStraight();
    v2->turnLeft();
    v3->turnRight();

    laneWest->enqueue(v1);
    laneWest->enqueue(v2);
    laneWest->enqueue(v3);

    Intersection pamure;
    pamure.connectEast(laneEast,Intersection::LD_OUTGOING);
    ASSERT(!pamure.valid());
    pamure.connectWest(laneWest,Intersection::LD_INCOMING);
    ASSERT(!pamure.valid());
    pamure.connectNorth(laneNorth,Intersection::LD_OUTGOING);
    ASSERT(!pamure.valid());
    pamure.connectSouth(laneSouth,Intersection::LD_OUTGOING);
    ASSERT(pamure.valid());

    pamure.simulate();

    ASSERT_EQUALS(laneEast->front(),v1);
    ASSERT(laneNorth->empty());
    ASSERT(laneSouth->empty());

    pamure.simulate();

    ASSERT_EQUALS(laneEast->front(),v1);
    ASSERT_EQUALS(laneNorth->front(),v2);
    ASSERT(laneSouth->empty());

    pamure.simulate();

    ASSERT_EQUALS(laneEast->front(),v1);
    ASSERT_EQUALS(laneNorth->front(),v2);
    ASSERT_EQUALS(laneSouth->front(),v3);

    ASSERT_EQUALS(laneNorth->dequeue(),v2);
    ASSERT_EQUALS(laneEast->dequeue(),v1);
    ASSERT_EQUALS(laneSouth->dequeue(),v3);


    //simulate 2 incoming lanes : various
    pamure.connectEast(laneEast,Intersection::LD_INCOMING);

    Vehicle *v4 = new Vehicle(Vehicle::VT_BUS,29);
    v1->turnLeft();
    v3->turnLeft();
    v2->turnLeft();
    v4->turnRight();

    //proof this doesn't crash the code lol
    pamure.simulate();

    laneWest->enqueue(v1);
    laneWest->enqueue(v2);
    laneEast->enqueue(v3);
    laneEast->enqueue(v4);

    //is the lane empty?
    ASSERT(!laneEast->empty());

    ASSERT_EQUALS(laneWest->front(),v1);
    ASSERT_EQUALS(laneEast->front(),v3);

    ASSERT_EQUALS(laneWest->front()->nextTurn(),Vehicle::TD_LEFT);
    ASSERT_EQUALS(laneEast->front()->nextTurn(),Vehicle::TD_LEFT);

    pamure.simulate();

    ASSERT_EQUALS(laneSouth->back(),v3);
    ASSERT_EQUALS(laneNorth->back(),v1);

    pamure.simulate();

    ASSERT_EQUALS(laneNorth->back(),v2);
    ASSERT_EQUALS(laneSouth->back(),v3);

    pamure.simulate();

    ASSERT_EQUALS(laneNorth->back(),v4);
    ASSERT_EQUALS(laneSouth->back(),v3);

    laneNorth->dequeue();
    laneNorth->dequeue();
    laneNorth->dequeue();
    laneSouth->dequeue();

    ASSERT(laneNorth->empty());
    ASSERT(laneSouth->empty());
    ASSERT(laneEast->empty());
    ASSERT(laneWest->empty());

    laneEast->enqueue(v1);
    laneSouth->enqueue(v2);
    pamure.connectWest(laneWest,Intersection::LD_OUTGOING);
    pamure.connectSouth(laneSouth,Intersection::LD_INCOMING);
    
    v2->turnLeft();
    v1->turnRight();

    pamure.simulate();

    //only car turning left should have moved
    ASSERT_EQUALS(laneWest->back(),v2);
    ASSERT(laneNorth->empty());
    ASSERT(laneSouth->empty());
    ASSERT_EQUALS(laneEast->front(),v1);

    pamure.simulate();

    //only car turning right should have moved
    ASSERT_EQUALS(laneWest->dequeue(),v2);
    ASSERT(laneEast->empty());
    ASSERT(laneSouth->empty());
    ASSERT_EQUALS(laneNorth->dequeue(),v1);

    

    //testing expresslane
    pamure.connectWest(laneWest,Intersection::LD_INCOMING);


    

    //quick check that expresslanes work with this
    Intersection glendale;

    ExpressLane *elaneEast = new ExpressLane();
    ExpressLane *elaneNorth = new ExpressLane();
    ExpressLane *elaneWest = new ExpressLane();
    ExpressLane *elaneSouth = new ExpressLane();

    glendale.connectEast(elaneEast,Intersection::LD_INCOMING);
    glendale.connectNorth(elaneNorth,Intersection::LD_OUTGOING);
    glendale.connectWest(elaneWest,Intersection::LD_INCOMING);
    glendale.connectSouth(elaneSouth,Intersection::LD_OUTGOING);

    elaneWest->enqueue(v1);
    elaneWest->enqueue(v2);
    //v2 is a motorbike
    ASSERT_EQUALS(elaneWest->front(),v2);

    elaneEast->enqueue(v3);
    elaneEast->enqueue(v4);

    v2->turnLeft();
    v3->turnLeft();
    v1->turnRight();
    v4->turnLeft();

    glendale.simulate();
    //v2 should have gone first, since its a motorbike, and turned left
    ASSERT_EQUALS(elaneNorth->front(),v2);
    ASSERT_EQUALS(elaneSouth->front(),v3);

    glendale.simulate();
    //left turning v4 should have been given way to by right turning v1
    ASSERT_EQUALS(elaneSouth->back(),v4);
    ASSERT_EQUALS(elaneWest->front(),v1);
    glendale.simulate();
    //now v1 should be in the south lane back
    ASSERT_EQUALS(elaneSouth->back(),v1);
    ASSERT_EQUALS(elaneSouth->count(),3);
    ASSERT_EQUALS(elaneNorth->count(),1);

    delete laneWest;
    delete laneEast;
    delete laneSouth;
    delete laneNorth;
    //vehicles are still inside the elanes
    delete elaneWest;
    delete elaneEast;
    delete elaneSouth;
    delete elaneNorth;

    return TR_PASS;
}

#endif

#ifdef ENABLE_VEHICLE_TESTS
/*
Test setting the vehicle type and number of occupants in the Vehicle constructor
*/
TestResult test_VehicleConstruction() {
    {
        Vehicle c(Vehicle::VT_CAR, 2);
        ASSERT_EQUALS(c.type(), Vehicle::VT_CAR);
        ASSERT_EQUALS(c.occupantCount(), 2);
    }

    {
        Vehicle b(Vehicle::VT_BUS, 14);
        ASSERT_EQUALS(b.type(), Vehicle::VT_BUS);
        ASSERT_EQUALS(b.occupantCount(), 14);
    }

    {
        Vehicle b(Vehicle::VT_MOTORCYCLE, 1);
        ASSERT_EQUALS(b.type(), Vehicle::VT_MOTORCYCLE);
        ASSERT_EQUALS(b.occupantCount(), 1);
    }

    return TR_PASS;
}

/*
Test the turn direction functionality of the Vehicle class.
*/
TestResult test_VehicleTurning() {
    Vehicle c(Vehicle::VT_CAR, 2);
    // Test car with empty turn queue
    ASSERT_EQUALS(c.nextTurn(), Vehicle::TD_INVALID);
    ASSERT_EQUALS(c.makeTurn(), Vehicle::TD_INVALID);

    // Queue some turns and go through them
    c.turnLeft();
    c.turnRight();
    c.turnStraight();

    ASSERT_EQUALS(c.nextTurn(), Vehicle::TD_LEFT);
    ASSERT_EQUALS(c.makeTurn(), Vehicle::TD_LEFT);
    ASSERT_EQUALS(c.nextTurn(), Vehicle::TD_RIGHT);
    ASSERT_EQUALS(c.makeTurn(), Vehicle::TD_RIGHT);
    ASSERT_EQUALS(c.nextTurn(), Vehicle::TD_STRAIGHT);
    ASSERT_EQUALS(c.makeTurn(), Vehicle::TD_STRAIGHT);

    // Test empty queue again, after turns executed
    ASSERT_EQUALS(c.nextTurn(), Vehicle::TD_INVALID);
    ASSERT_EQUALS(c.makeTurn(), Vehicle::TD_INVALID);

    return TR_PASS;
}
#endif /*ENABLE_VEHICLE_TESTS*/

#ifdef ENABLE_T1_TESTS
/*
Test Lane construction (and destruction).
*/
TestResult test_SimpleLaneConstruction() {
    // scope the instance to explicitly invoke the destructor before the return
    {
        SimpleLane lane;
        // prevent the compiler from optimizing out the instance
        (void)lane;
    }

    return TR_PASS;
}

/*
Test SimpleLane initial state.
*/
TestResult test_SimpleLaneInitialState() {
    SimpleLane lane;

    ASSERT_EQUALS(lane.front(), 0);
    ASSERT_EQUALS(lane.back(), 0);
    ASSERT_EQUALS(lane.dequeue(), 0);
    ASSERT_EQUALS(lane.empty(), true);
    ASSERT_EQUALS(lane.count(), 0);
    return TR_PASS;
}

/*
Test adding vehicles to the SimpleLane.
*/
TestResult test_SimpleLaneEnqueue() {
    SimpleLane lane;
    Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
    Vehicle* v2 = new Vehicle(Vehicle::VT_CAR, 2);
    Vehicle* v3 = new Vehicle(Vehicle::VT_BUS, 3);
    Vehicle* m1 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);

    lane.enqueue(v1);
    ASSERT(!lane.empty())
    ASSERT_EQUALS(lane.count(), 1)
    ASSERT_EQUALS(lane.back(), v1);
    ASSERT_EQUALS(lane.front(), v1);
    lane.enqueue(v2);
    ASSERT(!lane.empty())
    ASSERT_EQUALS(lane.count(), 2)
    ASSERT_EQUALS(lane.back(), v2);
    ASSERT_EQUALS(lane.front(), v1);
    lane.enqueue(v3);
    ASSERT(!lane.empty())
    ASSERT_EQUALS(lane.count(), 3)
    ASSERT_EQUALS(lane.back(), v3);
    ASSERT_EQUALS(lane.front(), v1);
    lane.enqueue(m1);
    ASSERT(!lane.empty())
    ASSERT_EQUALS(lane.count(), 4)
    ASSERT_EQUALS(lane.back(), m1);
    ASSERT_EQUALS(lane.front(), v1);

    // vehicles should be deleted by the lane

    return TR_PASS;
}

/*
Make sure ExpressLane exhibits the same initial state as SimpleLane
*/
TestResult test_ExpressLaneInitialState() {
    ExpressLane lane;

    ASSERT_EQUALS(lane.front(), 0);
    ASSERT_EQUALS(lane.back(), 0);
    ASSERT_EQUALS(lane.dequeue(), 0);
    ASSERT_EQUALS(lane.empty(), true);
    ASSERT_EQUALS(lane.count(), 0);

    Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
    Vehicle* v2 = new Vehicle(Vehicle::VT_CAR, 2);
    Vehicle* v3 = new Vehicle(Vehicle::VT_BUS, 3);
    Vehicle* m1 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);

    lane.enqueue(v1);
    lane.enqueue(v2);
    lane.enqueue(v3);
    lane.enqueue(m1);
    ASSERT_EQUALS(lane.front(),m1);
    ASSERT_EQUALS(lane.dequeue(),m1);

    return TR_PASS;
}
#endif /*ENABLE_T1_TESTS*/

#ifdef ENABLE_T2_TESTS
/*
Test Intersection construction and initial state.
*/
TestResult test_IntersectionConstruction() {
    Intersection* intersection = new Intersection();
    // check the intersection is initially invalid
    ASSERT(!intersection->valid());
    // invoke the destructor (if any)
    delete intersection;

    return TR_PASS;
}

/*
Test intersection Lane overwriting behavior; i.e. when a new Lane is assigned in
a position already occupied by another Lane connected to the Intersection.
*/
TestResult test_IntersectionOverwrite() {
    Intersection intersection;

    Lane* l1 = new SimpleLane();
    Lane* l2 = new SimpleLane();
    Lane* l3 = new SimpleLane();
    Lane* l4 = new SimpleLane();
    Lane* l5 = new SimpleLane();

    // connect first lanes
    ASSERT_EQUALS(intersection.connectNorth(l1, Intersection::LD_INCOMING), 0);
    ASSERT(!intersection.valid());
    ASSERT_EQUALS(intersection.connectEast(l2, Intersection::LD_OUTGOING), 0);
    ASSERT(!intersection.valid());
    ASSERT_EQUALS(intersection.connectSouth(l3, Intersection::LD_INCOMING), 0);
    ASSERT(!intersection.valid());
    ASSERT_EQUALS(intersection.connectWest(l4, Intersection::LD_OUTGOING), 0);
    ASSERT(intersection.valid());

    // assign a new lane for each direction
    ASSERT_EQUALS(intersection.connectNorth(l5, Intersection::LD_INCOMING), l1);
    ASSERT(intersection.valid());
    ASSERT_EQUALS(intersection.connectEast(l5, Intersection::LD_OUTGOING), l2);
    ASSERT(intersection.valid());
    ASSERT_EQUALS(intersection.connectSouth(l5, Intersection::LD_INCOMING), l3);
    ASSERT(intersection.valid());
    ASSERT_EQUALS(intersection.connectWest(l5, Intersection::LD_OUTGOING), l4);
    ASSERT(intersection.valid());

    // de-assign all lanes
    // LH: changed these 4 valid() to !valid(), otherwise I don't get it...
    // question for Nasser, perhaps
    ASSERT_EQUALS(intersection.connectNorth(0, Intersection::LD_INCOMING), l5);
    ASSERT(!intersection.valid());
    ASSERT_EQUALS(intersection.connectEast(0, Intersection::LD_OUTGOING), l5);
    ASSERT(!intersection.valid());
    ASSERT_EQUALS(intersection.connectSouth(0, Intersection::LD_INCOMING), l5);
    ASSERT(!intersection.valid());
    ASSERT_EQUALS(intersection.connectWest(0, Intersection::LD_OUTGOING), l5);
    ASSERT(!intersection.valid());

    delete l1;
    delete l2;
    delete l3;
    delete l4;
    delete l5;

    return TR_PASS;
}

/*
Test an intersection with four Lanes attached, one incoming and three outgoing. This should be the simplest intersection
it is possible to create; no give way rules have to be applied. Only tested using the SimpleLane class, so motorcycle
filtering behavior shouldn't affect this test.
*/
TestResult test_IntersectionOneIn() {
    Intersection intersection;

    // vehicles for testing

    Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
    v1->turnLeft();
    Vehicle* v2 = new Vehicle(Vehicle::VT_BUS, 10);
    v2->turnRight();
    Vehicle* v3 = new Vehicle(Vehicle::VT_CAR, 1);
    v3->turnStraight();
    Vehicle* v4 = new Vehicle(Vehicle::VT_MOTORCYCLE, 2);
    v4->turnLeft();
    v4->turnRight();

    // create the RoadWays
    Lane* roadIn = new SimpleLane();
    roadIn->enqueue(v1);
    roadIn->enqueue(v2);
    roadIn->enqueue(v3);
    roadIn->enqueue(v4);

    Lane* roadLeft = new SimpleLane();
    Lane* roadStraight = new SimpleLane();
    Lane* roadRight = new SimpleLane();
    
    // add RoadWays to the Intersection
    ASSERT_EQUALS(intersection.connectNorth(roadIn, Intersection::LD_INCOMING), 0); // entry
    ASSERT_EQUALS(intersection.connectEast(roadLeft, Intersection::LD_OUTGOING), 0); // exit left
    ASSERT_EQUALS(intersection.connectSouth(roadStraight, Intersection::LD_OUTGOING), 0); // exit straight
    ASSERT_EQUALS(intersection.connectWest(roadRight, Intersection::LD_OUTGOING), 0); // exit right
    // check intersection is valid
    ASSERT(intersection.valid());
    
    // simulate a single tick
    intersection.simulate();

    // check results (only one vehicle should proceed)
    ASSERT_EQUALS(roadIn->front(), v2);
    ASSERT_EQUALS(roadLeft->front(), v1);
    ASSERT(roadRight->empty());
    ASSERT(roadStraight->empty());
    // run the simulation for 3 more ticks to allow the other vehicles to proceed
    for (int i = 0; i < 3; ++i) {
        intersection.simulate();
    }
    // check all vehicles passed through the intersection successfully
    ASSERT_EQUALS(roadIn->front(), 0);
    ASSERT_EQUALS(roadLeft->dequeue(), v1);
    ASSERT_EQUALS(roadLeft->dequeue(), v4);
    
    ASSERT_EQUALS(roadLeft->front(), 0);
    ASSERT_EQUALS(roadStraight->dequeue(), v3);
    ASSERT_EQUALS(roadStraight->front(), 0);
    ASSERT_EQUALS(roadRight->dequeue(), v2);
    ASSERT_EQUALS(roadRight->front(), 0);
    
    delete roadIn;
    delete roadLeft;
    delete roadStraight;
    delete roadRight;

    delete v1;
    delete v2;
    delete v3;
    delete v4;

    return TR_PASS;
}

/*
Test an intersection with four Lanes attached, two incoming and two outgoing, arranged so that Lanes attached to the
intersection in the same direction (e.g. incoming) are directly opposite each other.
*/
TestResult test_IntersectionTwoInOpposing() {
    Intersection intersection;

    // vehicles for testing
    Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
    v1->turnLeft();
    Vehicle* v2 = new Vehicle(Vehicle::VT_BUS, 10);
    v2->turnRight();
    Vehicle* v3 = new Vehicle(Vehicle::VT_CAR, 1);
    v3->turnRight();
    Vehicle* v4 = new Vehicle(Vehicle::VT_MOTORCYCLE, 2);
    v4->turnLeft();
    v4->turnRight();
    Vehicle* v5 = new Vehicle(Vehicle::VT_CAR, 3);
    v5->turnRight();
    Vehicle* v6 = new Vehicle(Vehicle::VT_CAR, 2);
    v6->turnRight();
    v6->turnLeft();
    Vehicle* v7 = new Vehicle(Vehicle::VT_BUS, 8);
    v7->turnRight();
    Vehicle* v8 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);
    v8->turnLeft();

    // create the Lanes
    Lane* roadInNorth = new SimpleLane();
    roadInNorth->enqueue(v1);
    roadInNorth->enqueue(v2);
    roadInNorth->enqueue(v3);
    roadInNorth->enqueue(v4);

    Lane* roadInSouth = new SimpleLane();
    roadInSouth->enqueue(v5);
    roadInSouth->enqueue(v6);
    roadInSouth->enqueue(v7);
    roadInSouth->enqueue(v8);

    Lane* roadOutEast = new SimpleLane();
    Lane* roadOutWest = new SimpleLane();

    // add Lanes to the Intersection
    ASSERT_EQUALS(intersection.connectNorth(roadInNorth, Intersection::LD_INCOMING), 0); // entry
    ASSERT_EQUALS(intersection.connectEast(roadOutEast, Intersection::LD_OUTGOING), 0); // exit
    ASSERT_EQUALS(intersection.connectSouth(roadInSouth, Intersection::LD_INCOMING), 0); // entry
    ASSERT_EQUALS(intersection.connectWest(roadOutWest, Intersection::LD_OUTGOING), 0); // exit
    // check intersection is valid
    ASSERT(intersection.valid());

    // simulate a single tick
    intersection.simulate();
    // check results (exactly one vehicle should proceed)
    ASSERT_EQUALS(roadInNorth->front(), v2);
    ASSERT_EQUALS(roadOutEast->front(), v1);
    ASSERT_EQUALS(roadInSouth->front(), v5);
    ASSERT_EQUALS(roadOutWest->front(), 0);

    // run the simulation for 5 more ticks to allow the other vehicles to proceed (should be enough if road rules are
    // followed)
    for (int i = 0; i < 5; ++i) {
        intersection.simulate();
    }

    // check all vehicles passed through the intersection successfully
    // check inbound lanes
    ASSERT_EQUALS(roadInNorth->front(), 0);
    ASSERT_EQUALS(roadInSouth->front(), 0);
    // check eastbound out lane
    ASSERT_EQUALS(roadOutEast->dequeue(), v1);
    ASSERT_EQUALS(roadOutEast->dequeue(), v5);
    ASSERT_EQUALS(roadOutEast->dequeue(), v6);
    ASSERT_EQUALS(roadOutEast->dequeue(), v4);
    ASSERT_EQUALS(roadOutEast->dequeue(), v7);
    ASSERT_EQUALS(roadOutEast->dequeue(), 0);
    // check westbound out lane
    ASSERT_EQUALS(roadOutWest->dequeue(), v2);
    ASSERT_EQUALS(roadOutWest->dequeue(), v3);
    ASSERT_EQUALS(roadOutWest->dequeue(), v8);
    ASSERT_EQUALS(roadOutWest->dequeue(), 0);

    delete roadInNorth;
    delete roadOutEast;
    delete roadInSouth;
    delete roadOutWest;

    delete v1;
    delete v2;
    delete v3;
    delete v4;
    delete v5;
    delete v6;
    delete v7;
    delete v8;

    return TR_PASS;
}
#endif /*ENABLE_T2_TESTS*/

/*
This function collects up all the tests as a vector of function pointers. If you create your own
tests and want to be able to run them, make sure you add them to the `tests` vector here.
*/
vector<TestResult (*)()> generateTests() {
    vector<TestResult (*)()> tests;
#ifdef ENABLE_VEHICLE_TESTS
    tests.push_back(&test_VehicleConstruction);
    tests.push_back(&test_VehicleTurning);
#endif /*ENABLE_VEHICLE_TESTS*/
#ifdef ENABLE_T1_TESTS
    tests.push_back(&test_SimpleLaneConstruction);
    tests.push_back(&test_SimpleLaneInitialState);
    tests.push_back(&test_SimpleLaneEnqueue);
    tests.push_back(&test_ExpressLaneInitialState);
#endif /*ENABLE_T1_TESTS*/
#ifdef ENABLE_T2_TESTS
    tests.push_back(&test_IntersectionConstruction);
    tests.push_back(&test_IntersectionOverwrite);
    tests.push_back(&test_IntersectionOneIn);
    tests.push_back(&test_IntersectionTwoInOpposing);
#endif /*ENABLE_T2_TESTS*/
#ifdef ENABLE_CUSTOM_TESTS
    tests.push_back(&test_SimpleLane);
    tests.push_back(&test_ExpressLane);
    tests.push_back(&test_Intersection_Rigorous);
#endif

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
