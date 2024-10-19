#include <iostream>
#include "request.h"

int main() {
    Request req("192.168.1.1", "192.168.1.2");
    Request req_rand;

    std::cout << "Request IP in: " << req_rand.getIpIn() << std::endl;
    std::cout << "Request IP out: " << req_rand.getIpOut() << std::endl;

    return 0;

}