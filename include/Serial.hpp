#pragma once
// C library headers
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <stdarg.h>
#include <sys/time.h>
class Serial {

public:
    Serial();
    int begin(const char * file, int baud=921600);
    int sendBytes(char *data, int len);
    int readBytes(char * data, int len);
    int DataAvail();
    void Printf (const char *message, ...);
    void flush();
    int Getchar();
    ~Serial();
    unsigned long millis();
    private:
    int         serial_port;

};