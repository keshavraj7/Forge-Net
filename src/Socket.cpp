#include "Socket.h"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

Socket::Socket() : socketFd(-1) {}

Socket::Socket(int fd) : socketFd(fd) {}

Socket::Socket(Socket&& other) noexcept : socketFd(other.socketFd) {
    other.socketFd = -1;
}

Socket& Socket::operator=(Socket&& other) noexcept {
    if(this != &other) {
        if(socketFd != -1)
            close(socketFd);

        socketFd = other.socketFd;
        other.socketFd = -1;
    }

    return *this;
}

Socket::~Socket() {
    if(socketFd != -1)
        close(socketFd);
}

bool Socket::create() {
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if(socketFd == -1) {
        cerr << "Socket creation failed\n";
        return false;
    }

    return true;
}
bool Socket::isValid() const {
    return socketFd != -1;
}
bool Socket::bind(int port) {
    sockaddr_in serverAddr{};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if(::bind(socketFd, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "Bind failed\n";
        return false;
    }

    return true;
}

bool Socket::listen(int backlog) {
    if(::listen(socketFd, backlog) == -1) {
        cerr << "Listen failed\n";
        return false;
    }

    return true;
}

Socket Socket::accept() {
    int clientFd = ::accept(socketFd, nullptr, nullptr);

    if(clientFd == -1) {
        cerr << "Accept failed\n";
        return Socket();
    }

    return Socket(clientFd);
}
int Socket::acceptFd() {

    int clientFd = ::accept(socketFd, nullptr, nullptr);

    if(clientFd == -1)
        cerr << "Accept failed\n";

    return clientFd;
}
int Socket::receive(char* buffer, int size) {
    int bytes = ::recv(socketFd, buffer, size, 0);

    if(bytes == -1)
        cerr << "Receive failed\n";

    return bytes;
}

bool Socket::send(const string& message) {
    if(::send(socketFd, message.c_str(), message.size(), 0) == -1) {
        cerr << "Send failed\n";
        return false;
    }

    return true;
}

int Socket::getFd() const {
    return socketFd;
}