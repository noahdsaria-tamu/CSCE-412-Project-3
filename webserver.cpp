#include "webserver.h"
#include <iostream>
#include <thread>  // For simulating processing time

// Constructor to initialize the server with an ID and set it as idle
WebServer::WebServer(int id) : serverId(id), idle(true) {}

// Method to process a request
void WebServer::processRequest(const Request& request, int currentCycle, int duration) {
    // Check if the request can be processed within the remaining duration
    if (request.getTime() + currentCycle > duration) {
        logMessage(currentCycle, "Clock cycle " + std::to_string(currentCycle) +
                   ": Request from " + request.getIpIn() + " to " + request.getIpOut() +
                   " cannot be processed within the time duration.");
        return;
    }

    // Mark the server as busy
    idle = false;

    // Display the request being processed
    logMessage(currentCycle, "Clock cycle " + std::to_string(currentCycle) +
               ": WebServer " + std::to_string(serverId) + " is processing request from " +
               request.getIpIn() + " to " + request.getIpOut() +
               " | Job Type: " + (request.getJobType() == 'P' ? "Processing " : "Streaming | Task Time: ") + std::to_string(request.getTime()) + " cycles | ");

    // Simulate the request processing based on the request's time
    simulateRequestTime(request, request.getTime(), currentCycle); 

    // After processing, mark the server as idle again
    idle = true;
}

// Check if the server is idle
bool WebServer::isIdle() const {
    return idle;
}

// Simulate the time it takes to process a request based on clock cycles
void WebServer::simulateRequestTime(const Request& request, int cycles, int currentCycle) {
    // Simulating the request processing time by busy-waiting for the given number of clock cycles
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + std::chrono::nanoseconds(cycles);
    while (std::chrono::high_resolution_clock::now() < end) {
        // Busy-wait loop
    }
    logMessage(cycles + currentCycle, "Clock cycle " + std::to_string(cycles + currentCycle) +
               ": WebServer " + std::to_string(serverId) + " finished processing request from " + request.getIpIn() + " to " + request.getIpOut());
}

// Get server ID
int WebServer::getId() const {
    return serverId;
}

void WebServer::logMessage(int clockCycle, const std::string& message) {
    log.push_back({clockCycle, message});
}

const std::vector<LogEntry>& WebServer::getLogEntries() const {
    return log;
}
