#include "Wifi.hpp"

Wifi::Wifi() {

}

Wifi::~Wifi() {

}
int Wifi::getStatus(const char *iwname)
{
    iwreq req;
    strcpy(req.ifr_ifrn.ifrn_name, iwname);

    // iw_statistics *stats;

    //have to use a socket for ioctl
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    //make room for the iw_statistics object
    req.u.data.pointer = (iw_statistics *)malloc(sizeof(iw_statistics));
    req.u.data.length = sizeof(iw_statistics);

    //this will gather the signal strength
    if(ioctl(sockfd, SIOCGIWSTATS, &req) == -1){
        //die with error, invalid interface
        fprintf(stderr, "Invalid interface.\n");
        return(-1);
    }
    else if(((iw_statistics *)req.u.data.pointer)->qual.updated & IW_QUAL_DBM){
        //signal is measured in dBm and is valid for us to use
        wifi.level=((iw_statistics *)req.u.data.pointer)->qual.level - 256;
    }

    //SIOCGIWESSID for ssid
    char buffer[32];
    memset(buffer, 0, 32);
    req.u.essid.pointer = buffer;
    req.u.essid.length = 32;
    //this will gather the SSID of the connected network
    if(ioctl(sockfd, SIOCGIWESSID, &req) == -1){
        //die with error, invalid interface
        return(-1);
    }
    else{
        memcpy(&wifi.ssid, req.u.essid.pointer, req.u.essid.length);
        memset(&wifi.ssid[req.u.essid.length],0,1);
    }

    //SIOCGIWRATE for bits/sec (convert to mbit)
    int bitrate=-1;
    //this will get the bitrate of the link
    if(ioctl(sockfd, SIOCGIWRATE, &req) == -1){
        fprintf(stderr, "bitratefail");
        return(-1);
    }else{
        memcpy(&bitrate, &req.u.bitrate, sizeof(int));
        wifi.bitrate=bitrate/1000000;
    }


    //SIOCGIFHWADDR for mac addr
    ifreq req2;
    strcpy(req2.ifr_ifrn.ifrn_name, iwname);
    //this will get the mac address of the interface
    if(ioctl(sockfd, (unsigned long)SIOCGIFHWADDR, &req2) == -1){
        fprintf(stderr, "mac error");
        return(-1);
    }
    else{
        sprintf(wifi.mac, "%.2X", (unsigned char)req2.ifr_hwaddr.sa_data[0]);
        for(int s=1; s<6; s++){
            sprintf(wifi.mac+strlen(wifi.mac), ":%.2X", (unsigned char)req2.ifr_hwaddr.sa_data[s]);
        }
    }
    close(sockfd);
    return 1;
}
char * Wifi::getMAC()
{
    return wifi.mac;
}
int Wifi::getSignal()
{
    return wifi.level;
}
int Wifi::getSpeed()
{
    return wifi.bitrate;
}
char * Wifi::getSSID()
{
    return wifi.ssid;
}