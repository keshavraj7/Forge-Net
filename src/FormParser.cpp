#include "FormParser.h"

#include <sstream>

using namespace std;

unordered_map<string, string> FormParser::parse(const string& body) {

    unordered_map<string, string> form;

    stringstream ss(body);
    string pair;

    while(getline(ss, pair, '&')) {

        size_t pos = pair.find('=');

        if(pos == string::npos)
            continue;

        string key = pair.substr(0, pos);
        string value = pair.substr(pos + 1);

        form[key] = value;
    }

    return form;
}