#pragma once

#include <vector>
#include <sys/epoll.h>

using namespace std;

class Epoll {

private:

    int epollFd;

public:

    Epoll();

    ~Epoll();

    bool create();

    bool add(int fd);

    bool remove(int fd);
    int getFd() const;
    vector<epoll_event> wait();

};