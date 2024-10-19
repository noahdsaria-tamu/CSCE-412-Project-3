#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
public:
    // Constructor
    Request(const std::string& ipIn, const std::string& ipOut, int time, char jobType);

    // Defining default constructor to generate random IP addresses
    Request();

    // Getters for accessing private members
    std::string getIpIn() const;
    std::string getIpOut() const;

    int getTime() const;
    char getJobType() const;

    void displayRequest() const;

private:
    std::string ipIn;
    std::string ipOut;

    int time;
    char jobType;
};

#endif // REQUEST_H
