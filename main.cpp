#include <iostream>
#include "request.h"
#include "webserver.h"
#include "loadbalancer.h"

using namespace std;

int main() {
    
    int numServers;
    int timeDuration;

    cout << "Enter number of servers: ";
    cin >> numServers;

    cout << "Enter loadbalancer time duration (clock cycles): ";
    cin >> timeDuration;

	//start the load balancer

    LoadBalancer loadBalancer(numServers, timeDuration);
    loadBalancer.generateRandomRequests(numServers * 100);

    loadBalancer.printStartStatus(timeDuration);
    loadBalancer.balanceLoad();
    loadBalancer.printLogEntries();
    loadBalancer.printEndStatus();

    return 0;

}