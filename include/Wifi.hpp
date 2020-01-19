#pragma once
//libraries necessary for wifi ioctl communication
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/wireless.h>
#include <sys/ioctl.h>

//struct to hold collected information
struct signalInfo {
    char mac[18];
    char ssid[33];
    int bitrate;
    int level;
};
class Wifi {

public:
    Wifi();
    int getStatus(const char *iwname);
    char * getMAC();
    int getSignal();
    int getSpeed();
    char * getSSID();

    ~Wifi();

private:
    signalInfo wifi;
};