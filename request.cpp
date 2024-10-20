#include "request.h"
#include <random>
#include <sstream>
#include <iostream>

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

// Helper function to generate a random time
int generateRandomTime() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100); // Example range for time
    return dist(gen);
}

// Helper function to generate a random job type
char generateRandomJobType() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1); // Range for two job types
    return dist(gen) == 0 ? 'P' : 'S'; // Randomly choose between 'P' and 'S'
}

// Constructor implementation
Request::Request(const std::string& ipIn, const std::string& ipOut, int time, char jobType)
    : ipIn(ipIn), ipOut(ipOut), time(time), jobType(jobType) {}

// Default constructor implementation with random parameters
Request::Request()
    : ipIn(generateRandomIp()), ipOut(generateRandomIp()), time(generateRandomTime()), jobType(generateRandomJobType()) {}

// Getter implementations
std::string Request::getIpIn() const {
    return ipIn;
}

std::string Request::getIpOut() const {
    return ipOut;
}

int Request::getTime() const {
    return time;
}

char Request::getJobType() const {
    return jobType;
}

// Display request information

void Request::displayRequest() const {
    std::cout << "Request IP in: " << ipIn << std::endl;
    std::cout << "Request IP out: " << ipOut << std::endl;
    std::cout << "Request time: " << time << std::endl;
    std::cout << "Request job type: " << jobType << std::endl;
}