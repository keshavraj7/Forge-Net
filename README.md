# ForgeNet

**A Lightweight HTTP Server Built from Scratch in Modern C++**

ForgeNet is a lightweight HTTP server developed in C++17 using low-level POSIX socket programming. It explores the fundamentals of networking, event-driven I/O, concurrency, and HTTP request handling without relying on external web frameworks.

The project is designed to understand how HTTP servers work internally, from accepting TCP connections to parsing requests and generating responses.

## Features

- **Socket Programming:** TCP server implementation using POSIX sockets.
- **RAII Socket Management:** Automatic resource management with C++ move semantics and deleted copy operations.
- **Non-Blocking I/O:** Non-blocking sockets using `fcntl()`.
- **Event-Driven Architecture:** I/O event monitoring using Linux `epoll`.
- **Multithreading:** Custom thread pool for concurrent request processing.
- **HTTP Request Parser:** Parses HTTP methods, paths, versions, headers, and request bodies.
- **HTTP Response Builder:** Constructs HTTP responses with appropriate status codes and headers.
- **Routing System:** Supports custom GET and POST route handlers.
- **Static File Server:** Serves static files such as HTML pages.
- **MIME Type Detection:** Determines content types based on file extensions.
- **Directory Traversal Protection:** Prevents unsafe file path access.
- **Form Parsing:** Parses URL-encoded form submissions.
- **Socket Configuration:** Supports `SO_REUSEADDR` for easier server restarts.
- **Logging:** Basic connection, request, and server event logging.

## Tech Stack

| Technology | Purpose |
|---|---|
| C++17 | Core implementation |
| POSIX Sockets | TCP communication |
| Linux epoll | Event-driven I/O |
| Multithreading | Concurrent request processing |
| CMake | Build configuration |
| Linux / WSL | Development and execution environment |

## Architecture

```text
                 HTTP Client
                      |
                      v
                TCP Connection
                      |
                      v
                Socket Layer
                      |
                      v
                  epoll
              Event Monitoring
                      |
                      v
                 Thread Pool
                      |
                      v
               HTTP Request
                   Parser
                      |
                      v
                   Router
                 /       \
                /         \
          GET / POST    Static Files
             Routes      File Server
                \         /
                 \       /
                      |
                      v
               HTTP Response
                   Builder
                      |
                      v
                Socket Send
                      |
                      v
                  Client
```

## Project Structure

```text
ForgeNet/
│
├── CMakeLists.txt
│
├── include/
│   ├── Server.h
│   ├── Socket.h
│   ├── HttpRequest.h
│   ├── HttpResponse.h
│   ├── Router.h
│   ├── FileServer.h
│   ├── MimeType.h
│   ├── PathUtils.h
│   ├── ThreadPool.h
│   ├── Epoll.h
│   ├── FormParser.h
│   └── Logger.h
│
├── src/
│   ├── main.cpp
│   ├── Server.cpp
│   ├── Socket.cpp
│   ├── HttpRequest.cpp
│   ├── HttpResponse.cpp
│   ├── Router.cpp
│   ├── FileServer.cpp
│   ├── MimeType.cpp
│   ├── PathUtils.cpp
│   ├── ThreadPool.cpp
│   ├── Epoll.cpp
│   └── FormParser.cpp
│
├── public/
│   └── index.html
│
└── build/
```

## Getting Started

### Prerequisites

- Linux or WSL
- C++17 compatible compiler (GCC or Clang)
- CMake 3.16 or newer
- POSIX-compatible environment with Linux `epoll` support

### 1. Clone the repository

```bash
git clone https://github.com/YOUR_USERNAME/ForgeNet.git
cd ForgeNet
```

### 2. Build the project

```bash
cmake -S . -B build
cmake --build build
```

### 3. Run the server

Run the executable from the project root so that the relative `public/` directory can be found.

```bash
./build/ForgeNet
```

The server starts on port `8080`.

### 4. Send requests

**Home page**

```bash
curl -i http://localhost:8080/
```

**About route**

```bash
curl -i http://localhost:8080/about
```

**POST login route**

```bash
curl -X POST \
     -d "username=Keshav" \
     http://localhost:8080/login
```

Example response:

```text
Welcome Keshav
```

## Benchmarking

ForgeNet can be benchmarked using ApacheBench (`ab`) and `wrk`.

Install the tools on Ubuntu/WSL:

```bash
sudo apt update
sudo apt install apache2-utils wrk
```

**ApacheBench**

```bash
ab -n 10000 -c 100 http://127.0.0.1:8080/
```

**wrk**

```bash
wrk -t4 -c100 -d30s http://127.0.0.1:8080/
```

Record the following metrics after successful runs:

| Metric | Result |
|---|---|
| Requests per second | To be measured |
| Average latency
