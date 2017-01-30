

#ifndef PRACTICE6_SERIALIZATION_H
#define PRACTICE6_SERIALIZATION_H

#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "src/sockets/Tcp.h"
#include "Driver.h"
#include "DetailsDriver.h"

using namespace std;


//receive.
template <class T>
T* receive(Tcp* tcp, int descriptor = 0) {
    T* obj;

    char buffer[65536];
    tcp->receiveData(buffer, sizeof(buffer), descriptor);
    //cout << buffer << endl;

    string str(buffer, sizeof(buffer));
    //cout << str;
    boost::iostreams::basic_array_source<char> device(str.c_str(), str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> obj;
    return obj;
}

//receive.
template <class T>
T receive(int i, Tcp* tcp, int descriptor = 0) {
    T obj;

    char buffer[1024];
    tcp->receiveData(buffer, sizeof(buffer), descriptor);
    //cout << buffer << endl;

    string str(buffer, sizeof(buffer));
    //cout << str;
    boost::iostreams::basic_array_source<char> device(str.c_str(), str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> obj;
    return obj;
}

//send.
template <class T>
void sendTo(T *c, Tcp* tcp, int descriptor = 0){

    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << c;
    s.flush();

    tcp->sendData(serial_str, descriptor);
}

//send.
template <class T>
void sendTo(T c, Tcp* tcp, int descriptor = 0){

    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << c;
    s.flush();

    tcp->sendData(serial_str, descriptor);
}

//get Location From Driver
Node* getLocationFromDriver(DetailsDriver* detailsDrivers);
//send trip.
void sendTrip(DetailsDriver* detailsDrivers, Trip* trip);
//send taxi.
void sendTaxi(DetailsDriver* detailsDrivers, Taxi* taxi);

//send move.
string sendMove(DetailsDriver* dd);

//if success.
void ifSuccess(Tcp* tcp, int socketId);

#endif //PRACTICE6_SERIALIZATION_H
