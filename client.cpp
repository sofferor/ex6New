
#include "src/sockets/Tcp.h"
#include "Driver.h"
#include "Point.h"
#include "Serialization.h"

using namespace std;

//make a driver.
Driver* makeDriver();
//Decide what to do.
void whatToDo(string task, Tcp* tcp, Driver* driver);
//Tke care if trip done.
bool takeCareIfTripDone(Driver* driver, Tcp* udp);

//main for the client.
int main(int argc, char *argv[]) {
    //std::cout << "Hello, from client" << std::endl;
    Tcp* tcp = new Tcp(0, atoi(argv[2]));
    tcp->setIp_address(argv[1]);
    tcp->initialize();

    Driver* d = makeDriver();
    sendTo<int>(d->getId(), tcp);

    char buffer[1024];
    string str("!close");
    while (str != "close") {
        str.assign(receive<string>(1, tcp));
        whatToDo(str, tcp, d);
    }

    if (tcp != NULL) {
        delete (tcp);
    }
    if (d != NULL) {
        d->deletePathFromClient();
        delete (d);
    }
    return 0;
}

//make a driver.
Driver* makeDriver() {
    int driver_id, age, xp, vehicle_id;
    char dummy;
    char status;
    Point p = Point(0,0);
    // getting details.
    cin >> driver_id >> dummy >> age >> dummy >> status >> dummy
        >> xp >> dummy >> vehicle_id;
    Driver *driver = new Driver(driver_id, age, status, xp,
                                vehicle_id);

    return driver;
}

//Decide what to do.
void whatToDo(string task, Tcp* tcp, Driver* driver) {
    switch (task.c_str()[0]) {
        case 'L':
        case 'l':{
            sendTo<Node>(driver->getLocation(), tcp);
            break;
        }
        //for Trip
        case 'R':
        case 'r': {
            sendTo<string>("success", tcp);
            Trip* trip;
            //receive(tcp) >> trip;
            trip = receive<Trip>(tcp);
            driver->setTrip(trip);
            sendTo<string>("success", tcp);
            break;
        }
        case 'M':
        case 'm': {
            driver->moveOneStep();
            if (!takeCareIfTripDone(driver, tcp)) {
                //If standard taxi:
                if (driver->getTaxi()->getSpeed() == 1) {
                    sendTo<string>("Not done trip", tcp);
                }
                else {//Luxury taxi.
                    driver->moveOneStep();
                    if (!takeCareIfTripDone(driver, tcp)) {
                        sendTo<string>("Not done trip", tcp);
                    }
                }

            }
            break;
        }
        case 'T':
        case 't':{
            sendTo<string>("success", tcp);
            Taxi* taxi;
            //receive(tcp) >> taxi;
            taxi = receive<Taxi>(tcp);
            driver->setTaxi(taxi);
            sendTo<string>("success", tcp);
            break;
        }
        default: {
            break;
        }
    }
}

//Tke care if trip done.
bool takeCareIfTripDone(Driver* driver, Tcp* udp) {
    if (driver->getTrip()->getPath().size() == 1) {
        sendTo<string>("Done trip", udp);
        //driver->getTrip()->deletePathFromClient();
        driver->deletePathFromClient();
        return true;
    }
    return false;
}
