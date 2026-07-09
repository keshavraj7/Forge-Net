#include "HttpResponse.h"

using namespace std;

HttpResponse::HttpResponse()
    : statusCode(200), statusMessage("OK") {

    headers["Server"] = "ForgeNet";
    headers["Connection"] = "close";
    headers["Content-Type"] = "text/plain";
}

void HttpResponse::setStatus(int code, const string& message) {
    statusCode = code;
    statusMessage = message;
}

void HttpResponse::setHeader(const string& key, const string& value) {
    headers[key] = value;
}

void HttpResponse::setBody(const string& content) {
    body = content;
}

string HttpResponse::build() const {

    headers.at("Server");

    string response;

    response += "HTTP/1.1 ";
    response += to_string(statusCode);
    response += " ";
    response += statusMessage;
    response += "\r\n";

    for(const auto& [key, value] : headers)
        response += key + ": " + value + "\r\n";

    response += "Content-Length: ";
    response += to_string(body.size());
    response += "\r\n";

    response += "\r\n";

    response += body;

    return response;
}