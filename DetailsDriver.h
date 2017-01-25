#include <queue>
#include <iostream>
#include <unistd.h> ////////// may be a problem!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
#include "src/sockets/Tcp.h"

#ifndef PRACTICE6_DETAILSDRIVER_H
#define PRACTICE6_DETAILSDRIVER_H


//Class details driver.
//for the details driver.
class DetailsDriver {
private:
    int driverId;
    int taxiId;
    bool available;
    Tcp* tcp;
    int socketId;
    //missions for the driver from the server side.
    queue<int> missions;
    int timeArrivedLastTrip;
    queue<int> tripId;
    int taxiType;

public:

    //Constructor for DetailsDriver.
    DetailsDriver(int driverId, int taxiId);

    //Constructor for DetailsDriver.
    DetailsDriver();

    //Constructor for DetailsDriver.
    DetailsDriver(int driverId);

    //Constructor for DetailsDriver.
    DetailsDriver(int driverId, Tcp* tcp);

    //deconstructor for DetailsDriver.
    virtual ~DetailsDriver() {};

    //Get the driver id.
    int getDriverId() const;

    //Get the taxi id.
    int getTaxiId() const;

    //Check if available.
    bool isAvailable() const;

    //Set the driver id.
    void setDriverId(int driverId);

    //Set the taxi id.
    void setTaxiId(int taxiId);

    //Set available.
    void setAvailable(bool available);

    //Get tcp.
    Tcp *getTcp() const;

    //Set tcp.
    void setTcp(Tcp *udp);

    //set socket id.
    void setSocketId(int socketId);

    //get socket id.
    int getSocketId() const;

    // pushing mission to queue.
    void pushMission(int nextMission);

    // getting next mission.
    int getNextMission();

    // delete next mission.
    void deleteNextMission();

    //get mission without delete it.
    int getMissionNoDelete();

    // set time of arrive to the destination of last trip.
    void setTimeArrivedLastTrip(int timeArrivedLastTrip);

    // get time of arrive to the destination of last trip.
    int getTimeArrivedLastTrip() const;

    // get first trip id.
    int popTripId() const;

    // delete trip id.
    void deleteTripId();

    //pushing trip id.
    void pushTripId(int tripId1);

    // getting taxi type.
    int getTaxiType() const;

    // setting taxi type.
    void setTaxiType(int taxiType);

};


#endif //PRACTICE6_DETAILSDRIVER_H
