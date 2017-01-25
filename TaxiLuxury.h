//
// Created by or on 05/12/16.
//

#ifndef EX2_TAXILUXURY_H
#define EX2_TAXILUXURY_H

#include "Taxi.h"
/*
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


#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
*/

//Class for luxury taxi.
//Which contain some parameters.
class TaxiLuxury : public Taxi {

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Taxi>(*this);
        //ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Taxi);
    }


public:
    //Constructor for luxury Taxi.
    TaxiLuxury(){};
    //Constructor for luxury Taxi with parameters.
    TaxiLuxury(int taxiId1, int numOfKilometers1, int tarrif1,
                 color colorOfTaxi1, manufacturer manufacturerOfTaxi1);

    //Constructor for luxury Taxi with parameters.
    TaxiLuxury(int taxiId, char colorOfTaxi1, char manufacturerOfTaxi1);

    //Get the speed.
    int getSpeed() const;

    //Set the speed.
    void setSpeed(int speed1);
};


#endif //EX2_TAXILUXURY_H
