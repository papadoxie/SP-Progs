#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Must enter IP and port of echo server\n");
        exit(1);
    }

    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &dest_addr.sin_addr);
    memset(&(dest_addr.sin_zero), '\0', sizeof dest_addr.sin_zero);

    char buff1[128], buff2[128];
    while (1)
    {
        int n = read(0, buff1, sizeof buff1);
        buff1[n] = '\0';
        sendto(sockfd, buff1, sizeof buff1, 0, (struct sockaddr *)&dest_addr, sizeof dest_addr);
        int addr_len = sizeof dest_addr;
        recvfrom(sockfd, buff2, sizeof buff2, 0, (struct sockaddr *)&dest_addr, &addr_len);
        buff2[n] = '\0';
        write(1, buff2, n);
    }

    close(sockfd);
    exit(0);
}