//
// Created by haim on 26/01/17.
//

#ifndef EX6_TASK_H
#define EX6_TASK_H

//class for task.
class Task {
private:
    void (*function)(void*);
    void* arg;

public:
    //constructor.
    Task(void (*pFunction)(void*), void* arg);

    //execute.
    void execute();

    //distractor.
    virtual ~Task();
};


#endif //EX6_TASK_H
