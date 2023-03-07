#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(54154);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), '\0', sizeof server_addr.sin_zero);
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof server_addr);

    while (1)
    {
        char buff[100];
        int addr_len = sizeof server_addr;
        recvfrom(sockfd, buff, sizeof buff, 0, (struct sockaddr *)&server_addr, &addr_len);
        sendto(sockfd, buff, sizeof buff, 0, (struct sockaddr *)&server_addr, sizeof server_addr);
    }

    close(sockfd);
    return 0;
}