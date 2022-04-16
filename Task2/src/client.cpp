#include <iostream>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <ifaddrs.h>
#include <sys/types.h>
#include <sys/socket.h>
class Client
{
private:

    const static int BUFFER_WIDTH = 1024;
    bool active;
    std::string ipaddr;
    int port;
    char buffer[Client::BUFFER_WIDTH];
    int sockVal;
    struct sockaddr_in serv, client;
    socklen_t l, m;

public:
    Client(std::string IP)
	{
	    this->ipaddr = IP;
	    this->port = 1234;

	    // Create the socket
	    sockVal = socket(AF_INET, SOCK_DGRAM, 0);

	    // Set connection properties
	    serv.sin_family = AF_INET;
	    serv.sin_port = htons(port);
	    serv.sin_addr.s_addr = inet_addr(IP.c_str());

	    // Set size of client and server
	    l = sizeof(client);
	    m = sizeof(serv);

	    // Assert active
	    active =  true;
	}
    void send(std::string message)
	{
	    // Try sending the message
	    if (sendto(sockVal, message.c_str(), message.length(), 0, (struct sockaddr *)&serv, m) < 0)
	    {
	        // Print error if message is not sent
	        fprintf(stderr,"Cannot send message");
	    }
	}
    std::string get(){
	    // Reset the buffer
	    memset(buffer, 0, sizeof(buffer));
	    
	    // Recieve the message
	    int bytesRecieved = recvfrom(sockVal, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &l);
	    
	    // Return the message
	    return std::string(buffer, bytesRecieved);
	}
    void end(){
	    // Set the active false
	    active = false;

	    // Close the socket
	    close(sockVal);
	}
    bool isActive(){
	    return active;
	}
};