#include "Trip.h"

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
Trip::Trip(Node *start, Node *end, int rideId, double metersPassed,
           int numOfPassengers, double tariff) : start(start), end(end),
                                              rideId(rideId),
                                              metersPassed(metersPassed),
                                              numOfPassengers(numOfPassengers),
                                              tariff(tariff) {
    path = NULL;
    doneCalculatePath = false;
}

//Constructor for trip.
Trip::Trip(Node *start, Node *end, int rideId, int numOfPassengers,
           double tariff)
        : start(start), end(end), rideId(rideId),
          numOfPassengers(numOfPassengers), tariff(tariff) {
    path = NULL;
    doneCalculatePath = false;
}

//Constructor for trip.
Trip::Trip(Node *start, Node *end, int rideId, int numOfPassengers,
           double tariff, int timeToStart)
        : start(start),
          end(end),
          rideId(rideId),
          numOfPassengers(numOfPassengers),
          tariff(tariff),
          timeToStart(timeToStart) {
    path = NULL;
    doneCalculatePath = false;
}

//Constructor for trip.
Trip::Trip() {
    start = NULL;
    end = NULL;
    path = NULL;
    doneCalculatePath = false;
}

/**
 * destructor for trip.
 */
Trip::~Trip() {}

/**
 * getting the start position.
 * @return Node*
 */
Node *Trip::getStart() const {
    return start;
}

/**
 * setting the start position.
 * @param start Node*
 */
void Trip::setStart(Node *start) {
    Trip::start = start;
}

/**
 * getting the end position.
 * @return Node*
 */
Node *Trip::getEnd() const {
    return end;
}

/**
 * setting the end position.
 * @param end Node*
 */
void Trip::setEnd(Node *end) {
    Trip::end = end;
}

/**
 * getting how many meters have been passed.
 * @return double
 */
double Trip::getMetersPassed() const {
    return metersPassed;
}


/**
 * setting how many meters have been passed.
 * @param metersPassed
 */
void Trip::setMetersPassed(double metersPassed) {
    Trip::metersPassed = metersPassed;
}

/**
 * getting how many passengers in the trip.
 * @return int
 */
int Trip::getNumOfPassengers() const {
    return numOfPassengers;
}

/**
 * setting the number of passengers.
 * @param numOfPassengers
 */
void Trip::setNumOfPassengers(int numOfPassengers) {
    Trip::numOfPassengers = numOfPassengers;
}

/**
 * getting the tariff of a current trip.
 * @return int
 */
double Trip::getTariff() const {
    return tariff;
}

/**
 * setting the tariff of a current trip.
 * @param tariff
 */
void Trip::setTariff(int tariff) {
    Trip::tariff = tariff;
}

//get the path of trip.
vector<Node*> Trip::getPath() const {
    return path;
}

//get the Time To Start
int Trip::getTimeToStart() const {
    return timeToStart;
}

//set path.
void Trip::setPath(const vector<Node*> &path) {
    Trip::path = path;
}

//set the Time To Start.
void Trip::setTimeToStart(int timeToStart) {
    Trip::timeToStart = timeToStart;
}

//Delete from client.
void Trip::deleteFromPathClient() {
    for (int j = 0; j < path.size(); ++j) {
        if (path[j] != NULL) {
            delete path[j];
        }
    }
    path.clear();

    /*
    if (start != NULL) {
        delete (start);
    }
    if (end != NULL) {
        delete (end);
    }
     */
}

//get trip id
int Trip::getTripId() {
    return this->rideId;
}

void Trip::deleteLastNodeInPath() {
    if (path.size() != 0 && path.at(path.size() - 1) != NULL) {
        delete(path.at(path.size() - 1));
        path.pop_back();
    }
}

Node *Trip::getLastNodeInPath() {
    if (path.size() != 0 && path.at(path.size() - 1) != NULL) {
        return(path.at(path.size() - 1));
    }
    return NULL;
}

bool Trip::isPathEmpty() {
    return path.empty();
}

bool Trip::isDoneCalculatePath() const {
    return doneCalculatePath;
}

void Trip::setDoneCalculatePath(bool doneCalculatePath) {
    Trip::doneCalculatePath = doneCalculatePath;
}
