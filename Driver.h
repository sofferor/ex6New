

#ifndef EX2_DRIVER_H
#define EX2_DRIVER_H

#include "Node.h"
#include "Taxi.h"
#include "Trip.h"
#include <iostream>
#include <fstream>
#include <vector>


enum maritalStatus {SINGLE, MARRIED, DIVORCED, WIDOWED};

//Class for driver.
//With some members.
class Driver {
private:
    Taxi* taxi;
    Trip* trip;
    int id;
    int age;
    maritalStatus mStatus;
    int yOfExp;
    int avgSatisfaction;
    Node* location;
    int vehicle_id;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & taxi;
        ar & trip;
        ar & id;
        ar & age;
        ar & mStatus;
        ar & yOfExp;
        ar & avgSatisfaction;
        ar & location;
        ar & vehicle_id;
    }

public:
    /**
     * constructor for Driver.
     *
     * @param id
     * @param age
     * @param mStatus
     * @param yOfExp
     * @param location
     */
    Driver(int id, int age, maritalStatus mStatus, int yOfExp, Node *location);

    /**
     * constructor for Driver.
     *
     * @param id
     * @param age
     * @param mrStatus
     * @param yOfExp
     * @param vehicle_id
     */
    Driver(int id, int age, char mrStatus, int yOfExp, int vehicle_id);

    /**
     * constructor for Driver.
     *
     * @param id
     * @param age
     * @param mrStatus
     * @param yOfExp
     * @param vehicle_id
     * @param locationD
     */
    Driver(int id, int age, char mrStatus, int yOfExp, int vehicle_id, Node* locationD);

    //Constructor for Driver.
    Driver(Driver* newDriver);

    //Constructor for DetailsDriver.
    Driver() {};

    /**
     * Distructor for Driver.
     */
    virtual ~Driver();

    /**
     * getting driver's taxi.
     * @return Taxi*
     */
    Taxi *getTaxi() const;

    /**
     * setting driver's taxi.
     * @param taxi
     */
    void setTaxi(Taxi *taxi);

    /**
     * get driver's id.
     * @return int
     */
    int getId() const;

    /**
     * setting driver's id.
     * @param id
     */
    void setId(int id);

    /**
     * getting driver's age.
     * @return int
     */
    int getAge() const;

    /**
     * setting driver's age.
     * @param age
     */
    void setAge(int age);

    /**
     * driver's marital status.
     * @return maritalStatus
     */
    maritalStatus getMStatus() const;

    /**
     * setting driver's marital status.
     * @param mStatus
     */
    void setMStatus(maritalStatus mStatus);

    /**
     * driver's years of experience.
     * @return int
     */
    int getYOfExp() const;

    /**
     * setting driver's years of experience.
     * @param yOfExp
     */
    void setYOfExp(int yOfExp);

    /**
     * average satisfaction.
     * @return int
     */
    int getAvgSatisfaction() const;

    /**
     * setting average satisfaction.
     * @param avgSatisfaction
     */
    void setAvgSatisfaction(int avgSatisfaction);

    /**
     * driver's location.
     * @return Node*
     */
    Node *getLocation() const;

    /**
     * setting driver's location.
     * @param location
     */
    void setLocation(Node *location);

    /**
     * get driver's trip.
     * @return Trip
     */
    Trip *getTrip() const;

    /**
     * setting Driver's trip.
     * @param trip
     */
    void setTrip(Trip *trip);

    /**
     * printing driver location.
     */
    void printLocation();

    /**
     * clearing the trip.
     */
    void clearTrip();

    //move one step.
    void moveOneStep();

    //delete from path.
    void deletePathFromClient();
};


#endif //EX2_DRIVER_H
