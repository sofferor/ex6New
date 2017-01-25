#include "Time.h"

//Constructor for clock.
Time::Time() {
    time = 0;
}

//Get the time.
int Time::getTime() {
    return time;
}

//Update the time.
void Time::updateTime() {
    time++;
}
