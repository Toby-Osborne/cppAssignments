#include "Node.hpp"
#include <iostream>
using namespace std;

//initializes a node with a vehicle pointer
Node::Node(Vehicle *vehicle) {
    this->vehicle = vehicle;
    this->nextNode = NULL;
}

//returns the node this node points to
Node *Node::getNext() {
    return nextNode;
}

//sets the "next" node for this 
void Node::setNext(Node *node) {
    nextNode = node;
}

//returns the vehicle pointer stored in this node
Vehicle *Node::getVehicle() {
    return vehicle;
}

//does not delete the vehicle stored within this node, this is
//done by the SimpleLane class
Node::~Node() {}