#include <iostream>
#include "request.h"
#include "webserver.h"

int main() {
    Request req("192.168.1.1", "192.168.1.2", 2000000, 'P');
    Request req_rand;

    WebServer server1(1);
    WebServer server2(2);

    server1.processRequest(req);
    server2.processRequest(req_rand);

    return 0;

}