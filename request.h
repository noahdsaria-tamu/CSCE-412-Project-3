#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
public:
    // Constructor
    Request(const std::string& ipIn, const std::string& ipOut);

    // Getters for accessing private members
    std::string getIpIn() const;
    std::string getIpOut() const;

private:
    std::string ipIn;
    std::string ipOut;
};

#endif // REQUEST_H
