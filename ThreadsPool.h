//
// Created by haim on 26/01/17.
//

#ifndef EX6_THREADSPOOL_H
#define EX6_THREADSPOOL_H

#include <iostream>
#include <queue>
#include "Task.h"

using namespace std;

//class for thread pool.
class ThreadsPool {
private:
    queue<Task*> tasks;
    int numOfThreads;
    pthread_t * threads;
    bool stop;
    pthread_mutex_t lock;

public:
    //Constructor
    ThreadsPool(int numOfThreads);

    //static void* startTasks(void *arg);

    //run tasks.
    void runTasks();

    //empty pool.
    void emptyPool();

    //add task.
    void addTask(Task* task);

    //join.
    void join();

    //distractor.
    virtual ~ThreadsPool();
};


#endif //EX6_THREADSPOOL_H
