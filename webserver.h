#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"
#include <string>
#include <vector>

/**
 * @struct LogEntry
 * @brief Represents a log entry for a WebServer.
 * 
 * Each log entry contains a clock cycle and a message, which helps to track the server's activity over time.
 */
struct LogEntry {
    int clockCycle;     /**< The clock cycle during which the log message was recorded */
    std::string message; /**< The log message detailing server activity */
};

/**
 * @class WebServer
 * @brief Represents a web server capable of processing requests and logging its activity.
 * 
 * The WebServer class simulates a server that processes requests, logs activity, and maintains an idle/busy status.
 * It can simulate processing time based on the provided request and time duration.
 */
class WebServer {
public:
    /**
     * @brief Constructs a WebServer with a specified ID.
     * 
     * @param id The unique ID assigned to the server.
     */
    WebServer(int id);

    /**
     * @brief Processes a request and logs the activity.
     * 
     * @param request The request to be processed by the server.
     * @param currentCycle The current clock cycle during which the request starts processing.
     * @param duration The time duration (in clock cycles) for which the request is processed.
     */
    void processRequest(const Request& request, int currentCycle, int duration);

    /**
     * @brief Checks if the server is idle.
     * 
     * @return true if the server is idle, false if it is currently processing a request.
     */
    bool isIdle() const;

    /**
     * @brief Simulates the time taken to process a request.
     * 
     * @param request The request being processed.
     * @param time The time in clock cycles required to process the request.
     * @param currentCycle The current clock cycle during which the processing occurs.
     */
    void simulateRequestTime(const Request& request, int time, int currentCycle);

    /**
     * @brief Gets the server's unique ID.
     * 
     * @return The unique ID of the server.
     */
    int getId() const;

    /**
     * @brief Logs a message with the current clock cycle.
     * 
     * @param clockCycle The clock cycle at which the message is logged.
     * @param message The message to log.
     */
    void logMessage(int clockCycle, const std::string& message);

    /**
     * @brief Gets the log entries recorded by the server.
     * 
     * @return A const reference to the vector of log entries.
     */
    const std::vector<LogEntry>& getLogEntries() const;

private:
    int serverId;        /**< Unique ID of the server */
    bool idle;           /**< Indicates whether the server is idle (true) or processing (false) */
    std::vector<LogEntry> log; /**< Stores log entries of server activities */
};

#endif // WEBSERVER_H
