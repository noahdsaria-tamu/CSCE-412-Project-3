#include "loadbalancer.h"
#include <iostream>
#include <cstdlib> // For rand()
#include <climits> // For INT_MAX and INT_MIN
#include <ctime>   // For time()

int CURRENT_CYCLE = 1;
// Constructor: initialize servers and round-robin index
LoadBalancer::LoadBalancer(int numServers, int runtime) 
    : runtime(runtime), nextServerIndex(0), requestsFinished(0) {
    // Initialize the list of web servers
    for (int i = 0; i < numServers; ++i) {
        servers.emplace_back(WebServer(i + 1)); // Server IDs start from 1
    }
}

// Method to add a request to the queue
void LoadBalancer::addRequest(const Request& request) {
    int taskTime = request.getTime();
    if (taskTime < requestTimes[0]) requestTimes[0] = taskTime;
    if (taskTime > requestTimes[1]) requestTimes[1] = taskTime;
    else requestTimes[0] = INT_MAX, requestTimes[1] = INT_MIN;
    requestQueue.push(request);
}

// Method to balance the load by assigning requests to available servers
void LoadBalancer::balanceLoad() {
    srand((unsigned) time(0));
    for (; CURRENT_CYCLE <= runtime; ++CURRENT_CYCLE) {

        // Find an available server
        WebServer* availableServer = nullptr;

        // Simple round-robin approach to assign requests to servers
        for (int i = 0; i < int(servers.size()); ++i) {
            int currentIndex = (nextServerIndex + i) % servers.size();
            if (servers[currentIndex].isIdle()) {
                availableServer = &servers[currentIndex];
                nextServerIndex = (currentIndex + 1) % servers.size(); // Update next server index for round-robin
                break;
            }
        }

        // If we found an idle server, assign the request
        if (availableServer && !requestQueue.empty()) {
            const Request& nextRequest = requestQueue.front();
            availableServer->processRequest(nextRequest, CURRENT_CYCLE); // Assign request to the server
            requestsFinished++;
            requestQueue.pop();
        } 
        else if (!availableServer && !requestQueue.empty()) {
            std::cout << "Clock cycle " << CURRENT_CYCLE << ": No available servers. Requests in queue: " << requestQueue.size() << std::endl;
        }
        else if (!requestQueue.empty()) {
            int random = rand();

            if(random % 2 == 0) {
                std::cout << "Generating and adding a random request.\n";
                Request newRequest;
                addRequest(newRequest);
            }
            else {
                std::cout << "No random request generated.\n";
            }
        }
        else if(requestQueue.empty()) {
            std::cout << "Clock cycle " << CURRENT_CYCLE << ": No requests in queue. Servers are idle." << std::endl;
            
            int random = rand();

            if(random % 2 == 0) {
                std::cout << "Generating and adding a random request.\n";
                Request newRequest;
                addRequest(newRequest);
            }
            else {
                std::cout << "No random request generated.\n";
            }
        }
    }
}

// Method to generate random requests dynamically
void LoadBalancer::generateRandomRequests(int numRequests) {
    for (int i = 0; i < numRequests; ++i) {
        
        // Create a new request
        Request newRequest;
        addRequest(newRequest);
    }
}

int LoadBalancer::getRequestQueueSize() const {
    return requestQueue.size();
}

int LoadBalancer::getMinRequestTime() const {
    return requestTimes[0];
}

int LoadBalancer::getMaxRequestTime() const {
    return requestTimes[1];
}

int LoadBalancer::getRequestsFinished() const {
    return requestsFinished;
}