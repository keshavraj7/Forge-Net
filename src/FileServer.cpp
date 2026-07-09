#include "FileServer.h"
#include "MimeType.h"
#include <fstream>
#include <sstream>

using namespace std;

HttpResponse FileServer::serve(const string& path) {

    HttpResponse response;

    ifstream file(path, ios::binary);

    if(!file.is_open()) {

    ifstream notFound("public/404.html", ios::binary);

    if(notFound.is_open()) {

        ostringstream buffer;
        buffer << notFound.rdbuf();

        response.setStatus(404, "Not Found");
        response.setHeader("Content-Type", "text/html");
        response.setBody(buffer.str());

        return response;
    }

    response.setStatus(404, "Not Found");
    response.setBody("404 Not Found");

    return response;
}

    ostringstream buffer;
    buffer << file.rdbuf();

    response.setHeader("Content-Type", MimeType::get(path));
    response.setBody(buffer.str());

    return response;
}