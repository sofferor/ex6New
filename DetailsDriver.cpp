
#include "DetailsDriver.h"

//Constructor for DetailsDriver.
DetailsDriver::DetailsDriver(int driverId, int taxiId) : driverId(driverId), taxiId(taxiId) {
    available = true;
    timeArrivedLastTrip = 0;
}

//Constructor for DetailsDriver.
DetailsDriver::DetailsDriver() {
    available = true;
    taxiId = -1;
    timeArrivedLastTrip = 0;
}

//Constructor for DetailsDriver.
DetailsDriver::DetailsDriver(int driverId) : driverId(driverId) {
    available = true;
    taxiId = -1;
    timeArrivedLastTrip = 0;
}

//Constructor for DetailsDriver.
DetailsDriver::DetailsDriver(int driverId, Tcp* tcp) : tcp(tcp), driverId(driverId){
    available = true;
    taxiId = -1;
    timeArrivedLastTrip = 0;
}

//Get the driver id.
int DetailsDriver::getDriverId() const {
    return driverId;
}

//Get the taxi id.
int DetailsDriver::getTaxiId() const {
    return taxiId;
}

//Set the driver id.
void DetailsDriver::setDriverId(int driverId) {
    DetailsDriver::driverId = driverId;
}

//Set the taxi id.
void DetailsDriver::setTaxiId(int taxiId) {
    DetailsDriver::taxiId = taxiId;
}

//Check if available.
bool DetailsDriver::isAvailable() const {
    return available;
}

//Set available.
void DetailsDriver::setAvailable(bool available) {
    DetailsDriver::available = available;
}

//Set tcp.
void DetailsDriver::setTcp(Tcp *udp) {
    DetailsDriver::tcp = udp;
}

//Get tcp.
Tcp *DetailsDriver::getTcp() const {
    return tcp;
}
//set socket id.
void DetailsDriver::setSocketId(int socketId) {
    DetailsDriver::socketId = socketId;
}
//get socket id.
int DetailsDriver::getSocketId() const {
    return socketId;
}
// pushing mission to queue.
void DetailsDriver::pushMission(int nextMission) {
    missions.push(nextMission);
}

// getting next mission in queue.
int DetailsDriver::getNextMission() {
    if (missions.empty()) {
        return -1;
    }
    return missions.front();
}

// delete next mission.
void DetailsDriver::deleteNextMission() {
    if (missions.empty()) {
        return;
    }
    missions.pop();
}

// getting next mission in queue.
int DetailsDriver::getMissionNoDelete() {
    if (missions.empty()) {
        return -1;
    }
    return missions.front();
}

// set time of arrive to the destination of last trip.
void DetailsDriver::setTimeArrivedLastTrip(int timeArrivedLastTrip) {
    DetailsDriver::timeArrivedLastTrip = timeArrivedLastTrip;
}

// get time of arrive to the destination of last trip.
int DetailsDriver::getTimeArrivedLastTrip() const {
    return timeArrivedLastTrip;
}

// get first trip id.
int DetailsDriver::popTripId() const {
    return tripId.front();
}

// pushing trip id.
void DetailsDriver::pushTripId(int tripId1) {
    tripId.push(tripId1);
}

//getting taxi type.
int DetailsDriver::getTaxiType() const {
    return taxiType;
}

// setting taxi type.
void DetailsDriver::setTaxiType(int taxiType) {
    DetailsDriver::taxiType = taxiType;
}

// delete trip id.
void DetailsDriver::deleteTripId() {
    tripId.pop();
}
