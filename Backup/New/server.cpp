#include <stdio.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
 
int main()
{
    int sfd, n;
    socklen_t len;
    char line[128];
    struct sockaddr_in saddr, caddr;
 
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
	line[n+1]='\0';
        fputs(line, stdout);
    }
 
    return 0;
}
