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
    TaxiCenter* taxiCenter;

    // is Manufacturer
    bool isManufacturer(char c);

    //is Color
    bool isColor(char c);

    // is Marital Status
    static bool isMaritalStatus(char c);

    //is In Range Of Grid
    bool isInRangeOfGrid(int num);

    //static vector<string> split(const string &s, const string &dell);

    //is Double
    static bool isDouble(const string& s);

    template<typename Out>
    static void split(const std::string &s, char delim, Out result);

    static vector<std::string> split(const std::string &s, char delim);
public:
    // constructor.
    Recieve();

    // constructor.
    Recieve(TaxiCenter *taxiCenter);

    // destructor
    virtual ~Recieve();

    // print Invalid
    void printInvalid();

    // recieve Matrix
    Matrix2D* recieveMatrix();

    //recieve Trip
    Trip* recieveTrip();

    //recieve Taxi
    Taxi* recieveTaxi();

    //is Int
    static bool isInt(const string& s);

    // recieve Driver
    static Driver* recieveDriver();
};


#endif //EX6_RECIEVE_H
