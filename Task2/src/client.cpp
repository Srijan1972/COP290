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

	    sockVal = socket(AF_INET, SOCK_DGRAM, 0);

	    serv.sin_family = AF_INET;
	    serv.sin_port = htons(port);
	    serv.sin_addr.s_addr = inet_addr(IP.c_str());

	    l = sizeof(client);
	    m = sizeof(serv);

	    active =  true;
	}
    void send(std::string message)
	{
	    if (sendto(sockVal, message.c_str(), message.length(), 0, (struct sockaddr *)&serv, m) < 0)
	    {
	        fprintf(stderr,"Cannot send message");
	    }
	}
    std::string get(){
	    memset(buffer, 0, sizeof(buffer));
	    
	    int bytesRecieved = recvfrom(sockVal, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &l);

	    return std::string(buffer, bytesRecieved);
	}
    void end(){
	    active = false;

	    close(sockVal);
	}
    bool isActive(){
	    return active;
	}
};