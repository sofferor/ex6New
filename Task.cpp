//
// Created by haim on 26/01/17.
//

#include "Task.h"

Task::Task(void (*pFunction)(void *), void *arg) : function(pFunction), arg(arg) {
    // TODO Auto-generated constructor stub
}

void Task::execute() {
    (*function)(arg);
}

Task::~Task() {
    // TODO Auto-generated destructor stub
}
