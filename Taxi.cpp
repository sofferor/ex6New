
#include "Taxi.h"

using namespace std;


//Constructor for Taxi with parameters.
Taxi::Taxi(int taxiId1, int numOfKilometers1, int tarrif1, color colorOfTaxi1,
           manufacturer manufacturerOfTaxi1) {
    taxiId = taxiId1;
    numOfKilometers = numOfKilometers1;
    tarrif = tarrif1;
    colorOfTaxi = colorOfTaxi1;
    manufacturerOfTaxi = manufacturerOfTaxi1;
}
//Constructor for Taxi with parameters.
Taxi::Taxi(int taxiId, char colorOfTaxi1, char manufacturerOfTaxi1) : taxiId(taxiId) {

    taxiColor['R'] = RED;
    taxiColor['B'] = BLUE;
    taxiColor['G'] = GREEN;
    taxiColor['P'] = PINK;
    taxiColor['W'] = WHITE;

    taxiManufacturer['H'] = HONDA;
    taxiManufacturer['S'] = SUBARO;
    taxiManufacturer['T'] = TESLA;
    taxiManufacturer['F'] = FIAT;

    colorOfTaxi = taxiColor[colorOfTaxi1];
    manufacturerOfTaxi = taxiManufacturer[manufacturerOfTaxi1];

}

//Get taxi id.
int Taxi::getTaxiId() const {
    return taxiId;
}

//Get the number of kilometers.
int Taxi::getNumOfKilometers() const {
    return numOfKilometers;
}

//Get the tarrif.
int Taxi::getTarrif() const {
    return tarrif;
}

//Get the color.
color Taxi::getColorOfTaxi() const {
    return colorOfTaxi;
}

//Get the manufacture.
manufacturer Taxi::getManufacturerOfTaxi() const {
    return manufacturerOfTaxi;
}

//Set the taxi id.
void Taxi::setTaxiId(int taxiId) {
    Taxi::taxiId = taxiId;
}

//Set the number of kilometers.
void Taxi::setNumOfKilometers(int numOfKilometers) {
    Taxi::numOfKilometers = numOfKilometers;
}

//Set the tarrif.
void Taxi::setTarrif(int tarrif) {
    Taxi::tarrif = tarrif;
}

//Set the color.
void Taxi::setColorOfTaxi(color colorOfTaxi) {
    Taxi::colorOfTaxi = colorOfTaxi;
}

//Set the manufacture.
void Taxi::setManufacturerOfTaxi(manufacturer manufacturerOfTaxi) {
    Taxi::manufacturerOfTaxi = manufacturerOfTaxi;
}

//Add the number of kilometers.
void Taxi::addNumOfKilometers(int numOfKilometers) {
    Taxi::numOfKilometers += numOfKilometers;
}