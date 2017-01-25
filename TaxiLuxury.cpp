
#include "TaxiLuxury.h"

//Constructor for luxury Taxi with parameters.
TaxiLuxury::TaxiLuxury(int taxiId, int numOfKilometers, int tarrif,
                           color colorOfTaxi, manufacturer manufacturerOfTaxi)
        : Taxi(taxiId, numOfKilometers, tarrif, colorOfTaxi, manufacturerOfTaxi){
    speed = 2;
}

//Constructor for luxury Taxi with parameters.
TaxiLuxury::TaxiLuxury(int taxiId, char colorOfTaxi1, char manufacturerOfTaxi1)
        : Taxi(taxiId, colorOfTaxi1, manufacturerOfTaxi1) {
    speed = 2;
}

//Get the speed.
int TaxiLuxury::getSpeed() const {
    return speed;
}

//Set the speed.
void TaxiLuxury::setSpeed(int speed1) {
    speed = speed1;
}

BOOST_CLASS_EXPORT(TaxiLuxury)