#include "Router.h"
#include "FileServer.h"
#include "PathUtils.h"
using namespace std;

void Router::get(const string& path,
                 function<HttpResponse(const HttpRequest&)> handler) {

    routes["GET"][path] = handler;
}
void Router::post(
    const string& path,
    function<HttpResponse(const HttpRequest&)> handler) {

    routes["POST"][path] = handler;
}
HttpResponse Router::route(const HttpRequest& request) {
    if(!PathUtils::isSafe(request.getPath())) {

    HttpResponse response;

    response.setStatus(403, "Forbidden");
    response.setBody("403 Forbidden");
    return response;
}
   auto methodIt = routes.find(request.getMethod());

if(methodIt != routes.end()) {

    auto pathIt = methodIt->second.find(request.getPath());

    if(pathIt != methodIt->second.end())
        return pathIt->second(request);
}

    string filePath = "public";

    if(request.getPath() == "/")
        filePath += "/index.html";
    else
        filePath += request.getPath();

    return FileServer::serve(filePath);
}