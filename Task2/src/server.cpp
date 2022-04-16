#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <ifaddrs.h>

// Constructor
class Server
{
private:
    const static int BUFFER_WIDTH = 1024;
    bool active;
    std::string ipaddr;
    int port;
    char buffer[Server::BUFFER_WIDTH];
    int sockVal;
    struct sockaddr_in serv, client;
    socklen_t l;

public:
    // Constructor
    Server(std::string IP){
        this->ipaddr = IP;
        this->port = 1234;

        sockVal = socket(AF_INET, SOCK_DGRAM, 0);

        serv.sin_family = AF_INET;
        serv.sin_port = htons(port);
        serv.sin_addr.s_addr = inet_addr(IP.c_str());

        if (bind(sockVal, (struct sockaddr *)&serv, sizeof(serv)) < 0)
        {
            fprintf(stderr,"Error binding socket");
        }

        active = true;
        l = sizeof(client);
    }
    
    void send(std::string message)
    {
        // Try sending the message
        if(sendto(sockVal, message.c_str(), message.length(), 0, (struct sockaddr *)&client, l) < 0)
        {
            // Print the error
            fprintf(stderr,"Cannot send message...");
        }
    }
    
    std::string get()
    {
        // Reset the buffer
        memset(buffer, 0, sizeof(buffer));
        
        // Recieve the messages
        int bytesRecieved = recvfrom(sockVal, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &l);
        
        // Return the message
        return std::string(buffer, bytesRecieved);
    }
    
   void end()
    {
        // Set the active false
        active = false;

        // Close the socket
        close(sockVal);
    }


    // Returns true if the socket is active
    bool isActive()
    {
        return active;
    }
};