#include <iostream>
#include "Matrix2D.h"
#include "BFS.h"
#include "TaxiCenter.h"
#include "ThreadsPool.h"

using namespace std;

#ifndef EX5_SERVER_H
#define EX5_SERVER_H

class ServerRun {
private:
    Matrix2D* matrix2D;
    BFS bfs;
    TaxiCenter* taxiCenter;
    Time* clock;
    Tcp* tcp;
    int selection;
    pthread_mutex_t lockEnvironment;
    pthread_mutex_t lockTaxies;
    pthread_mutex_t lockList;
    ThreadsPool* tp;

    //map for driverId and the thread of this driver.
    map<int, pthread_t*> clientThreads;
    //map for tripId and the thread of this trip.
    map<int, Task*> taskMap;

    struct ClientDetails
    {
        DetailsDriver* detailsDriver;
        int client;
        ServerRun* server;
    };

    struct TripDetails
    {
        Trip* trip;
        ServerRun* server;
    };

public:
    // constructor.
    ServerRun(Tcp *tcp);
    //initialize.
    void initialize();
    // begin the server operation.
    void begin();
    // thread function for the clients.
    static void* clientThread(void* clientDetails);
    // running the client.
    void clientRun(ClientDetails* clientDetails);
    // thread function for the trips.
    static void tripThread(void* tripDetails);
    // calculating the trip.
    void tripCalculate(TripDetails* tripDetails);
    //setting taxi for client.
    void setTaxiForClient(ClientDetails* clientDetails);
    // determine when the taxi should arrive to the destination.
    int whenArrive(Trip* trip, int taxiType);
    // destructor.
    virtual ~ServerRun();
};

#endif //EX5_SERVER_H

