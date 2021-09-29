#include "SimpleLane.hpp"
#include <iostream>
using namespace std;

//creates a new simple lane, which is empty
SimpleLane::SimpleLane() {
}

//destructor of simple lane deletes all nodes in the lane, and the vehicles within
SimpleLane::~SimpleLane() {
    //if there is at least one node
    if (length > 0){
        //starts at the head, and deletes nodes until it reaches the tail
        Node *nodeNext = head;
        Node *node = head;
        //while the node is not equal to null, which it will be after tail is deleted
        while (node != NULL) {
            //sets the next node to operate on
            //this will be the tail
            nodeNext = node->getNext();
            //I added this so you, the marker, can see when I am deleting a node
            cout << "deleting a node" << endl;
            //deletes the node
            delete node->getVehicle();
            delete node;
            //sets the node to the nodenext
            node = nodeNext;
        }
    
    //I removed this part.  Used to be while (node != tail) {stuff}
    //cout << "deleting a node" << endl;
    //delete nodeNext->getVehicle();
    //delete nodeNext;
    }
}

//enqueues a new node
void SimpleLane::enqueue(Vehicle* vehicle) {
    //creates a new node to be added
    Node *node = new Node(vehicle);
    //if the list is currently empty, sets head and tail to current node
    if (length == 0) {
        head = node;
        tail = node;
    //otherwise, it sets the newly created node to point to the current head
    //and updates the head to the newly created node
    } else {
        node->setNext(head);
        head = node;
    }
    //length++ to keep track
    length++;
    return;
}

//I added this function in order to debug a segmentation fault
//I do not like segmentation faults
void SimpleLane::print() const {
    Node *node = head;
    cout << "lane contains: ";
        for (unsigned int i = 0;i<length-1;i++){
        cout << node->getVehicle() << ", ";
        node = node->getNext();
    }
    cout << node->getVehicle() << endl;
}

//updates the tail to be the node before the current tail
//this is where a doubly linked queue would be useful, but I 
//have not created one due to my time being taken up by applying for internships.
Vehicle* SimpleLane::dequeue() {
    //if there is a node to dequeue
    if (length > 0){
        //starts at the head, and attempts to find the last node
        Node *node = head;
        Node *prevnode;
        //while the current node is not equal to tail
        while (node != tail){
            //sets the previous node (possibly the new tail) to the current node, as it is not the tail
            prevnode = node;
            //another step down the list
            node = node->getNext();
        }
        
        //after while loop is exited, prevnode should be the node before the current tail
        Vehicle *vehicle = node->getVehicle();

        //I was getting segmentation faults, I'm keeping this here in case they come back
        //this->print();

        //if there is at least 2 nodes in the list
        if (length > 1){
            //prevnode has its next node set to null, as it is the new tail
            prevnode->setNext(NULL);
            //as it is the new tail
            tail = prevnode;
        //if there was only one node, then it just sets head and tail to zero, which is the initialized condition
        } else {
            head = 0;
            tail = 0;
        }
        //deletes the old tail
        delete node;
        //length-- to keep track
        length--;
        return vehicle;        
    }
    //if its empty, return null operator
    return 0;
}

//simple check to see if the lane is empty
bool SimpleLane::empty() const { return (length == 0); };

//returns the length variable.  This is why I kept track
unsigned int SimpleLane::count() const { return length; };

//returns the front of the lane's vehicle, if there is a front.  Otherwise returns 0.
const Vehicle* SimpleLane::front() const { 
    if (tail != NULL){
        return tail->getVehicle();
    }
    return NULL;
};

//returns the back of the lane's vehicle, if there is a back.  otherwise returns 0.
const Vehicle* SimpleLane::back() const {
    if (head != NULL){
        return head->getVehicle();
    }
    return NULL;
};
