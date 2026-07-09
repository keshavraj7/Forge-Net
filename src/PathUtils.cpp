#include "PathUtils.h"

using namespace std;

bool PathUtils::isSafe(const string& path) {

    if(path.find("..") != string::npos)
        return false;

    if(path.find('\\') != string::npos)
        return false;

    return true;
}