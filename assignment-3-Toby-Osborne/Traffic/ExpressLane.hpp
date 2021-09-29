#ifndef EXPRESSLANE_HPP
#define EXPRESSLANE_HPP

#include "SimpleLane.hpp"

/*
The ExpressLane class simulates a single lane of a road. It is a FIFO queue for Vehicle objects.

ExpressLane implements the same behavior as SimpleLane, except when a Vehicle of type VT_MOTORCYCLE is enqueued, that
Vehicle is inserted ahead of all Vehicles of type VT_CAR and VT_BUS, but behind other motorcycles that have already been
enqueued.
*/
class ExpressLane : public SimpleLane {
private:
    //this class uses a seperate simple lane for motorbikes, that is "in front" of the regular queue
    SimpleLane motorbikes;
public:
/*
    Create a new empty traffic lane. Remember to initialize member variables where necessary.
    */

    //all important variables are initialized in the SimpleLane constructor
    ExpressLane();

    //destroys everything
    virtual ~ExpressLane();

    //enqueues a vehicle.  If it is a motorbike, it jumps the queue
    virtual void enqueue(Vehicle* vehicle);

    //dequeues the current front
    virtual Vehicle* dequeue();

    //checks if this lane is empty
    virtual bool empty() const;

    //prints the contents of the lane (for debugging purposes)
    virtual void print() const;

    //returns the number of vehicles in this lane
    virtual unsigned int count() const;

    //returns a pointer to a constant vehicle that is at the front
    //of the queue (least recently in)
    virtual const Vehicle* front() const;

    //returns a pointer to a constant vehicle that is at the back 
    //of the queue (most recently in)
    virtual const Vehicle* back() const;
};

#endif /* end of include guard: EXPRESSLANE_HPP */
