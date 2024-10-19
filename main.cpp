#include <iostream>
#include "request.h"

int main() {
    Request req("192.168.1.1", "192.168.1.2");

    std::cout << "Request IP in: " << req.getIpIn() << std::endl;
    std::cout << "Request IP out: " << req.getIpOut() << std::endl;

    return 0;

}