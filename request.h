#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @class Request
 * @brief Represents a web request containing source IP, destination IP, job type, and processing time.
 * 
 * The Request class simulates a network request. It contains the source IP, destination IP, the type of job (processing or streaming),
 * and the time (in clock cycles) required to complete the job. It also supports generating requests with random IP addresses.
 */
class Request {
public:
    /**
     * @brief Constructs a Request with specified IP addresses, job time, and job type.
     * 
     * @param ipIn The source IP address of the request.
     * @param ipOut The destination IP address of the request.
     * @param time The time in clock cycles required to process the request.
     * @param jobType The type of job ('P' for processing, 'S' for streaming).
     */
    Request(const std::string& ipIn, const std::string& ipOut, int time, char jobType);

    /**
     * @brief Default constructor that generates a Request with random IP addresses and other parameters.
     * 
     * This constructor randomly generates IP addresses and can assign random times and job types.
     */
    Request();

    /**
     * @brief Gets the source IP address of the request.
     * 
     * @return A string representing the source IP address.
     */
    std::string getIpIn() const;

    /**
     * @brief Gets the destination IP address of the request.
     * 
     * @return A string representing the destination IP address.
     */
    std::string getIpOut() const;

    /**
     * @brief Gets the time required to process the request.
     * 
     * @return An integer representing the number of clock cycles needed to process the request.
     */
    int getTime() const;

    /**
     * @brief Gets the type of the job for this request.
     * 
     * @return A character ('P' for processing, 'S' for streaming) representing the job type.
     */
    char getJobType() const;

    /**
     * @brief Displays the details of the request.
     * 
     * This method prints the request's IP addresses, job type, and processing time to the console.
     */
    void displayRequest() const;

private:
    std::string ipIn;   /**< The source IP address */
    std::string ipOut;  /**< The destination IP address */

    int time;           /**< The time (in clock cycles) needed to process the request */
    char jobType;       /**< The type of job ('P' for processing, 'S' for streaming) */
};

#endif // REQUEST_H
