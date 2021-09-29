#include "ExpressLane.hpp"
#include <iostream>
using namespace std;
// TODO: Write your implementation for the ExpressLane class here

    //there is a simple lane inherent to this class, as it inherits from SimpleLane
    ExpressLane::ExpressLane(){}

    //when the express lane destructor is called, it also calls the SimpleLane destructor to handle
    //the inherited objects from simplelane
    ExpressLane::~ExpressLane(){}

    //NOTE I had to override all my functions due to the extra motorbikes lane

    //Enqueues a vehicle
    void ExpressLane::enqueue(Vehicle* vehicle){
        //if its a motorcycle, it goes to the motorcycle lane
        if (vehicle->type() == Vehicle::VT_MOTORCYCLE) {
            motorbikes.enqueue(vehicle);
        } else {
            //otherwise, its regularly enqueued
            this->SimpleLane::enqueue(vehicle);
        }
    }

    //added for debugging purposes
    void ExpressLane::print() const {
        motorbikes.print();
        this->SimpleLane::print();
    }

    //dequeues the front of the queue
    Vehicle* ExpressLane::dequeue(){
        //if the motorcycles lane is empty, regularly dequeues
        if (motorbikes.empty()) {
            return this->SimpleLane::dequeue();
        //otherwise, dequeues from the motorcycles lane
        } else {
            return motorbikes.dequeue();
        }
        //if both lanes are empty, simplelane dequeue returns the corresponding empty lane values
    }

    //checks that both motorbikes and this lane are empty
    bool ExpressLane::empty() const{
        return ((motorbikes.empty())&&(this->SimpleLane::empty()));
    }

    //returns the sum of this lane and the motorbikes lane
    unsigned int ExpressLane::count() const{
        return (motorbikes.count() + this->SimpleLane::count());
    }

    //returns a pointer to the vehicle at the front of the queue
    const Vehicle* ExpressLane::front() const{
        //if no motorbikes are enqueued, returns the front of this lane
        if (motorbikes.empty()) {
            return this->SimpleLane::front();
        //else returns the front of the motorbikes lane
        } else {
            return motorbikes.front();
        }
    }
    
    //returns a pointer to a vehicle at the back of the queue
    const Vehicle* ExpressLane::back() const{
        //if theres nothing enqueued in the this lane, return the back of motorbikes
        if (this->SimpleLane::empty()) {
            return motorbikes.back();
        //else return this back
        } else {
            return this->SimpleLane::back();
        }
    }