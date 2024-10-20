#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "request.h"
#include "webserver.h"
#include <queue>
#include <vector>
#include <random>

class LoadBalancer {
public:
    // Constructor that initializes the load balancer with a number of servers
    LoadBalancer(int numServers, int runtime);

    // Method to add a request to the queue
    void addRequest(const Request& request);
    void balanceLoad();
    void generateRandomRequests(int numRequests);

    int getRequestQueueSize() const;
    int getMinRequestTime() const;
    int getMaxRequestTime() const;
    int getRequestsFinished() const;

private:
    std::queue<Request> requestQueue;     // Queue to hold the incoming requests
    std::vector<WebServer> servers;       // Vector to hold the web servers
    int runtime;                          // Total runtime of the load balancer
    int nextServerIndex;                  // To track which server gets the next request (round-robin)
    int requestTimes[2];                  // Range for request times (min, max)
    int requestsFinished;
};

#endif
