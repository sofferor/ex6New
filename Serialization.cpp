#include "Serialization.h"

//get Location From Driver
Node* getLocationFromDriver(DetailsDriver* detailsDrivers) {
    Node* location = NULL;
    Tcp* tcp = detailsDrivers->getTcp();
    int socketId = detailsDrivers->getSocketId();
    sendTo<string>("location", tcp, socketId);
    location = receive<Node>(tcp, socketId);
    return location;
}

//send trip.
void sendTrip(DetailsDriver* detailsDrivers, Trip* trip) {
    Tcp* tcp = detailsDrivers->getTcp();
    int socketId = detailsDrivers->getSocketId();
    sendTo<string>("ride", tcp, socketId);
    ifSuccess(tcp, socketId);
    //waiting for the trip to be calculated
    while (!trip->isDoneCalculatePath()) {
        usleep(10000);
    }
    sendTo<Trip>(trip, tcp, socketId);
    ifSuccess(tcp, socketId);
}

//send taxi.
void sendTaxi(DetailsDriver* detailsDrivers, Taxi* taxi) {
    Tcp* tcp = detailsDrivers->getTcp();
    int socketId = detailsDrivers->getSocketId();
    sendTo<string>("taxi", tcp, socketId);
    ifSuccess(tcp, socketId);
    sendTo<Taxi>(taxi, tcp, socketId);
    ifSuccess(tcp, socketId);
}

string sendMove(DetailsDriver* dd) {
    sendTo<string>("move", dd->getTcp(), dd->getSocketId());
    string ifDone = receive<string>(1, dd->getTcp(), dd->getSocketId());
    return ifDone;
}

void ifSuccess(Tcp* tcp, int socketId) {
    string ifReceive;
    ifReceive = receive<string>(1, tcp, socketId);
}
