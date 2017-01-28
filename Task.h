//
// Created by haim on 26/01/17.
//

#ifndef EX6_TASK_H
#define EX6_TASK_H


class Task {
private:
    void (*function)(void*);
    void* arg;

public:
    Task(void (*pFunction)(void*), void* arg);
    void execute();

    virtual ~Task();
};


#endif //EX6_TASK_H
