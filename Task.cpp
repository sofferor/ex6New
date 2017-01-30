
#include "Task.h"

//constructor.
Task::Task(void (*pFunction)(void *), void *arg) : function(pFunction), arg(arg) {
    // TODO Auto-generated constructor stub
}

//execute.
void Task::execute() {
    (*function)(arg);
}

//distractor.
Task::~Task() {
    // TODO Auto-generated destructor stub
}
