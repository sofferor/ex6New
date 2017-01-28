//
// Created by haim on 26/01/17.
//

#include <zconf.h>
#include "ThreadsPool.h"

void *startTasks(void *arg) {
    ThreadsPool* tp = (ThreadsPool*) arg;
    tp->runTasks();
    return NULL;
}

ThreadsPool::ThreadsPool(int numOfThreads) : numOfThreads(numOfThreads) {
    // TODO Auto-generated constructor stub

    stop = false;
    threads = new pthread_t[numOfThreads];

    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < numOfThreads; i++) {
        pthread_create(threads + i, NULL, startTasks, this);
    }
}

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

void ThreadsPool::emptyPool() {
    stop = true;
}

void ThreadsPool::addTask(Task *task) {
    tasks.push(task);
}

ThreadsPool::~ThreadsPool() {
    delete[] threads;
}
