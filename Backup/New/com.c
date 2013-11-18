
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

int
open_port(void)
{
    int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
    /*
    * Could not open the port.
    */

    perror("open_port: Unable to open /dev/ttyf1 - ");
    }
    else
    fcntl(fd, F_SETFL, 0);

    return (fd);
}

void setBaudrate(int fd)
{
    struct termios options;

    /*
    * Get the current options for the port...
    */

    tcgetattr(fd, &options);

    /*
    * Set the baud rates to 19200...
    */

    cfsetispeed(&options, B38400);
    cfsetospeed(&options, B38400);

    /*
    * Enable the receiver and set local mode...
    */

    options.c_cflag |= (CLOCAL | CREAD);

    /*
    * Set the new options for the port...
    */

    options.c_cflag &= ~CSIZE; /* Mask the character size bits */
    options.c_cflag |= CS8;    /* Select 8 data bits */

    tcsetattr(fd, TCSANOW, &options);

}

int
main ()
{
    char charbuff = ' ';
    int fd = open_port();
    setBaudrate(fd);
    while (1==1){
        charbuff = getchar();
	if (charbuff == '\0')  break;
	write(fd, &charbuff, 1);
    }
    close (fd);
    return (0);
}

