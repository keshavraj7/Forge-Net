#include "Server.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include <utility>
#include <iostream>
#include <thread>
#include "FileServer.h"
#include "FormParser.h"
using namespace std;

Server::Server(int port) : port(port){
      router.get("/", [](const HttpRequest&) {
    return FileServer::serve("public/index.html");
});
router.post("/login", [](const HttpRequest& request) {

    auto form = FormParser::parse(request.getBody());

    HttpResponse response;

    string body = "Welcome " + form["username"];

    response.setBody(body);

    return response;
});
    router.get("/about", [](const HttpRequest& request) {

        HttpResponse response;
        response.setBody("About ForgeNet");

        return response;
    });
}

int Server::acceptClientFd() {
   return serverSocket.acceptFd();
}

void Server::handleClient(int clientFd) {
  Socket clientSocket(clientFd);
    char buffer[1024]{};

    int bytes = clientSocket.receive(buffer, sizeof(buffer));

    if(bytes <= 0)
        return;

    HttpRequest request;

    request.parse(buffer);

    cout << "Method : " << request.getMethod() << '\n';
    cout << "Path   : " << request.getPath() << '\n';
    cout << "Version: " << request.getVersion() << '\n';
  cout << "Host        : " << request.getHeader("Host") << '\n';
cout << "User-Agent  : " << request.getHeader("User-Agent") << '\n';
cout << "Connection  : " << request.getHeader("Connection") << '\n';
    HttpResponse response = router.route(request);
clientSocket.send(response.build());
}

bool Server::start() {
  if(!epoll.create())
    return false;
    if(!serverSocket.create())
        return false;

    if(!serverSocket.bind(port))
        return false;

    if(!serverSocket.listen())
        return false;
    if(!epoll.add(serverSocket.getFd()))
    return false;
    cout << "Server listening on port " << port << '\n';

    while(true) {
    vector<epoll_event> events = epoll.wait();
    for(const auto& event : events) {
        if(event.data.fd == serverSocket.getFd()) {
            int clientFd = serverSocket.acceptFd();
            if(clientFd != -1)
                epoll.add(clientFd);
        }
        else {
            handleClient(event.data.fd);
        }
    }
}
    return true;
}