#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"

class WebServer {
public:
    // Constructor
    WebServer(int id);

    // Method to process a request
    void processRequest(const Request& request);

    // Check if the server is idle
    bool isIdle() const;

    // Method to simulate request processing
    void simulateRequestTime(int time);

    // Get server ID
    int getId() const;

private:
    int serverId;      // Unique ID for the server
    bool idle;         // Server status (true if idle, false if processing)
};

#endif // WEBSERVER_H
