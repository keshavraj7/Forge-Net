#pragma once

#include <string>

using namespace std;

class Socket {
private:
    int socketFd;

public:
    Socket();
    Socket(int fd);
    ~Socket();
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    Socket(Socket&& other) noexcept;
    Socket& operator=(Socket&& other) noexcept;

    bool create();
    bool bind(int port);
    bool listen(int backlog = 5);

    Socket accept();
    int acceptFd();
    int receive(char* buffer, int size);
    bool send(const string& message);
  bool isValid() const;
    int getFd() const;
};