#ifndef NODE_HPP
#define NODE_HPP

#include "Vehicle.hpp"

class Node {
private:
//every node stores a vehicle, and a pointer to the next node
Vehicle *vehicle;
Node *nextNode;

public:
//these are primarily for use with the SimpleLane function

//gets the node after this one
Node *getNext();
//sets the "next" node
void setNext(Node *node);
//gets the vehicle stored in this node
Vehicle *getVehicle();
//node constructor with a vehicle
Node(Vehicle *vehicle);
//node destructor
virtual ~Node();
};


#endif /* end of include guard: NODE_HPP */