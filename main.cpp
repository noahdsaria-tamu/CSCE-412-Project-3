#include <iostream>
#include "request.h"

int main() {
    Request req("192.168.1.1", "192.168.1.2", 50, 'P');
    Request req_rand;

    std::cout << "Request IP in: " << req_rand.getIpIn() << std::endl;
    std::cout << "Request IP out: " << req_rand.getIpOut() << std::endl;
    std::cout << "Request time: " << req_rand.getTime() << std::endl;
    std::cout << "Request job type: " << req_rand.getJobType() << std::endl;

    return 0;

}