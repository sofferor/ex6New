#include "Matrix2D.h"
#include "TaxiCenter.h"
#include <iostream>
#include "Matrix2D.h"
#include "Trip.h"
#include "Taxi.h"
#include "TaxiStandard.h"
#include "TaxiLuxury.h"

using namespace std;

#ifndef EX6_RECIEVE_H
#define EX6_RECIEVE_H


class Recieve {
private:
    Matrix2D* matrix2D;
    char comma;
    bool legal;

    bool isManufacturer(int num);

    bool isColor(int num);
public:
    Recieve(bool legal);

    virtual ~Recieve();

    void printInvalid();

    Matrix2D* recieveMatrix();

    Trip* recieveTrip();

    Taxi* recieveTaxi();
};


#endif //EX6_RECIEVE_H
