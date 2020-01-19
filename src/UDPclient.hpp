#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class UDPclient
{
private:
    
    
public:
    UDPclient(/* args */);
    ~UDPclient();

    int begin(char * hostname, int port);
    int send(char * buf, size_t len);
    int recv(char * buf, size_t siz);
    private:
    int _port;
    int sock, length, n;
    struct sockaddr_in server, from;
    struct hostent *hp;
};

