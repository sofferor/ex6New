
#include "TaxiCenter.h"
#include "Serialization.h"

/*
//Get taxis.
const vector<Taxi *> &TaxiCenter::getTaxis() const {
    return taxis;
}

//Get passengers.
const vector<Passenger *> &TaxiCenter::getPassengers() const {
    return passengers;
}

//Set taxis.
void TaxiCenter::setTaxis(const vector<Taxi *> &taxis) {
    TaxiCenter::taxis = taxis;
}

//Set passngers.
void TaxiCenter::setPassengers(const vector<Passenger *> &passengers) {
    TaxiCenter::passengers = passengers;
}
//Getting the trips.
const vector<Trip *> &TaxiCenter::getTrips() const {
    return trips;
}
//Setting the trips.
void TaxiCenter::setTrips(const vector<Trip *> &trips) {
    TaxiCenter::trips = trips;
}

//Adding passenger.
void TaxiCenter::addPassenger(Passenger *passenger) {
    TaxiCenter::passengers.push_back(passenger);
}
*/


//Adding taxi.
void TaxiCenter::addTaxi(Taxi *taxi) {
    TaxiCenter::taxis.push_back(taxi);
}

//Adding trip.
void TaxiCenter::addTrip(Trip *trip) {
    int size = trips.size();
    for (int i = 0; i < size; i++) {
        if (trip->getTimeToStart() < trips.at(i)->getTimeToStart()) {
            trips.insert(trips.begin() + i, trip);
            break;
        }
    }
    if (size == 0 || trips.size() == size) {
        trips.push_back(trip);
    }
}

//Print the location of the driver.
void TaxiCenter::printDriverLocation(int id) {
    for (int i = 0; i < detailsDrivers.size(); i++) {
        if (detailsDrivers.at(i)->getDriverId() == id) {
            detailsDrivers.at(i)->pushMission(4);

            //Waiting for the thread to print the location of driver.
            while (detailsDrivers.at(i)->getMissionNoDelete() != -1) {
                usleep(10000);
            }
        }
    }
}

//Get the location of the driver.
Node* TaxiCenter::getDriverLocation(int id) {
    for (int i = 0; i < detailsDrivers.size(); i++) {
        if (detailsDrivers.at(i)->getDriverId() == id) {
            return getLocationFromDriver(detailsDrivers.at(i));
        }
    }
    return NULL;
}

//Setting taxis and trips to the drivers.
void TaxiCenter::setAll() {
    /*
    //Assigning taxis to drivers.
    for (int i = 0, j = 0; i < taxis.size() && j < detailsDrivers.size(); i++, j++) {
        for (int k = 0; k < detailsDrivers.size(); k++) {
            if (detailsDrivers.at(k)->getTaxiId() == -1) {
                detailsDrivers.at(k)->setTaxiId(taxis.at(i)->getTaxiId());

                //to serialize the taxi and sendTo it to the driver.
                sendTaxi(detailsDrivers.at(k), taxis.at(i));
                taxis.erase(taxis.begin() + i);/////////check if really delete.
                i--;
                break;
            }
        }
    }
    */

    //Assigning trips to drivers
    for (int i = 0; i < trips.size(); ++i) {
        if (trips.at(i)->getTimeToStart() > clock->getTime()) {
            continue;
        }

        //if we are here there is a trip to assign and we wait for all the drivers to
        //finish the mission.
        for (int j = 0; j < detailsDrivers.size(); ++j) {
            //Waiting for the thread to finsh all his missions.
            while (detailsDrivers.at(j)->getMissionNoDelete() != -1) {
                usleep(10000);
            }
        }
        //now all the drivers arrived to their destination.

        //only here delete the trip.
        if (trips.at(i)->getTimeToStart() < clock->getTime()) {
            trips.erase(trips.begin() + i);
            i--;
            continue;
        }


        //getting a new vector with the detailsDrivers sort by the arrived time of the trip.
        vector<DetailsDriver*> detailsSortedByArrivedTime = getDetailsSortedByArrivedTime();

        for (int k = 0; k < detailsSortedByArrivedTime.size(); k++) {
            set();

            //pass on the ones which are in the middle of trip.
            if (!detailsSortedByArrivedTime.at(k)->isAvailable()) {
                continue;
            }

            if (clock->getTime() == 8) {
                //cout << "           time: 8 in the for, in the for after if " << endl;
            }

            detailsSortedByArrivedTime.at(k)->pushTripId(trips.at(i)->getTripId());
            detailsSortedByArrivedTime.at(k)->pushMission(3);
            set();
            if (detailsSortedByArrivedTime.at(k)->isAvailable()) {
                continue;
            }
            break;

            /*
            Node* location = this->getDriverLocation(detailsDrivers.at(k)->getDriverId());
            if (*trips.at(i)->getStart() == location) {
                if (location != NULL) {
                    delete (location);
                }
                sendTrip(detailsDrivers.at(k), trips.at(i));
                trips.erase(trips.begin() + i);/////////check if really delete.
                //availableDrivers.erase(availableDrivers.begin() + k);
                detailsDrivers.at(k)->setAvailable(false);
                i--;
                break;//////////check if exit the for and not only the if.
            }
            */
        }
    }
}

//Distructor to taxi center.
TaxiCenter::~TaxiCenter() {
    for (int j = 0; j < taxis.size(); ++j) {
        if (taxis[j] != NULL) {
            delete taxis[j];
        }
    }
    taxis.clear();

    for (int j = 0; j < trips.size(); ++j) {
        if (trips[j] != NULL) {
            delete trips[j];
        }
    }
    trips.clear();

    for (int i = 0; i < detailsDrivers.size() ; ++i) {
        if (detailsDrivers[i] != NULL) {
            delete detailsDrivers[i];
        }
    }
    detailsDrivers.clear();

    passengers.clear();
}

/*
//add Details Drivers.
void TaxiCenter::addDetailsDrivers(int driverId) {
    DetailsDriver* detailsDriver = new DetailsDriver(driverId);
    detailsDrivers.push_back(detailsDriver);
}*/

//add Details Drivers.
void TaxiCenter::addDetailsDrivers(int driverId, Tcp *tcp, int socketId) {
    DetailsDriver* detailsDriver = new DetailsDriver(driverId, tcp);
    detailsDriver->setSocketId(socketId);

    //inserting the new details driver by sorting according to the driver id.
    for (int i = 0; i < detailsDrivers.size(); ++i) {
        if (driverId < detailsDrivers[i]->getDriverId()) {
            detailsDrivers.insert(detailsDrivers.begin() + i, detailsDriver);
            return;
        }
    }
    detailsDrivers.push_back(detailsDriver);
}

//get details driver By Id
DetailsDriver* TaxiCenter::getDetailsDriversById(int driverId) {
    for (int i = 0; i < detailsDrivers.size() ; ++i) {
        if (detailsDrivers[i]->getDriverId() == driverId) {
            return detailsDrivers[i];
        }
    }
    return NULL;
}

//update the Time.
void TaxiCenter::updateTime() {
    clock->updateTime();
    //cout << "time: " << clock->getTime() << endl;
    set();
    for (int i = 0; i < detailsDrivers.size(); i++) {
        if (!detailsDrivers.at(i)->isAvailable()) {
            detailsDrivers.at(i)->pushMission(9);
        }
    }
}

//set clock.
void TaxiCenter::setClock(Time* clock) {
    TaxiCenter::clock = clock;
}

//add Taxi To Driver
void TaxiCenter::addTaxiToDriver(int id) {
    for (int i = 0; i < detailsDrivers.size(); ++i) {
        if (detailsDrivers[i]->getDriverId() == id) {
            detailsDrivers[i]->setTaxiId(id);
            break;
        }
    }
}

//get Taxi By Id
Taxi *TaxiCenter::getTaxiById(int id) {
    for (int i = 0; i < taxis.size(); ++i) {
        if (taxis[i]->getTaxiId() == id) {
            return taxis[i];
        }
    }
    return NULL;
}

//delete Taxi By Id
void TaxiCenter::deleteTaxiById(int id) {
    for (int i = 0; i < taxis.size(); ++i) {
        if (taxis[i]->getTaxiId() == id) {
            taxis.erase(taxis.begin() + i);
        }
    }
}

//get trip By Id
Trip *TaxiCenter::getTripByid(int id) {
    for (int i = 0; i < trips.size(); ++i) {
        if (trips[i]->getTripId() == id) {
            return trips[i];
        }
    }
    return NULL;
}

//delete Trip By Id
void TaxiCenter::deleteTripById(int id) {
    for (int i = 0; i < trips.size(); ++i) {
        if (trips[i]->getTripId() == id) {
            trips.erase(trips.begin() + i);
        }
    }
}

//get Details Sorted By Arrived Time
vector<DetailsDriver *> TaxiCenter::getDetailsSortedByArrivedTime() {
    vector<DetailsDriver *> sortedDetails;
    for (int i = 0; i < detailsDrivers.size(); ++i) {
        sortedDetails.push_back(detailsDrivers[i]);
    }
    sort(sortedDetails.begin(), sortedDetails.end(), compareDetailsDriver);
    return sortedDetails;
}

//compare Details Driver
bool TaxiCenter::compareDetailsDriver(DetailsDriver *d1, DetailsDriver *d2) {
    return (d1->getTimeArrivedLastTrip() < d2->getTimeArrivedLastTrip());
}

//close Client Threads
void TaxiCenter::closeClientThreads() {
    for (int i = 0; i < detailsDrivers.size(); ++i) {
        detailsDrivers[i]->pushMission(7);
    }
}

//set
void TaxiCenter::set() {
    for (int j = 0; j < detailsDrivers.size(); ++j) {
        while (detailsDrivers.at(j)->getMissionNoDelete() != -1) {
            usleep(10000);
        }
    }
}
