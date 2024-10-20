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
	cout << "-------------------------------------------------------" << endl;
    cout << "Start LoadBalancer Status: " << endl;
    LoadBalancer loadBalancer(numServers, timeDuration);
    loadBalancer.generateRandomRequests(numServers * 100);
    cout << "Starting with full queue size: " << loadBalancer.getRequestQueueSize() << endl;
	cout << "Clock cycles: " << to_string(timeDuration) << endl;
    cout << "Range for request time: " << loadBalancer.getMinRequestTime() << "-" << loadBalancer.getMaxRequestTime() << " clock cycles\n";
	cout << "-------------------------------------------------------" << endl;


    loadBalancer.balanceLoad();
    loadBalancer.printLogEntries();

    
    cout << "-------------------------------------------------------" << endl;
    cout << "End LoadBalancer Status: " << endl;
    cout << "Requests in queue processsed: " << loadBalancer.getRequestsFinished() << endl;
    cout << "Remaining requests in the queue: " << loadBalancer.getRequestQueueSize() << endl;
	cout << "-------------------------------------------------------" << endl;

    return 0;

}