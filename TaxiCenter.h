
#ifndef EX2_TAXICENTER_H
#define EX2_TAXICENTER_H


#include <vector>
#include "Taxi.h"
#include "Passenger.h"
#include "Driver.h"
#include "Trip.h"
#include "DetailsDriver.h"
#include "Time.h"

//Class for taxi center.
//Which contain some parameters.
class TaxiCenter {
private:
    //Details of driver with driver ID and taxi ID.
    vector<DetailsDriver*> detailsDrivers;
    Time* clock;

    vector<Taxi*> taxis;
    vector<Passenger*> passengers;
    vector<Trip*> trips;
public:
    //Constructor for Taxi center with parameters.
    TaxiCenter() {}

    //Get taxis.
    //const vector<Taxi *> &getTaxis() const;

    //Get passengers.
    //const vector<Passenger *> &getPassengers() const;

    //Set taxis.
    //void setTaxis(const vector<Taxi *> &taxis);

    //Set passngers.
    //void setPassengers(const vector<Passenger *> &passengers);

    //Getting the trips.
    //const vector<Trip *> &getTrips() const;

    //Setting the trips.
    //void setTrips(const vector<Trip *> &trips);

    //Adding taxi.
    void addTaxi(Taxi* taxi);

    //Adding passenger.
    //void addPassenger(Passenger* passenger);

    //Adding trip.
    void addTrip(Trip* trip);

    //get Taxi By Id
    Taxi* getTaxiById(int id);

    //get trip By Id
    Trip* getTripByid(int id);

    //delete Taxi By Id
    void deleteTaxiById(int id);

    //Print the location of the driver.
    void printDriverLocation(int id);

    //Get the location of the driver.
    Node* getDriverLocation(int id);

    //set clock.
    void setClock(Time *clock);

    //Setting taxis and trips to the drivers.
    void setAll();

    //add Details Drivers.
    //void addDetailsDrivers(int driverId);

    //add Details Drivers.
    void addDetailsDrivers(int driverId, Tcp* tcp, int socketId);

    //get details driver By Id
    DetailsDriver* getDetailsDriversById(int driverId);

    //update the Time.
    void updateTime();

    //Distructor to taxi center.
    virtual ~TaxiCenter();

    //add Taxi To Driver
    void addTaxiToDriver(int id);

    //delete Trip By Id
    void deleteTripById(int id);

    //get Details Sorted By Arrived Time
    vector<DetailsDriver*> getDetailsSortedByArrivedTime();

    //compare Details Driver
    static bool compareDetailsDriver(DetailsDriver* d1,DetailsDriver* d2);

    //close Client Threads
    void closeClientThreads();

    //set
    void set();
};


#endif //EX2_TAXICENTER_H
