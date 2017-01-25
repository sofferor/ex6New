#include "Passenger.h"

//Empty constructor for passenger.
Passenger::Passenger() {
    _source = NULL;
    _destination = NULL;
}

//Constructor for passenger with parameters.
Passenger::Passenger(Node *source, Node *destination) {
    _source = source;
    _destination = destination;
}

//Get the satisfcation.
int Passenger::getSatisfaction() {
    return rand() % 5 + 1;
}
