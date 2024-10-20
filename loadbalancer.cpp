#include "loadbalancer.h"
#include <iostream>
#include <cstdlib> // For rand()
#include <climits> // For INT_MAX and INT_MIN
#include <ctime>   // For time()
#include <fstream>

int CURRENT_CYCLE = 1;

/**
 * @brief Constructs a LoadBalancer object and initializes servers.
 * @param numServers The number of web servers.
 * @param runtime The total runtime of the simulation in clock cycles.
 */
LoadBalancer::LoadBalancer(int numServers, int runtime) 
    : runtime(runtime), nextServerIndex(0), requestsFinished(0), requestsRejected(0) {
    // Initialize the list of web servers
    for (int i = 0; i < numServers; ++i) {
        servers.emplace_back(WebServer(i + 1)); // Server IDs start from 1
        std::cout << "WebServer " << (i + 1) << " created with LoadBalancer duration " << runtime << std::endl;
    }
    requestTimes[0] = INT_MAX, requestTimes[1] = INT_MIN;
}

/**
 * @brief Adds a request to the queue and updates min/max task times.
 * @param request The request to be added.
 */
void LoadBalancer::addRequest(const Request& request) {
    int taskTime = request.getTime();
    if (taskTime < requestTimes[0]) requestTimes[0] = taskTime;
    if (taskTime > requestTimes[1]) requestTimes[1] = taskTime;
    requestQueue.push(request);
}

/**
 * @brief Balances the load by assigning requests to available servers.
 * Simulates request assignment and processing using a round-robin approach.
 */
void LoadBalancer::balanceLoad() {
    srand((unsigned) time(0)); // Initialize random seed
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
            availableServer->processRequest(nextRequest, CURRENT_CYCLE, runtime); // Assign request to the server
            requestQueue.pop();
        } 
        // Log when no servers are available but requests are in queue
        else if (!availableServer && !requestQueue.empty()) {
            servers[0].logMessage(CURRENT_CYCLE, "Clock cycle " + std::to_string(CURRENT_CYCLE) +
               ": No available servers. Requests in queue: " + std::to_string(requestQueue.size()));
        }
        // Log and generate random requests when needed
        else if (!requestQueue.empty()) {
            int random = rand();

            if(random % 2 == 0) {
                servers[0].logMessage(CURRENT_CYCLE, "Clock cycle " + std::to_string(CURRENT_CYCLE) +
                ": Generating and adding a random request.");
                Request newRequest;
                addRequest(newRequest);
            }
            else {
                servers[0].logMessage(CURRENT_CYCLE, "Clock cycle " + std::to_string(CURRENT_CYCLE) +
                ": No random request generated.");
            }
        }
        else if(requestQueue.empty()) {
            servers[0].logMessage(CURRENT_CYCLE, "Clock cycle " + std::to_string(CURRENT_CYCLE) +
               ": No requests in queue. Servers are idle.");
            
            int random = rand();

            if(random % 2 == 0) {
                servers[0].logMessage(CURRENT_CYCLE, "Clock cycle " + std::to_string(CURRENT_CYCLE) +
                ": Generating and adding a random request.");
                Request newRequest;
                addRequest(newRequest);
            }
            else {
                servers[0].logMessage(CURRENT_CYCLE, "Clock cycle " + std::to_string(CURRENT_CYCLE) +
                ": No random request generated.");
            }
        }
    }
}

/**
 * @brief Generates a specified number of random requests and adds them to the queue.
 * @param numRequests The number of random requests to generate.
 */
void LoadBalancer::generateRandomRequests(int numRequests) {
    for (int i = 0; i < numRequests; ++i) {
        
        // Create a new request
        Request newRequest;
        addRequest(newRequest);
    }
}

/**
 * @brief Gets the current size of the request queue.
 * @return The number of requests in the queue.
 */
int LoadBalancer::getRequestQueueSize() const {
    return requestQueue.size();
}

/**
 * @brief Gets the minimum processing time of any request in the queue.
 * @return The minimum request processing time (in clock cycles).
 */
int LoadBalancer::getMinRequestTime() const {
    return requestTimes[0];
}

/**
 * @brief Gets the maximum processing time of any request in the queue.
 * @return The maximum request processing time (in clock cycles).
 */
int LoadBalancer::getMaxRequestTime() const {
    return requestTimes[1];
}

/**
 * @brief Gets the total number of requests that have been processed.
 * @return The number of finished requests.
 */
int LoadBalancer::getRequestsFinished() const {
    return requestsFinished;
}

/**
 * @brief Prints the log entries of all servers to the console and to an output file.
 */
void LoadBalancer::printLogEntries() {
    std::ofstream logFile("output.txt", std::ios::app);
    std::vector<LogEntry> allLogEntries;
    for (const auto& server : servers) {
        const auto& serverLogEntries = server.getLogEntries();
        allLogEntries.insert(allLogEntries.end(), serverLogEntries.begin(), serverLogEntries.end());
    }

    // Sort log entries by clock cycle
    std::sort(allLogEntries.begin(), allLogEntries.end(), [](const LogEntry& a, const LogEntry& b) {
        return a.clockCycle < b.clockCycle;
    });

    // Print each log entry
    for (const auto& entry : allLogEntries) {
        if (entry.clockCycle <= runtime) {
            std::cout << entry.message << std::endl;
            logFile << entry.message << std::endl;
            std::cout << "-------------------------------------------------------" << std::endl;
            logFile << "-------------------------------------------------------" << std::endl;
            if(entry.message.find("finished processing request") != std::string::npos) {
                requestsFinished++;
            }
            else if(entry.message.find("cannot be processed within the time duration") != std::string::npos) {
                requestsRejected++;
            }
        }
        // Beyond the runtime, discard the requests
        else {
            requestsRejected++;
        }
    }
    logFile.close();
}

/**
 * @brief Prints the initial status of the LoadBalancer including queue size and request time range.
 * @param timeDuration The total simulation duration in clock cycles.
 */
void LoadBalancer::printStartStatus(int timeDuration) {
    std::ofstream logFile("output.txt", std::ios::app);
    std::cout << "-------------------------------------------------------" << std::endl;
    logFile << "-------------------------------------------------------" << std::endl;
    std::cout << "Start LoadBalancer Status: " << std::endl;
    logFile << "Start LoadBalancer Status: " << std::endl;
    std::cout << "Starting with full queue size: " << getRequestQueueSize() << std::endl;
    logFile << "Starting with full queue size: " << getRequestQueueSize() << std::endl;
    std::cout << "Clock cycles: " << std::to_string(timeDuration) << std::endl;
    logFile << "Clock cycles: " << std::to_string(timeDuration) << std::endl;
    std::cout << "Range for request time: " << getMinRequestTime() << "-" << getMaxRequestTime() << " clock cycles\n";
    logFile << "Range for request time: " << getMinRequestTime() << "-" << getMaxRequestTime() << " clock cycles\n";
    std::cout << "-------------------------------------------------------" << std::endl;
    logFile << "-------------------------------------------------------" << std::endl;
    logFile.close();
}

/**
 * @brief Prints the final status of the LoadBalancer including server statuses and queue size.
 */
void LoadBalancer::printEndStatus() {
    std::ofstream logFile("output.txt", std::ios::app);
    int activeServers = 0;
    int inactiveServers = 0;
    for (const auto& server : servers) {
        if (server.isIdle()) {
            inactiveServers++;
        } else {
            activeServers++;
        }
    }

    std::cout << "End LoadBalancer Status: " << std::endl;
    logFile << "End LoadBalancer Status: " << std::endl;
    std::cout << "Remaining requests in the queue: " << getRequestQueueSize() << std::endl;
    logFile << "Remaining requests in the queue: " << getRequestQueueSize() << std::endl;
    std::cout << "Active servers: " << activeServers << std::endl;
    logFile << "Active servers: " << activeServers << std::endl;
    std::cout << "Inactive servers: " << inactiveServers << std::endl;
    logFile << "Inactive servers: " << inactiveServers << std::endl;
    std::cout << "Requests processed: " << requestsFinished << std::endl;
    logFile << "Requests processed: " << requestsFinished << std::endl;
    std::cout << "Requests rejected/discarded: " << requestsRejected << std::endl;
    logFile << "Requests rejected/discarded: " << requestsRejected << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    logFile << "-------------------------------------------------------" << std::endl;
    logFile.close();
}