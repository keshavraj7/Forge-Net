#pragma once

#include <string>
#include <unordered_map>

using namespace std;

class HttpRequest {
private:
    string method;
    string path;
    string version;
    string body;
    unordered_map<string, string> headers;

public:
    bool parse(const string& request);

    string getMethod() const;
    string getPath() const;
    string getVersion() const;
    string getBody() const;
    string getHeader(const string& key) const;
};