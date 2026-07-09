#include "HttpRequest.h"

#include <sstream>

using namespace std;

bool HttpRequest::parse(const string& request) {

    method.clear();
    path.clear();
    version.clear();
    body.clear();
    headers.clear();

    stringstream ss(request);

    ss >> method;
    ss >> path;
    ss >> version;

    string line;

    getline(ss, line);

    while(getline(ss, line)) {

        if(line == "\r" || line.empty())
            break;

        if(line.back() == '\r')
            line.pop_back();

        size_t pos = line.find(':');

        if(pos == string::npos)
            continue;

        string key = line.substr(0, pos);
        string value = line.substr(pos + 1);

        if(!value.empty() && value.front() == ' ')
            value.erase(0, 1);

        headers[key] = value;
    }

    while(getline(ss, line)) {

        if(line.back() == '\r')
            line.pop_back();

        body += line;

        if(!ss.eof())
            body += '\n';
    }

    return !method.empty();
}
string HttpRequest::getMethod() const {
    return method;
}

string HttpRequest::getPath() const {
    return path;
}

string HttpRequest::getVersion() const {
    return version;
}

string HttpRequest::getHeader(const string& key) const {

    auto it = headers.find(key);

    if(it == headers.end())
        return "";

    return it->second;
}
string HttpRequest::getBody() const {
    return body;
}