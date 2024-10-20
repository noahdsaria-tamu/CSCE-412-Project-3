#include "request.h"
#include <random>
#include <sstream>
#include <iostream>

// Helper function to generate a random IP address
/**
 * @brief Generates a random IPv4 address.
 * 
 * This function generates a random IPv4 address in the format X.X.X.X,
 * where each X is a random integer between 0 and 255.
 * 
 * @return A string representing the randomly generated IPv4 address.
 */
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

/**
 * @brief Generates a random processing time for the request.
 * 
 * This function generates a random integer between 1 and 20 (inclusive)
 * to represent the processing time required for a request.
 * 
 * @return A randomly generated integer representing the processing time.
 */
int generateRandomTime() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 20); // Example range for time
    return dist(gen);
}

/**
 * @brief Generates a random job type for the request.
 * 
 * This function randomly selects between two job types: 'P' (Processing) or 'S' (Streaming).
 * 
 * @return A randomly chosen character representing the job type ('P' or 'S').
 */
char generateRandomJobType() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1); // Range for two job types
    return dist(gen) == 0 ? 'P' : 'S'; // Randomly choose between 'P' and 'S'
}

/**
 * @brief Constructs a Request object with the provided parameters.
 * 
 * @param ipIn The incoming IP address.
 * @param ipOut The outgoing IP address.
 * @param time The time required to process the request.
 * @param jobType The type of the job ('P' for processing, 'S' for streaming).
 */
Request::Request(const std::string& ipIn, const std::string& ipOut, int time, char jobType)
    : ipIn(ipIn), ipOut(ipOut), time(time), jobType(jobType) {}

/**
 * @brief Constructs a Request object with randomly generated parameters.
 * 
 * This constructor generates random values for the incoming/outgoing IP addresses,
 * the processing time, and the job type.
 */
Request::Request()
    : ipIn(generateRandomIp()), ipOut(generateRandomIp()), time(generateRandomTime()), jobType(generateRandomJobType()) {}

/**
 * @brief Gets the incoming IP address of the request.
 * @return The incoming IP address as a string.
 */
std::string Request::getIpIn() const {
    return ipIn;
}

/**
 * @brief Gets the outgoing IP address of the request.
 * @return The outgoing IP address as a string.
 */
std::string Request::getIpOut() const {
    return ipOut;
}

/**
 * @brief Gets the time required to process the request.
 * @return The processing time as an integer.
 */
int Request::getTime() const {
    return time;
}

/**
 * @brief Gets the job type of the request.
 * @return The job type as a character ('P' for processing, 'S' for streaming).
 */
char Request::getJobType() const {
    return jobType;
}

/**
 * @brief Displays the details of the request.
 * 
 * This function prints the incoming IP, outgoing IP, processing time, 
 * and job type of the request to the console.
 */
void Request::displayRequest() const {
    std::cout << "Request IP in: " << ipIn << std::endl;
    std::cout << "Request IP out: " << ipOut << std::endl;
    std::cout << "Request time: " << time << std::endl;
    std::cout << "Request job type: " << jobType << std::endl;
}
