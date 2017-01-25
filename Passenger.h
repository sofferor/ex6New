
#ifndef EX2_PASSENGER_H
#define EX2_PASSENGER_H

#include <iostream>
#include "Node.h"

//Class for passenger.
//Which contain source and destination.
class Passenger {
private:
    Node* _source;
    Node* _destination;
public:
    //Empty constructor for passenger.
    Passenger();

    //Constructor for passenger with parameters.
    Passenger(Node *source, Node *destination);

    //Destructor.
    virtual ~Passenger() {};

    //Get the satisfaction.
    int getSatisfaction();
};

#endif //EX2_PASSENGER_H
