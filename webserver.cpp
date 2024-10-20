#include "webserver.h"
#include <iostream>
#include <thread>  // For simulating processing time

/**
 * @brief Constructor to initialize the WebServer with an ID.
 * 
 * @param id The ID of the server being initialized.
 */
WebServer::WebServer(int id) : serverId(id), idle(true) {}

/**
 * @brief Method to process a request assigned to the server.
 * 
 * This method checks if the request can be processed within the remaining
 * time of the load balancer's runtime. If possible, the server processes
 * the request and marks itself as idle afterward.
 * 
 * @param request The request object containing details like time, IPs, and job type.
 * @param currentCycle The current clock cycle at which the request is assigned.
 * @param duration The total runtime of the load balancer.
 */
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
               " | Job Type: " + (request.getJobType() == 'P' ? "Processing " : "Streaming | Task Time: ") +
               std::to_string(request.getTime()) + " cycles | ");

    // Simulate the request processing based on the request's time
    simulateRequestTime(request, request.getTime(), currentCycle);

    // After processing, mark the server as idle again
    idle = true;
}

/**
 * @brief Check if the server is idle.
 * 
 * This method returns whether the server is idle (i.e., ready to accept a new request).
 * 
 * @return True if the server is idle, false if it is busy processing a request.
 */
bool WebServer::isIdle() const {
    return idle;
}

/**
 * @brief Simulates the processing time of a request by busy-waiting.
 * 
 * This method simulates the time it takes for a web server to process a request.
 * It "busy-waits" for the duration specified by the request's processing time.
 * 
 * @param request The request object being processed.
 * @param cycles The number of clock cycles required to process the request.
 * @param currentCycle The current clock cycle at the start of processing.
 */
void WebServer::simulateRequestTime(const Request& request, int cycles, int currentCycle) {
    // Simulating the request processing time by busy-waiting for the given number of clock cycles
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + std::chrono::nanoseconds(cycles);
    while (std::chrono::high_resolution_clock::now() < end) {
        // Busy-wait loop
    }
    logMessage(cycles + currentCycle, "Clock cycle " + std::to_string(cycles + currentCycle) +
               ": WebServer " + std::to_string(serverId) + " finished processing request from " +
               request.getIpIn() + " to " + request.getIpOut());
}

/**
 * @brief Get the ID of the server.
 * 
 * This method returns the unique server ID assigned when the server was created.
 * 
 * @return An integer representing the server ID.
 */
int WebServer::getId() const {
    return serverId;
}

/**
 * @brief Logs a message for the server's activity.
 * 
 * This method records a log entry with the current clock cycle and a descriptive
 * message regarding the server's actions (e.g., processing a request, finishing a request).
 * 
 * @param clockCycle The current clock cycle at the time of the event.
 * @param message The message to be logged, describing the server's activity.
 */
void WebServer::logMessage(int clockCycle, const std::string& message) {
    log.push_back({clockCycle, message});
}

/**
 * @brief Get the log entries for the server.
 * 
 * This method returns a vector of all log entries recorded by the server.
 * Each log entry includes the clock cycle and a message describing the server's activity.
 * 
 * @return A reference to a vector of LogEntry objects.
 */
const std::vector<LogEntry>& WebServer::getLogEntries() const {
    return log;
}
