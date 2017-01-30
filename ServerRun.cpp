
#include "ServerRun.h"
#include "Point.h"
/*
#include "Matrix2D.h"
#include "Driver.h"
#include "TaxiCenter.h"
 */
#include "TaxiStandard.h"
#include "TaxiLuxury.h"
#include "Serialization.h"

// constructor.
ServerRun::ServerRun(Tcp *tcp) : tcp(tcp) {
    bfs = BFS();
    taxiCenter = new TaxiCenter();
    recieve = new Recieve(taxiCenter);
    clock = new Time();
    taxiCenter->setClock(clock);
    selection = -1;

    // Init mutex
    pthread_mutex_init(&this->lockEnvironment, 0);
    pthread_mutex_init(&this->lockTaxies, 0);
    pthread_mutex_init(&this->lockList, 0);
}

//initialize.
void ServerRun::initialize() {
    do {
        matrix2D = recieve->recieveMatrix();
        if (matrix2D == NULL) {
            recieve->printInvalid();
        }
    } while (matrix2D == NULL);

    tp = new ThreadsPool(5);
}

// begin the server operation.
void ServerRun::begin() {
    char dummy;
    int descriptor = -1;
    int checkThread = 1;
    string s;

    do {
        s.clear();
        getline(cin, s);
        boost::trim(s);
        if (!Recieve::isInt(s)) {
            recieve->printInvalid();
            continue;
        }
        selection = stoi(s);

        switch (selection) {
            // insert driver
            case 1: {

                //getting num of driver.
                int numOfDrivers;
                s.clear();
                getline(cin, s);
                boost::trim(s);
                if (!Recieve::isInt(s)) {
                    recieve->printInvalid();
                    continue;
                }
                numOfDrivers = stoi(s);

                while (numOfDrivers > 0) {
                    descriptor = tcp->acceptClient();

                    //Receiving the driver id.
                    int driverId = -1;
                    driverId = receive<int>(1, tcp, descriptor);

                    //pthread_mutex_lock(&this->lockList);
                    taxiCenter->addDetailsDrivers(driverId, tcp, descriptor);

                    ClientDetails* clientDetails = new ClientDetails();
                    clientDetails->client = descriptor;
                    clientDetails->server = this;
                    clientDetails->detailsDriver = taxiCenter->getDetailsDriversById(driverId);

                    pthread_t* thread = new pthread_t();
                    // Create a thread in order to listen to the client
                    checkThread = pthread_create(thread, NULL, clientThread, (void*)clientDetails);
                    if (checkThread){
                        cout << "Error:unable to create thread," << checkThread << endl;
                        exit(-1);
                    }
                    this->clientThreads[driverId] = thread;

                    numOfDrivers--;
                    //pthread_mutex_unlock(&this->lockList);
                }
                break;
            }

                // new ride
            case 2: {
                Trip *ride = recieve->recieveTrip();
                if (ride == NULL) {
                    recieve->printInvalid();
                    break;
                }

                //build the trip details.
                TripDetails* tripDetails = new TripDetails();
                tripDetails->server = this;
                tripDetails->trip = ride;

                Task* task = new Task(&tripThread, (void*)tripDetails);
                tp->addTask(task);
/*
                pthread_t* thread = new pthread_t();
                // Create a thread in order to calculate the path of the trip.
                checkThread = pthread_create(thread, NULL, tripThread, (void*)tripDetails);
                if (checkThread){
                    cout << "Error:unable to create thread," << checkThread << endl;
                    exit(-1);
                }
*/
                //adding to the map:the trip ID and the thread.
                taskMap[ride->getTripId()] = task;


                // adding the ride.
                taxiCenter->addTrip(ride);
                break;
            }

                // insert taxi
            case 3: {
                Taxi* taxi;
                taxi = recieve->recieveTaxi();
                if (taxi == NULL) {
                    recieve->printInvalid();
                    break;
                }

                taxiCenter->addTaxi(taxi);
                break;
            }

                // printing driver location
            case 4: {
                int driverId;

                s.clear();
                getline(cin, s);
                boost::trim(s);
                if (!Recieve::isInt(s)) {
                    recieve->printInvalid();
                    continue;
                }
                driverId = stoi(s);

                if (!taxiCenter->printDriverLocation(driverId)) {
                    recieve->printInvalid();
                }
                break;
            }

            case 9: {
                taxiCenter->set();
                taxiCenter->setAll();
                taxiCenter->updateTime();
                break;
            }

            case 7: {
                break;
            }

            default: {
                recieve->printInvalid();
                break;
            }

        }

        taxiCenter->set();

    } while (selection != 7);


    taxiCenter->closeClientThreads();


    //the server is waiting for all threads to finish.
    for (std::map<int, pthread_t*>::iterator it=clientThreads.begin(); it!=clientThreads.end(); ++it) {
        pthread_join(*it->second, NULL);
    }
}

// thread function for the clients.
void* ServerRun::clientThread(void *clientDetails) {
    ClientDetails* c = (ClientDetails*)clientDetails;
    c->server->clientRun(c);
    c = NULL;
    return NULL;
}

/*void ServerRun::clientRun(ServerRun::ClientDetails* clientDetails) {
    //Receiving the driver id.
    int driverId = -1;
    driverId = receive<int>(1, tcp, clientDetails->client);
    cout << "server: got driverId" << endl;

    pthread_mutex_lock(&this->lockList);
    taxiCenter->addDetailsDrivers(driverId, tcp, clientDetails->client);
    pthread_mutex_unlock(&this->lockList);

}*/

// running the client.
void ServerRun::clientRun(ServerRun::ClientDetails* clientDetails) {
    DetailsDriver* detailsDriver = clientDetails->detailsDriver;
    int mission;
    int timeArrived = -1;

    do {
        if (detailsDriver->getTaxiId() == -1) {
            setTaxiForClient(clientDetails);
        }

        mission = detailsDriver->getNextMission();

        switch (mission) {

            //if there are no missions yet.
            case -1: {
                continue;
            }

            // adding trip to driver.
            case 3: {
                Node* location = taxiCenter->getDriverLocation(detailsDriver->getDriverId());
                Trip* trip = taxiCenter->getTripByid(detailsDriver->popTripId());
                if (trip == NULL) {
                    cout << "client: trip is null" << endl;
                }
                if (trip != NULL && *trip->getStart() == location) {
                    detailsDriver->setAvailable(false);////check if need to lock
                    timeArrived = whenArrive(trip, detailsDriver->getTaxiType());
                    sendTrip(detailsDriver, trip);
                    //the trip will be deleted from the setAll function.
                }
                detailsDriver->deleteTripId();
                if (location != NULL) {
                    delete (location);
                }
                break;
            }

            //printing the location.
            case 4: {
                Node* location = getLocationFromDriver(detailsDriver);
                cout << location;
                if (location != NULL) {
                    delete (location);
                }
                break;
            }

            case 9: {
                string ifDone = sendMove(detailsDriver);

                //if done trip it will be == 0.
                if (ifDone.compare("Done trip") == 0) {
                    detailsDriver->setTimeArrivedLastTrip(timeArrived);
                    detailsDriver->setAvailable(true);
                }
                break;
            }

            default: {
                break;
            }
        }

        detailsDriver->deleteNextMission();

    } while (mission != 7);

    sendTo<string>("close", tcp, detailsDriver->getSocketId());
    pthread_exit(NULL);

}


// thread function for the trips.
void ServerRun::tripThread(void *tripDetails) {
    TripDetails* t = (TripDetails*)tripDetails;
    t->server->tripCalculate(t);
}

// calculating the trip.
void ServerRun::tripCalculate(ServerRun::TripDetails *tripDetails) {
    pthread_mutex_lock(&this->lockEnvironment);
    if (bfs.findPath(matrix2D, tripDetails->trip->getStart(), tripDetails->trip->getEnd())) {
        tripDetails->trip->setPath(matrix2D->getPath(tripDetails->trip->getEnd()));
    }
    matrix2D->initializeEnvironment();
    pthread_mutex_unlock(&this->lockEnvironment);
    tripDetails->trip->setDoneCalculatePath(true);
}

//setting taxi for client.
void ServerRun::setTaxiForClient(ClientDetails* clientDetails) {
    DetailsDriver* detailsDriver = clientDetails->detailsDriver;

    pthread_mutex_lock(&this->lockTaxies);
    Taxi* taxi = clientDetails->server->taxiCenter->getTaxiById(detailsDriver->getDriverId());

    //if there is no taxi with the driver id.
    if (taxi == NULL) {
        pthread_mutex_unlock(&this->lockTaxies);
        return;
    }

    detailsDriver->setTaxiId(taxi->getTaxiId());
    detailsDriver->setTaxiType(taxi->getSpeed());

    //to serialize the taxi and sendTo it to the driver.
    sendTaxi(detailsDriver, taxi);
    //delete taxi from the list.
    clientDetails->server->taxiCenter->deleteTaxiById(detailsDriver->getDriverId());

    pthread_mutex_unlock(&this->lockTaxies);
}

// determine when the taxi should arrive to the destination.
int ServerRun::whenArrive(Trip *trip, int taxiType) {
    //waiting for the trip to be calculated
    while (!trip->isDoneCalculatePath()) {
        usleep(10000);
    }
    //if path is emty - means there is no path and the trip was supposed to be erased-problem
    if (trip->isPathEmpty()){
        cout << "ERROR: ServerRun::whenArrive - SHOULD NOT REACH HERE." << endl;
        return -1;
    }
    double check = ((double) trip->getPath().size()) / ((double) taxiType);
    int timeOfPath = (int) check;

    if (taxiType == 2) {
        if (((double) timeOfPath) != check) {
            timeOfPath = timeOfPath + 1;
        }
    }

    return trip->getTimeToStart() + timeOfPath;
}

// destructor.
ServerRun::~ServerRun() {

    pthread_mutex_destroy(&lockEnvironment);
    pthread_mutex_destroy(&lockTaxies);
    pthread_mutex_destroy(&lockList);

    for (std::map<int, pthread_t*>::iterator it=clientThreads.begin(); it!=clientThreads.end(); ++it) {
        delete(it->second);
    }

    for (std::map<int, Task*>::iterator it=taskMap.begin(); it!=taskMap.end(); ++it) {
        delete(it->second);
    }



    // deleting items.
    if (clock != NULL) {
        delete (clock);
    }
    if (recieve != NULL) {
        delete (recieve);
    }
    if (tcp != NULL) {
        delete (tcp);
    }
    if (taxiCenter != NULL) {
        delete (taxiCenter);
    }
    if (matrix2D != NULL) {
        delete (matrix2D);
    }

    tp->emptyPool();
    tp->join();
    if (tp != NULL) {
        delete (tp);
    }
}
