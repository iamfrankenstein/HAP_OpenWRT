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
#include <iostream>
using namespace std;
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

//decompose base64
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
static char *decoding_table = NULL;

void build_decoding_table() {

    decoding_table = (char* )malloc(256);

    for (int i = 0; i < 64; i++)
        decoding_table[(unsigned char) encoding_table[i]] = i;
}

int base64_decode(const char *data,
                             int input_length,
                             char* decoded_data) {
    if (decoding_table == NULL) build_decoding_table();

    if (input_length % 4 != 0) return 0;

    int output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (output_length)--;
    if (data[input_length - 2] == '=') (output_length)--;

    //unsigned char decoded_data[150];
    if (decoded_data == NULL) return 0;

    for (int i = 0, j = 0; i < input_length;) {

        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

        uint32_t triple = (sextet_a << 3 * 6)
        + (sextet_b << 2 * 6)
        + (sextet_c << 1 * 6)
        + (sextet_d << 0 * 6);

        if (j < output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }
    return (input_length / 4 * 3);
}

void base64_cleanup() {
    free(decoding_table);
}

void create_key(char *keypart,uint64_t m_key){
    for (int i=0;i<8;i++) {
        uint64_t part = m_key;
        for (int j=i; j>0; j--)
            part = part >> 8;
        part = part & 0xff;
        keypart[i] = static_cast<char>(part);
    }
}

int main()
{
    int  decodedsize = 0;
    int  datasize = 0;
    char m_keypart[8];
    create_key(m_keypart, 0x0c2ad4a4acb9f023);
    char dataline[200]         = {"AwKszAf4KY3Xvu9zq3ejHlEhdOs+5y6fwLw=\n"};
    char decodedline[200] = {'\0'};

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

    //mesure data length
    //convert string to data (base64)
   // cout << decodedmidline<<"\n";
    //set counter and check length

    for(;;) {
        len=sizeof(caddr);
        n=recvfrom(sfd, line, 128, 0, (struct sockaddr *)&caddr, &len);
        fputs(line, stdout);
        if (n < 5) continue;
//-------------------------------------------------------------------------------------------------------------------------
        decodedsize = base64_decode(line,len,decodedline) -1;
        decodedsize-=2;
        if (decodedsize < 6)
            return(1);
        char *decodedmidline = 2+decodedline;
        int pos = 0;
        int lastChar = 0; 
 
        while (pos < decodedsize) {
            char currentChar = decodedmidline[pos];
            decodedmidline[pos] = decodedmidline[pos] ^ lastChar ^ m_keypart[(pos % 8)];
            lastChar = currentChar;
            ++pos;
        }
	decodedmidline[decodedsize]='\n';
	fputs(decodedmidline, stdout);
//--------------------------------------------------------------------------
        for (int iTemp = 0; ;iTemp++)
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

