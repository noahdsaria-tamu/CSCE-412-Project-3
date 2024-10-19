#include "request.h"
#include <iostream>

// Constructor implementation
Request::Request(const std::string& ipIn, const std::string& ipOut)
    : ipIn(ipIn), ipOut(ipOut) {}

// Getter implementations
std::string Request::getIpIn() const {
    return ipIn;
}

std::string Request::getIpOut() const {
    return ipOut;
}
