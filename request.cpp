#include "request.h"
#include <random>
#include <sstream>

// Helper function to generate a random IP address
std::string generateRandomIp() {
    std::random_device rd;  // Seed generator
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dist(0, 255); // Range for octets

    // Generate four random octets
    int octet1 = dist(gen);
    int octet2 = dist(gen);
    int octet3 = dist(gen);
    int octet4 = dist(gen);

    // Convert the octets to a string in the format X.X.X.X
    std::stringstream ss;
    ss << octet1 << "." << octet2 << "." << octet3 << "." << octet4;
    
    return ss.str();
}

// Constructor implementation
Request::Request(const std::string& ipIn, const std::string& ipOut)
    : ipIn(ipIn), ipOut(ipOut) {}

// Constructor implementation with random IP addresses
Request::Request()
    : ipIn(generateRandomIp()), ipOut(generateRandomIp()) {}

// Getter implementations
std::string Request::getIpIn() const {
    return ipIn;
}

std::string Request::getIpOut() const {
    return ipOut;
}
