#include "Server.h"

using namespace std;

int main() {
    Server server(8080);

    if(!server.start())
        return 1;

    return 0;
}