#pragma once

#include "Socket.h"
#include "Router.h"
#include "FileServer.h"
#include "ThreadPool.h"
#include "Epoll.h"
class Server {
private:
    Socket serverSocket;
    Epoll epoll;
    int port;
    Router router;
    int acceptClientFd();
    void handleClient(int clientFd);
    
public:
    Server(int port);

    bool start();
};