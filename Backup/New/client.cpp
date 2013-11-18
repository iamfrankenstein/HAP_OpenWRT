#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#define MAX 100
 
int main(int argc, char** argv)
{
    int sfd, n;
    socklen_t len;
    char sline[MAX], rline[MAX+1];
    struct sockaddr_in saddr;

    sfd = socket(AF_INET, SOCK_DGRAM, 0);   
 
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl (INADDR_ANY); /* any local host internet address */
    saddr.sin_port = htons(45454);
 
    printf("Client Running\n");
    while(fgets(sline, MAX, stdin)!=NULL) {
        len=sizeof(saddr);
        sendto(sfd, sline, strlen(sline), 0, (struct sockaddr *)&saddr, len);
    }
    return 0;
}
