//
// Created by or on 05/12/16.
//


#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>


#include <map>
#include <boost/serialization/access.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>

using namespace std;

#ifndef EX2_TAXI_H
#define EX2_TAXI_H

enum color {RED, BLUE, GREEN, PINK, WHITE};
enum manufacturer {HONDA, SUBARO, TESLA, FIAT};

//Class for taxi.
//Which contain some parameters.
class Taxi {
protected:
    map<char, color> taxiColor;
    map<char, manufacturer> taxiManufacturer;
    int taxiId;
    int numOfKilometers;
    int tarrif;
    color colorOfTaxi;
    manufacturer manufacturerOfTaxi;
    int speed;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & taxiId;
        ar & numOfKilometers;
        ar & tarrif;
        ar & colorOfTaxi;
        ar & manufacturerOfTaxi;
        ar & speed;
    }


public:
    //Constructor for Taxi with parameters.
    Taxi(){};
    //Constructor for Taxi with parameters.
    Taxi(int taxiId, int numOfKilometers, int tarrif, color colorOfTaxi,
         manufacturer manufacturerOfTaxi);
    //Constructor for Taxi with parameters.
    Taxi(int taxiId, char colorOfTaxi1, char manufacturerOfTaxi1);

    //Get taxi id.
    int getTaxiId() const;

    //Get the number of kilometers.
    int getNumOfKilometers() const;

    //Get the tarrif.
    int getTarrif() const;

    //Get the color.
    color getColorOfTaxi() const;

    //Get the manufacture.
    manufacturer getManufacturerOfTaxi() const;

    //Set the taxi id.
    void setTaxiId(int taxiId);

    //Set the number of kilometers.
    void setNumOfKilometers(int numOfKilometers);

    //Set the tarrif.
    void setTarrif(int tarrif);

    //Set the color.
    void setColorOfTaxi(color colorOfTaxi);

    //Set the manufacture.
    void setManufacturerOfTaxi(manufacturer manufacturerOfTaxi);

    //Add the number of kilometers.
    void addNumOfKilometers(int numOfKilometers);

    //Get the speed.
    virtual int getSpeed() const = 0;

    //Set the speed.
    virtual void setSpeed(int speed) = 0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Taxi)

#endif //EX2_TAXI_H
