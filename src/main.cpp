#include <iostream>
#include <string>
#include <unistd.h>

#include "mavesp8266.h"
#include "mavesp8266_vehicle.h"
#include "mavesp8266_gcs.h"

#include "Wifi.hpp"
#include "Serial.hpp"

//libraries necessary for wifi ioctl communication
#include <linux/wireless.h>
#include <sys/ioctl.h>

using namespace std;
// udp_client_server::udp_server s("192.168.0.113", 12345);
// udp_client_server::udp_client * udpClient;

char tmp[100];

MavESP8266GCS           GCS;
MavESP8266Vehicle       Vehicle;
MavESP8266Log           Logger;
Serial  uart;
//---------------------------------------------------------------------------------
//-- Accessors


class MavESP8266WorldImp : public MavESP8266World {
public:
    MavESP8266Vehicle*      getVehicle      () { return &Vehicle;       }
    MavESP8266GCS*          getGCS          () { return &GCS;           }
    MavESP8266Log*          getLogger       () { return &Logger;        }
    Serial*                 getSerial       () { return &uart;          }
};

MavESP8266WorldImp      World;

MavESP8266World* getWorld()
{
    return &World;
}

int main (int argc, char ** argv)
{
    
	system("uname -a");
    for(int x = 0 ; x<argc;x++)
    {
        printf("arg %d = %s\r\n", x, argv[x]);
    }
    if(argc!=5)
    {
        printf("Usage : UDP_Host UDP_Port SerialPort Baudrate\r\n");
        printf("Eg : 192.168.43.1 1133 /dev/ttyS0 921600\r\n");
        return 0;
    }
    // uart.begin("/dev/ttyS0", 921600);
    uart.begin(argv[3], atoi(argv[4]));

    GCS.begin(&Vehicle, argv[1], atoi(argv[2]));
    Vehicle.begin(&GCS);
    printf("GCS and Vehice initialized...\r\n");
    
    while(1)
    {
        
        GCS.readMessage();
        
        usleep(1000);
        
        Vehicle.readMessage();
        
    }
}
