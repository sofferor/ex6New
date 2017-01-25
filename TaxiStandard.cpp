
#include "TaxiStandard.h"

using namespace std;

//Constructor for standard Taxi with parameters.
TaxiStandard::TaxiStandard(int taxiId, int numOfKilometers, int tarrif,
                           color colorOfTaxi, manufacturer manufacturerOfTaxi)
        : Taxi(taxiId, numOfKilometers, tarrif, colorOfTaxi, manufacturerOfTaxi)
{
    speed = 1;
}

//Constructor for standard Taxi with parameters.
TaxiStandard::TaxiStandard(int taxiId, char colorOfTaxi1,
                           char manufacturerOfTaxi1) : Taxi(taxiId,
                                                            colorOfTaxi1,
                                                            manufacturerOfTaxi1)
{
    speed = 1;
}


//Get the speed.
int TaxiStandard::getSpeed() const {
    return speed;
}

//Set the speed.
void TaxiStandard::setSpeed(int speed1) {
    speed = speed1;
}

BOOST_CLASS_EXPORT(TaxiStandard)