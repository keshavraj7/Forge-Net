#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

class ThreadPool {

private:

    vector<thread> workers;

    queue<function<void()>> tasks;

    mutex queueMutex;

    condition_variable condition;

    bool stop;

public:

    ThreadPool(size_t threads);

    ~ThreadPool();

    void enqueue(function<void()> task);

};