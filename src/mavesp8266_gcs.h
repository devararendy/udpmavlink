
#ifndef MAVESP8266_GCS_H
#define MAVESP8266_GCS_H

#include <string>
#include <unistd.h>
#include "mavesp8266.h"
#include "Wifi.hpp"
#include "UDPclient.hpp"

using namespace std;

class MavESP8266GCS : public MavESP8266Bridge {
public:
    MavESP8266GCS();

    void    begin                   (MavESP8266Bridge* forwardTo, string gcsIP, uint16_t port );
    void    readMessage             ();
    void    readMessageRaw          ();
    int     sendMessage             (mavlink_message_t* message, int count);
    int     sendMessage             (mavlink_message_t* message);
    int     sendMessageRaw           (uint8_t *buffer, int len);
protected:
    void    _sendRadioStatus        ();

private:
    bool    _readMessage            ();
    void    _sendSingleUdpMessage   (mavlink_message_t* msg);
    void    _checkUdpErrors         (mavlink_message_t* msg);

private:
    UDPclient           _udp;
    string              _ip;
    mavlink_message_t   _message;
    unsigned long       _last_status_time;
    Wifi                wifi;
};

#endif
