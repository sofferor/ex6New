//
// Created by haim on 05/12/16.
//

#ifndef EX2_TRIP_H
#define EX2_TRIP_H


#include <vector>
#include "Node.h"
#include <boost/serialization/vector.hpp>

//Class trip.
//With source and destination.
class Trip {
private:
    Node* start;
    Node* end;
    int rideId;
    double metersPassed;
    int numOfPassengers;
    double tariff;
    vector<Node*> path;
    int timeToStart;
    bool doneCalculatePath;


    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & start;
        ar & end;
        ar & rideId;
        ar & metersPassed;
        ar & numOfPassengers;
        ar & tariff;
        ar & path;
        ar & timeToStart;
        ar & doneCalculatePath;
    }

public:
    /**
     * constructor for Trip.
     *
     * @param start
     * @param end
     * @param rideId
     * @param metersPassed
     * @param numOfPassengers
     * @param tariff
     */
    Trip(Node *start, Node *end, int rideId, double metersPassed,
         int numOfPassengers, double tariff);

    //Constructor for trip.
    Trip(Node *start, Node *end, int rideId, int numOfPassengers,
         double tariff);

    //Constructor for trip.
    Trip(Node *start, Node *end, int rideId, int numOfPassengers,
         double tariff, int timeToStart);

    //Constructor for trip.
    Trip();

    /**
     * getting the start position.
     * @return Node*
     */
    Node *getStart() const;

    /**
     * setting the start position.
     * @param start Node*
     */
    void setStart(Node *start);

    /**
     * getting the end position.
     * @return Node*
     */
    Node *getEnd() const;

    /**
     * setting the end position.
     * @param end Node*
     */
    void setEnd(Node *end);

    /**
     * getting how many meters have been passed.
     * @return double
     */
    double getMetersPassed() const;

    /**
     * setting how many meters have been passed.
     * @param metersPassed
     */
    void setMetersPassed(double metersPassed);

    /**
     * getting how many passengers in the trip.
     * @return int
     */
    int getNumOfPassengers() const;

    /**
     * setting the number of passengers.
     * @param numOfPassengers
     */
    void setNumOfPassengers(int numOfPassengers);

    /**
     * getting the tariff of a current trip.
     * @return int
     */
    double getTariff() const;

    /**
     * setting the tariff of a current trip.
     * @param tariff
     */
    void setTariff(int tariff);

    /**
     * destructor for trip.
     */
    virtual ~Trip();

    //get trip id.
    int getTripId();

    //get the path of trip.
    vector<Node*> getPath() const;

    //get the Time To Start
    int getTimeToStart() const;

    //set path.
    void setPath(const vector<Node*> &path);

    //set the Time To Start.
    void setTimeToStart(int timeToStart);

    //Delete from client.
    void deleteFromPathClient();

    void deleteLastNodeInPath();

    Node* getLastNodeInPath();

    bool isPathEmpty();

    bool isDoneCalculatePath() const;

    void setDoneCalculatePath(bool doneCalculatePath);
};


#endif //EX2_TRIP_H
