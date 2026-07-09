cmake_minimum_required(VERSION 3.16)

project(ForgeNet)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(ForgeNet
    src/main.cpp
    src/Socket.cpp
    src/Server.cpp
    src/HttpRequest.cpp
    src/HttpResponse.cpp
    src/Router.cpp
    src/FileServer.cpp
    src/MimeType.cpp
    src/PathUtils.cpp
    src/ThreadPool.cpp
    src/Epoll.cpp
    src/FormParser.cpp
)

target_compile_options(ForgeNet PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)