//
// Created by or on 02/01/17.
//

#ifndef PRACTICE6_CLOCK_H
#define PRACTICE6_CLOCK_H


/**
 * Clock class.
 * for the time.
 */
class Time {
private:
    int time;

public:
    //Constructor for clock.
    Time();

    //deconstructor for clock.
    virtual ~Time() {};

    //Get the time.
    int getTime();

    //Update the time.
    void updateTime();
};


#endif //PRACTICE6_CLOCK_H
