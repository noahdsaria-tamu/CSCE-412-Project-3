#include <iostream>
#include "request.h"

int main() {
    Request req("192.168.1.1", "192.168.1.2", 50, 'P');
    Request req_rand;

    req.displayRequest();
    req_rand.displayRequest();

    return 0;

}