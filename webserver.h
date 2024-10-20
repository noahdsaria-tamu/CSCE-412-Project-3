#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"
#include <string>
#include <vector>

struct LogEntry {
    int clockCycle;
    std::string message;
};

class WebServer {
public:
    // Constructor
    WebServer(int id);

    void processRequest(const Request& request, int currentCycle);
    bool isIdle() const;
    void simulateRequestTime(int time, int currentCycle);
    int getId() const;

    void logMessage(int clockCycle, const std::string& message);
    const std::vector<LogEntry>& getLogEntries() const;

private:
    int serverId;      // Unique ID for the server
    bool idle;         // Server status (true if idle, false if processing)
    std::vector<LogEntry> log; // Log of server activities
};

#endif // WEBSERVER_H
