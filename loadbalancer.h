#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "request.h"
#include "webserver.h"
#include <queue>
#include <vector>
#include <random>

/**
 * @class LoadBalancer
 * @brief Simulates a load balancer that distributes incoming requests to multiple web servers.
 */
class LoadBalancer {
public:
    /**
     * @brief Constructs a LoadBalancer object.
     * @param numServers The number of web servers managed by the load balancer.
     * @param runtime The total runtime (in clock cycles) of the load balancer.
     */
    LoadBalancer(int numServers, int runtime);

    /**
     * @brief Adds a request to the load balancer's request queue.
     * @param request The request to be added to the queue.
     */
    void addRequest(const Request& request);

    /**
     * @brief Adds a new server to the load balancer.
     */
    void addServer();

    /**
     * @brief Removes the last server from the load balancer.
     */
    void removeServer();

    /**
     * @brief Balances the load by distributing requests to the available servers.
     * Uses a round-robin approach to assign requests to servers.
     */
    void balanceLoad();

    /**
     * @brief Generates a specified number of random requests.
     * @param numRequests The number of random requests to generate.
     */
    void generateRandomRequests(int numRequests);

    /**
     * @brief Gets the current size of the request queue.
     * @return The size of the request queue.
     */
    int getRequestQueueSize() const;

    /**
     * @brief Gets the minimum request time for processing.
     * @return The minimum request processing time (in clock cycles).
     */
    int getMinRequestTime() const;

    /**
     * @brief Gets the maximum request time for processing.
     * @return The maximum request processing time (in clock cycles).
     */
    int getMaxRequestTime() const;

    /**
     * @brief Gets the number of finished requests.
     * @return The total number of requests that have been processed.
     */
    int getRequestsFinished() const;

    /**
     * @brief Prints the log entries of all the servers.
     */
    void printLogEntries();

    /**
     * @brief Prints the starting status of the load balancer.
     * Displays the initial queue size and server statuses.
     * @param timeDuration The total duration of the simulation.
     */
    void printStartStatus(int timeDuration);

    /**
     * @brief Prints the final status of the load balancer.
     * Shows the final server statuses and queue size.
     */
    void printEndStatus();

private:
    std::queue<Request> requestQueue;     ///< Queue to hold incoming requests
    std::vector<WebServer> servers;       ///< Vector to hold the web servers
    int runtime;                          ///< Total runtime of the load balancer
    int nextServerIndex;                  ///< Tracks which server gets the next request (round-robin)
    int requestTimes[2];                  ///< Range for request times (min, max)
    int requestsFinished;                 ///< Number of requests that have been successfully processed
    int requestsRejected;                 ///< Number of requests that were rejected or discarded
};

#endif // LOADBALANCER_H
