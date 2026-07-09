#pragma once

#include <string>
#include <unordered_map>

using namespace std;

class HttpResponse {
private:
    int statusCode;
    string statusMessage;
    string body;
    unordered_map<string, string> headers;

public:
    HttpResponse();

    void setStatus(int code, const string& message);
    void setHeader(const string& key, const string& value);
    void setBody(const string& content);

    string build() const;
};