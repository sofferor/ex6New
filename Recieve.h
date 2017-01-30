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

    bool isManufacturer(char c);

    bool isColor(char c);

    bool isInRangeOfGrid(int num);

    static vector<string> split(const string &s, const string &dell);

    static bool checkIfStringIsNumber(const string &s);
public:
    Recieve();

    virtual ~Recieve();

    void printInvalid();

    Matrix2D* recieveMatrix();

    Trip* recieveTrip();

    Taxi* recieveTaxi();
};


#endif //EX6_RECIEVE_H
