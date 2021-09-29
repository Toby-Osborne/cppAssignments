#include "Intersection.hpp"
#include <iostream>
using namespace std;
// TODO: Write your implementation for the Intersection class here

Intersection::Intersection() {}

bool Intersection::valid() { 
    //this was useful for debugging, keeping here in case it comes back
    //cout << "Unassigned = " << getUnassigned() << endl;
    //cout << "Outgoing = "<<getOutGoing() << endl;
    //cout << "Incoming = "<<getIncoming() << endl;
    //if there is at least one unassigned lane, no outgoing lanes, or no incoming lanes, the intersection is not valid
    if ((getUnassigned() > 0)||(getOutGoing()==0)||(getIncoming()==0)) {
        return false;
    }
    return true;
 }

//gets outgoing lanes count
int Intersection::getOutGoing() {
    int outgoing = 0;
    for (int i = 0;i<4;i++) {
        if (directions[i]==LD_OUTGOING) {
            outgoing++;
        }
    }
    return outgoing;
}

//gets incoming lanes count
int Intersection::getIncoming() {
    int incoming = 0;
    for (int i = 0;i<4;i++) {
        if (directions[i]==LD_INCOMING) {
            incoming++;
        }
    }
    return incoming;
}

//gets the number of unassigned lanes
int Intersection::getUnassigned() {
    int unassigned = 0;
    for (int i = 0;i<4;i++) {
        if (lanes[i] == 0) {
            unassigned++;
        }
    }
    return unassigned;
}

//ENWS = 0,1,2,3
//allocates north lane to id 1, and sets corresponding direction
Lane* Intersection::connectNorth(Lane* lane, LaneDirection direction) { 
    Lane* prevLane = lanes[1];
    lanes[1] = lane;
    directions[1] = direction;
    return prevLane;
 }
//allocates east lane to id 0, and sets corresponding direction
Lane* Intersection::connectEast(Lane* lane, LaneDirection direction) {
    Lane* prevLane = lanes[0];
    lanes[0] = lane;
    directions[0] = direction;
    return prevLane;
}
//allocates south lane to id 3, and sets corresponding direction
Lane* Intersection::connectSouth(Lane* lane, LaneDirection direction) {
    Lane* prevLane = lanes[3];
    lanes[3] = lane;
    directions[3] = direction;
    return prevLane;
}
//allocates west lane to id 2, and sets corresponding direction
Lane* Intersection::connectWest(Lane* lane, LaneDirection direction) {
    Lane* prevLane = lanes[2];
    lanes[2] = lane;
    directions[2] = direction;
    return prevLane;
}

//I separated this into a seperate method
//I do not know why
void Intersection::moveVehicle(int laneid) {
    //
    Vehicle::TurnDirection direction = lanes[laneid]->front()->nextTurn();

    //cout << "turning a vehicle" << endl;

    //calculating what the next lane should be in a circular fashion
    int newid;
    if (direction == Vehicle::TD_RIGHT){
        newid = laneid+1;
    } 
    if (direction == Vehicle::TD_STRAIGHT){
        newid = laneid+2;
    }
    if (direction == Vehicle::TD_LEFT){
        newid = laneid+3;
    }
    //this is the circular part
    newid = newid%4;

    //dequeues the vehicle from the lane passed
    Vehicle *temp = lanes[laneid]->dequeue();    
    //makes the turn
    temp->makeTurn();
    //enqueues the vehicle in the new lane
    lanes[newid]->enqueue(temp);
}

//this function is described best in Intersection.hpp
void Intersection::simulate() {

    //new variable acts as a switch, so multiple cars turning same direction can go
    bool waygiven = false;

    //if the intersection is not valid, then it should not work
    if (!(this->valid())) {
        return;
    }

    //creates an array of turndirections on the stack to be used
    Vehicle::TurnDirection turndirections[4] = {Vehicle::TD_INVALID,Vehicle::TD_INVALID,Vehicle::TD_INVALID,Vehicle::TD_INVALID};
    //assigns those directions based on the front of each queue (lane)
    //the laneid of the turndirections array corresponds with ENWS = 0,1,2,3.  Everything is consistent.
    for (int i = 0;i<4;i++){
        if ((!lanes[i]->empty())&&(directions[i]==LD_INCOMING)) {
            turndirections[i] = lanes[i]->front()->nextTurn();
        }
    }  

    //make straight turns first.  Allows 2 cars going straight to crash, as intended.
    for (int i = 0;i<4;i++){
        if ((turndirections[i] == Vehicle::TD_STRAIGHT)) {
            waygiven = true;
            //moves the vehicle
            moveVehicle(i);
        }
    }

    //then left turns
    //if no cars went straight
    if (!waygiven) {
        for (int i = 0;i<4;i++){
            if (turndirections[i] == Vehicle::TD_LEFT) {
                waygiven = true;
                moveVehicle(i);
            }
        }
    }
    

    //then right
    //if no cars went straight or left
    if (!waygiven) {
        for (int i = 0;i<4;i++){
            if (turndirections[i] == Vehicle::TD_RIGHT) {
                moveVehicle(i);
            }
        }
    }
    //returns after attempting to move all the vehicles.
    return;
}
