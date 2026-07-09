#pragma once

#include <unordered_map>
#include <functional>

#include "HttpRequest.h"
#include "HttpResponse.h"

using namespace std;

class Router {
private:
    unordered_map<string,
    unordered_map<string,
        function<HttpResponse(const HttpRequest&)>>> routes;

public:
    void get(const string& path, function<HttpResponse(const HttpRequest&)> handler);
    void post(const string& path,
          function<HttpResponse(const HttpRequest&)> handler);
    HttpResponse route(const HttpRequest& request);
};