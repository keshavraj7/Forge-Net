#include "MimeType.h"

using namespace std;

string MimeType::get(const string& path) {

    size_t pos = path.find_last_of('.');

    if(pos == string::npos)
        return "application/octet-stream";

    string extension = path.substr(pos);

    if(extension == ".html")
        return "text/html";

    if(extension == ".css")
        return "text/css";

    if(extension == ".js")
        return "application/javascript";

    if(extension == ".png")
        return "image/png";

    if(extension == ".jpg" || extension == ".jpeg")
        return "image/jpeg";

    if(extension == ".svg")
        return "image/svg+xml";

    if(extension == ".json")
        return "application/json";

    if(extension == ".txt")
        return "text/plain";

    return "application/octet-stream";
}