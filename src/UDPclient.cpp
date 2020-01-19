#include "UDPclient.hpp"
#include "mavesp8266.h"

UDPclient::UDPclient(/* args */)
{

}

UDPclient::~UDPclient()
{
   
}

int UDPclient::begin(char * hostname, int port)
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {   printf("Error : socket\r\n");
        return -1;
    }
    server.sin_family = AF_INET;
    hp = gethostbyname(hostname);
    if(hp==0)
    {   
        printf("Error : Unknown host..\r\n");
        return -2;
    }
    bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
    server.sin_port = htons(port);
    length = sizeof (struct sockaddr_in);
    _port = port;
    return 1;

}

int UDPclient::send(char * buf, size_t len)
{
    // bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
    // server.sin_port = htons(_port);
    // length = sizeof (struct sockaddr_in);

    n = sendto(sock, buf, len, 0, (sockaddr *)&server, length);
    if(n<0)
    {   
        printf("Error : sendTo");
        return -1;
    }
    return n;
}
int UDPclient::recv(char * buf, size_t siz)
{
    // bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
    // server.sin_port = htons(_port);
    // length = sizeof (struct sockaddr_in);


    // unsigned long tstart, dt;
    
    n = sendto(sock, buf, 0, 0, (sockaddr *)&server, length);
    // n = recvfrom(sock, buf, siz, 0, (sockaddr *)&from, (socklen_t *)&length);
    // tstart = getWorld()->getSerial()->millis();
    n = ::recv(sock, buf, siz, MSG_DONTWAIT);
    // dt = getWorld()->getSerial()->millis() - tstart;
    // printf("dt %d\r\n", dt);
    // if(n<0)
    // {
    //     printf("Error : recvfrom");
    //     return -1;
    // }
    return n;
}