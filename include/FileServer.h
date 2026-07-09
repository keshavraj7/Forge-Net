#pragma once

#include <string>

#include "HttpResponse.h"

using namespace std;

class FileServer {
public:
    static HttpResponse serve(const string& path);
};