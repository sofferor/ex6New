//
// Created by haim on 26/01/17.
//

#ifndef EX6_THREADSPOOL_H
#define EX6_THREADSPOOL_H

#include <iostream>
#include <queue>
#include "Task.h"

using namespace std;

class ThreadsPool {
private:
    queue<Task*> tasks;
    int numOfThreads;
    pthread_t * threads;
    bool stop;
    pthread_mutex_t lock;

public:
    ThreadsPool(int numOfThreads);
    //static void* startTasks(void *arg);
    void runTasks();
    void emptyPool();
    void addTask(Task* task);
    void join();

    virtual ~ThreadsPool();
};


#endif //EX6_THREADSPOOL_H
