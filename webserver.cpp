#include "webserver.h"
#include <iostream>
#include <thread>  // For simulating processing time

// Constructor to initialize the server with an ID and set it as idle
WebServer::WebServer(int id) : serverId(id), idle(true) {}

// Method to process a request
void WebServer::processRequest(const Request& request) {
    // Mark the server as busy
    idle = false;

    // Display the request being processed
    std::cout << "WebServer " << serverId << " is processing request from "
              << request.getIpIn() << " to " << request.getIpOut()
              << ", Job Type: " << (request.getJobType() == 'P' ? "Processing" : "Streaming")
              << std::endl;

    // Simulate the request processing based on the request's time
    simulateRequestTime(request.getTime());

    // After processing, mark the server as idle again
    idle = true;
}

// Check if the server is idle
bool WebServer::isIdle() const {
    return idle;
}

// Simulate the time it takes to process a request based on clock cycles
void WebServer::simulateRequestTime(int cycles) {
    // Simulating the request processing time by busy-waiting for the given number of clock cycles
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + std::chrono::nanoseconds(cycles);
    while (std::chrono::high_resolution_clock::now() < end) {
        // Busy-wait loop
    }
    std::cout << "WebServer " << serverId << " finished processing request" << std::endl;
}

// Get server ID
int WebServer::getId() const {
    return serverId;
}
