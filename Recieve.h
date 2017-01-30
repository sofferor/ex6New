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

    bool isManufacturer(char c);

    bool isColor(char c);

    static bool isMaritalStatus(char c);

    bool isInRangeOfGrid(int num);

    //static vector<string> split(const string &s, const string &dell);

    static bool isDouble(const string& s);

    template<typename Out>
    static void split(const std::string &s, char delim, Out result);

    static vector<std::string> split(const std::string &s, char delim);
public:
    Recieve();

    Recieve(TaxiCenter *taxiCenter);

    virtual ~Recieve();

    void printInvalid();

    Matrix2D* recieveMatrix();

    Trip* recieveTrip();

    Taxi* recieveTaxi();

    static bool isInt(const string& s);

    static Driver* recieveDriver();
};


#endif //EX6_RECIEVE_H
