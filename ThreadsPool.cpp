//
// Created by haim on 26/01/17.
//

#include <zconf.h>
#include "ThreadsPool.h"

//start tasks.
void *startTasks(void *arg) {
    ThreadsPool* tp = (ThreadsPool*) arg;
    tp->runTasks();
    return NULL;
}

//Constructor
ThreadsPool::ThreadsPool(int numOfThreads) : numOfThreads(numOfThreads) {
    // TODO Auto-generated constructor stub

    stop = false;
    threads = new pthread_t[numOfThreads];

    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < numOfThreads; i++) {
        pthread_create(threads + i, NULL, startTasks, this);
    }
}

//run tasks.
void ThreadsPool::runTasks() {
    while (!stop) {
        pthread_mutex_lock(&lock);
        if (tasks.empty()) {
            pthread_mutex_unlock(&lock);
            sleep(1);
        } else {
            Task* task = tasks.front();
            tasks.pop();
            pthread_mutex_unlock(&lock);
            task->execute();
        }
    }
    pthread_exit(NULL);
}

//empty pool.
void ThreadsPool::emptyPool() {
    stop = true;
}

//add task.
void ThreadsPool::addTask(Task *task) {
    tasks.push(task);
}

//distractor.
ThreadsPool::~ThreadsPool() {
    pthread_mutex_destroy(&lock);
    delete[] threads;
}

//join.
void ThreadsPool::join() {
    for (int i = 0; i < numOfThreads; ++i) {
        pthread_join(threads[i], NULL);
    }
}
