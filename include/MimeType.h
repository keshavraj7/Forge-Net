#pragma once

#include <string>

using namespace std;

class MimeType {
public:
    static string get(const string& path);
};