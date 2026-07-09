#include "Epoll.h"

#include <iostream>
#include <unistd.h>

using namespace std;

Epoll::Epoll() : epollFd(-1) {}

Epoll::~Epoll() {
    if(epollFd != -1)
        close(epollFd);
}

bool Epoll::create() {

    epollFd = epoll_create1(0);

    if(epollFd == -1) {
        cerr << "epoll_create1 failed\n";
        return false;
    }

    return true;
}

bool Epoll::add(int fd) {

    epoll_event event{};

    event.events = EPOLLIN;
    event.data.fd = fd;

    if(epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &event) == -1) {
        cerr << "Failed to add fd to epoll\n";
        return false;
    }

    return true;
}

bool Epoll::remove(int fd) {

    if(epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, nullptr) == -1) {
        cerr << "Failed to remove fd from epoll\n";
        return false;
    }

    return true;
}

vector<epoll_event> Epoll::wait() {

    vector<epoll_event> events(64);

    int ready = epoll_wait(epollFd,
                           events.data(),
                           events.size(),
                           -1);

    if(ready == -1) {
        cerr << "epoll_wait failed\n";
        return {};
    }

    events.resize(ready);

    return events;
}
int Epoll::getFd() const {
    return epollFd;
}