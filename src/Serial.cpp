#include "Serial.hpp"

Serial::Serial() {

}

Serial::~Serial() {
    close(serial_port);
}
int Serial::begin(const char * file, int baud)
{
    serial_port = open(file, O_RDWR);

    // Create new termios struc, we call it 'tty' for convention
    struct termios tty;
    memset(&tty, 0, sizeof tty);

    // Read in existing settings, and handle any error
    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }

    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag |= CS8; // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

    tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 9600
    switch (baud)
  {
    case      50:	baud =      B50 ; break ;
    case      75:	baud =      B75 ; break ;
    case     110:	baud =     B110 ; break ;
    case     134:	baud =     B134 ; break ;
    case     150:	baud =     B150 ; break ;
    case     200:	baud =     B200 ; break ;
    case     300:	baud =     B300 ; break ;
    case     600:	baud =     B600 ; break ;
    case    1200:	baud =    B1200 ; break ;
    case    1800:	baud =    B1800 ; break ;
    case    2400:	baud =    B2400 ; break ;
    case    4800:	baud =    B4800 ; break ;
    case    9600:	baud =    B9600 ; break ;
    case   19200:	baud =   B19200 ; break ;
    case   38400:	baud =   B38400 ; break ;
    case   57600:	baud =   B57600 ; break ;
    case  115200:	baud =  B115200 ; break ;
    case  230400:	baud =  B230400 ; break ;
    case  460800:	baud =  B460800 ; break ;
    case  500000:	baud =  B500000 ; break ;
    case  576000:	baud =  B576000 ; break ;
    case  921600:	baud =  B921600 ; break ;
    case 1000000:	baud = B1000000 ; break ;
    case 1152000:	baud = B1152000 ; break ;
    case 1500000:	baud = B1500000 ; break ;
    case 2000000:	baud = B2000000 ; break ;
    case 2500000:	baud = B2500000 ; break ;
    case 3000000:	baud = B3000000 ; break ;
    case 3500000:	baud = B3500000 ; break ;
    case 4000000:	baud = B4000000 ; break ;

    default:
      baud =  B115200 ;
  }
    cfsetispeed(&tty, baud);
    cfsetospeed(&tty, baud);

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return -1;
    }
    return 1;
}
int Serial::sendBytes(char *data, int len)
{
    return write(serial_port,data, len);
}
int Serial::readBytes(char * data, int len)
{
    memset(data, 0, len);
    return read(serial_port, data, len);

}
int Serial::DataAvail()
{
  int result ;

  if (ioctl (serial_port, FIONREAD, &result) == -1)
    return -1 ;

  return result ;
}
void Serial::Printf(const char *message, ...)
{
  va_list argp ;
  char buffer [1024] ;

  va_start (argp, message) ;
    vsnprintf (buffer, 1023, message, argp) ;
  va_end (argp) ;

  sendBytes(buffer, strlen(buffer));
}
void Serial::flush()
{
  tcflush (serial_port, TCIOFLUSH);
}
int Serial::Getchar()
{
  char x ;

  if (read (serial_port, &x, 1) != 1)
    return -1 ;

  return ((int)x) & 0xFF ;
}
unsigned long Serial::millis()
{
    timeval current;
    gettimeofday(&current,NULL);
    long mtmp = ((current.tv_sec) * 1000 + current.tv_usec/1000.0) + 0.5;
    return mtmp;
}