#include <stdio.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

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

int main()
{
    int sfd, n;
    char name[] = {"Supperwir"};
    int  namesize = sizeof(name);
    socklen_t len;
    bool same;
    char line[128];
    struct sockaddr_in saddr, caddr;
    char charbuff = ' ';
    int fd = open_port();
    setBaudrate(fd);
    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(45454);

    bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr));

    printf("Server running\n");
    for(;;) {
        len=sizeof(caddr);
        n=recvfrom(sfd, line, 128, 0, (struct sockaddr *)&caddr, &len);
        line[n]='\n';
        n++;
        line[n+=1]='\0';
        fputs(line, stdout);
        if (n < 5) continue;

        for (int iTemp = 0; ; iTemp++)
        {
            if (line[iTemp]=='\n')
                break;
            if (line[iTemp]=='|'){
	     	printf("Processing Serial command\n");
		fputs(line+iTemp+1, stdout);
                if (iTemp >= namesize) continue;
                same=true;
                for (int jTemp  = 0; jTemp == iTemp; jTemp++)
                {
                    if (jTemp > namesize) break;
                    if (line[iTemp-jTemp]!=name[namesize-jTemp]){
                        same=false;
                        break;
                    }
                }
                if(same){
		    printf("*Sending Serial command\n");                
		    write(fd, &charbuff+iTemp, n-iTemp);
		}
		else
		    printf("*Ignore Serial command\n");
            }
         }
    }
    close (fd);
    return 0;
}

